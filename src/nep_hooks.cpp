#include "defs.h"
#include "def_funcs.h"
#include "subhook.h"
#include "nep_main.h"
#include "nep_hooks.h"
#include "nep_shaders.h"
#include "nep_config.h"
#include "nep_util.h"

int shaderNum = 0;

subhook_t cgCreateProgram_hook;
cgCreateProgram_t cgCreateProgram_real;

int wndWidth, wndHeight;
int targetWidth = -1;
int targetHeight = -1;
int targetShadowSize = -1;
int checkSizeExcludeTex = -1;

HWND wnd = NULL;

int cgCreateProgram(int context, int program_type, const char* program, int profile, const char* entry, const char** args) {
    NEP_LOGV("cgCreateProgram enter | len: %d\n", strlen(program));
    subhook_remove(cgCreateProgram_hook);
    
    static float outlinesTransparency = nepCfg.getf("Outlines intensity");
    static bool simpleOutlines = nepCfg.getb("Simple outlines");
    static float shadowBlur = nepCfg.getf("Shadow blur");

    //goto skip;
    char progBuf[10240];
    switch(strlen(program)) {
        // Disable the dogshit Vita-resolution FXAA that ruins the picture on glorious 8K PC monitors
        // Also fill the bloom part with config values
        // Yes, that's right, they put FXAA and bloom code into the same fucking shader.
        case 10436: // RB1
        case 9905: // RB2
        case 9416: // RB3
        // Victory end screen. For some reason it must have a different shader that does nearly the same job.
        case 6989: // RB1
        case 6465: // RB2
        case 6468: // RB3
            if(!nepCfg.getb("Enable new FXAA and bloom")) break;
            sprintf(progBuf, nepGame == NEP_RB1 ? nep_new_bloom_no_fxaa_rb1 : nep_new_bloom_no_fxaa,
                nepCfg.geti("Bloom samples"),
                nepCfg.getf("Bloom softness"),
                nepCfg.getf("Bloom contrast"),
                nepCfg.getf("Bloom intensity"));
            program = progBuf;
            break;
            
        case 551: // RB1
        case 650: // RB2 & RB3
            if (!nepCfg.getb("Enable outline control")) break;
            sprintf(progBuf, nep_outlines_items, outlinesTransparency);
            program = progBuf;
            break;

        case 944: // RB1
        case 905: // RB2
        case 946: // RB3
            if (!nepCfg.getb("Enable outline control")) break;
            sprintf(progBuf, simpleOutlines ? nep_outlines_flat_girls : nep_outlines_girls, outlinesTransparency);
            program = progBuf;
            break;

        case 3727: // RB2
        case 5365: // RB2
        case 5575: // RB3
        case 4206: // RB3
            if (!nepCfg.getb("Enable outline control")) break;
            // Vertex shaders for outlines
            if((nepGame == NEP_RB2 || nepGame == NEP_RB3) && outlinesTransparency == 0.0f)
                program = "";
            break;

        case 2063: // RB1
        case 990: // RB2 && RB3
            if (!nepCfg.getb("Enable shadow control")) break;
            sprintf(progBuf, nepGame == NEP_RB1 ? nep_shadow_rb1 : nep_shadow, ((float)SHADOW_RES_CFG / targetShadowSize) * shadowBlur);
            program = progBuf;
    }
    //skip:

    int res = cgCreateProgram_real(context, program_type, program, profile, entry, args);

    subhook_install(cgCreateProgram_hook);
    NEP_LOGV("cgCreateProgram exit\n");
    return res;
}

typedef bool (WINAPI* wglSwapIntervalEXT_t)(int interval);
wglSwapIntervalEXT_t wglSwapIntervalEXT_real;

bool WINAPI wglSwapIntervalEXT(int interval) {
    (void)interval; // -1 = Adaptive VSync, 0 = no VSync, 1 = VSync. Game tries to set 1.
    int cfgOpt = nepCfg.geti("VSync type");
    // Config: 1 = No VSync, 2 = VSync, 3 = Adaptive VSync
    return wglSwapIntervalEXT_real(cfgOpt == 1 ? 0 : (cfgOpt == 2 ? 1 : -1));
}

GLPROXY_EXTERN PROC GLPROXY_DECL glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data) {
    static GLProxy::TGLFunc<PROC, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*> TGLFUNC_DECL(glTexImage2D);

    bool freeData = false;
    int tex;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex);
    NEP_LOGV("glTexImage2D enter | id: %d, width: %d, height: %d, target: %d, level: %d, internalformat: %d, format: %d, type: %d, data: %#010x\n", tex, width, height, target, level, internalformat, format, type, (uint32_t)data)
    
    static bool resControl = nepCfg.getb("Enable resolution control");
    static bool newFxaaBloom = nepCfg.getb("Enable new FXAA and bloom");
    static bool shadowControl = nepCfg.getb("Enable shadow control");
    static bool anisotropy = nepCfg.getb("Enable anisotropy");
    static bool compression = nepCfg.getb("Enable texture compression");

    if (resControl && checkSize(width, height) &&
        (!safeMode || safeMode && tex < 20)) {
        if (nepGame == NEP_RB1 || nepGame == NEP_RB2 || tex < 20) {
            width = targetWidth;
            height = targetHeight;
            data = NULL;
        }
        else if (nepGame == NEP_RB3) {
            // Unlike RB2, in RB3 textures are always created with data, even if that data is completely empty at the time.
            // Sometimes it isn't, however; Tutorial images (also sized 1920x1088) are one such case.
            bool empty = true;
            for (int i = 0; i < width * height * 4; i++) // It's RGBA, I promise
                if (((uint8_t*)data)[i]) {
                    empty = false;
                    checkSizeExcludeTex = tex;
                    break;
                }
            if (empty) {
                data = malloc(targetWidth * targetHeight * 4);
                freeData = true;
                width = targetWidth;
                height = targetHeight;
            }
        }
    }
    else if (newFxaaBloom && !data && checkIsBloom(width, height))
        setBloomSize(&width, &height);
    else if(shadowControl && checkIsShadow(width, height)) {
        if(tex == 8 || tex == 9 || tex == 10) {
            width = targetShadowSize;
            height = targetShadowSize;
            if(nepGame == NEP_RB1 || nepGame == NEP_RB3) {
                data = malloc(width * height * 4); // RGBA format. For monochrome shadows.
                freeData = true;
            }
            if(nepGame == NEP_RB2)
                // Can't pull this off in RB3 anymore, no siree!
                internalformat = GL_RED;
        }
    }
    else if(compression && (width > 2048 || height > 2048)) {
        // Compressing screenspace effect textures does not end well.
        if(width != targetWidth && (internalformat == GL_RGB || internalformat == GL_RGBA)) {
            internalformat = internalformat == GL_RGB ? GL_COMPRESSED_RGB : GL_COMPRESSED_RGBA;
            NEP_LOGI("Compressing %d x %d texture\n", width, height)
        }
    }

    if(anisotropy && target == GL_TEXTURE_2D && data != NULL) {
        GLfloat largest_supported_anisotropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);
    }

    NEP_LOGV("glTexImage2D pre call | id: %d, width: %d, height: %d, target: %d, level: %d, internalformat: %d, format: %d, type: %d, data: %#010x\n", tex, width, height, target, level, internalformat, format, type, (uint32_t)data)
    auto ret = TGLFUNC_CALL(glTexImage2D, target, level, internalformat, width, height, border, format, type, data);
    // Here in the Wild East we do this and many more things unfathomable.
    if(freeData) free((void*)data);
    
    printGlErrors();
    NEP_LOGV("glTexImage2D exit\n");
    return ret;
}

// OpenGL functions use __stdcall instead of __cdecl, and if you don't know that, you will spend hours debugging the crashes like a retard (me)
typedef void(__stdcall* glRenderbufferStorageEXT_t)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
glRenderbufferStorageEXT_t glRenderbufferStorageEXT_real;

void __stdcall glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    int tex;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex);
    NEP_LOGV("glRenderbufferStorageEXT enter | id: %d, width: %d, height: %d, target: %d, internalformat: %d\n", tex, width, height, target, internalformat)

    static bool resControl = nepCfg.getb("Enable resolution control");
    static bool newFxaaBloom = nepCfg.getb("Enable new FXAA and bloom");
    static bool shadowControl = nepCfg.getb("Enable shadow control");

    if(resControl && tex != checkSizeExcludeTex && checkSize(width, height) &&
        (!safeMode || safeMode && tex < 20)) {
        width = targetWidth;
        height = targetHeight;
    }
    else if(newFxaaBloom && checkIsBloom(width, height))
        setBloomSize(&width, &height);
    else if (shadowControl && checkIsShadow(width, height)) {
        // Needed for RB2. Not sure if any other buffers of RB3 (512x512) shadow size are created later in that game, but doesn't hurt to leave this just in case.
        static int counter = 0;
        if (counter == 0) {
            width = targetShadowSize;
            height = targetShadowSize;
        }
        counter++;
    }

    glRenderbufferStorageEXT_real(target, internalformat, width, height);
    NEP_LOGV("glRenderbufferStorageEXT exit\n");
}

GLPROXY_EXTERN PROC GLPROXY_DECL glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    static GLProxy::TGLFunc<PROC, GLint, GLint, GLsizei, GLsizei> TGLFUNC_DECL(glViewport);

    int tex;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex);
    NEP_LOGV("glViewport enter | id: %d, x: %d, y: %d, width: %d, height: %d\n", tex, x, y, width, height)
    
    static bool resControl = nepCfg.getb("Enable resolution control");
    static bool newFxaaBloom = nepCfg.getb("Enable new FXAA and bloom");
    static bool shadowControl = nepCfg.getb("Enable shadow control");

    // glViewport is the first one to be called among all functions whose parameters need to be changed
    if (!wnd) {
        NEP_LOGV("Getting window\n")
        getNepWindow();
        NEP_LOGV("Computing settings\n")
        computeSettings();
        NEP_LOGV("Checking FPS unlock...\n")
        if ((nepGame == NEP_RB1 || nepGame == NEP_RB2) && nepCfg.getb("FPS Unlock"))
            fpsUnlock();
        NEP_LOGV("Initial glViewport setup done\n")
    }

    if(resControl && tex != checkSizeExcludeTex && checkSize(width, height)) {
        width = targetWidth;
        height = targetHeight;
    }
    else if(newFxaaBloom && checkIsBloom(width, height))
        setBloomSize(&width, &height);
    else if(shadowControl && checkIsShadow(width, height) && (
        nepGame == NEP_RB1 && (tex == 0 || tex == 8 || tex == 9) ||
        nepGame == NEP_RB2 && (tex == 0 || tex == 8 || tex == 9) ||
        nepGame == NEP_RB3 && tex == 0)) {
        width = targetShadowSize;
        height = targetShadowSize;
    }

    // Maps/UI
    if (resControl && ((x > 0 && y > 0) || y < 0)) {
        x = x * targetWidth / DEF_W;
        y = y * targetHeight / DEF_H;
        width = width * targetWidth / DEF_W;
        height = height * targetHeight / DEF_H;
    }

    auto ret = TGLFUNC_CALL(glViewport, x, y, width, height);
    NEP_LOGV("glViewport exit\n");
    return ret;
}

GLPROXY_EXTERN PROC GLPROXY_DECL glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    static GLProxy::TGLFunc<PROC, GLint, GLint, GLsizei, GLsizei> TGLFUNC_DECL(glScissor);

    int tex;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex);
    NEP_LOGV("glScissor enter | id: %d, x: %d, y: %d, width: %d, height: %d\n", tex, x, y, width, height)

    static bool resControl = nepCfg.getb("Enable resolution control");
    static bool newFxaaBloom = nepCfg.getb("Enable new FXAA and bloom");
    static bool shadowControl = nepCfg.getb("Enable shadow control");

    if(resControl && tex != checkSizeExcludeTex && checkSize(width, height) &&
        (!safeMode || safeMode && tex < 20)) {
        width = targetWidth;
        height = targetHeight;
    }
    else if(newFxaaBloom && checkIsBloom(width, height))
        setBloomSize(&width, &height);
    else if(shadowControl && checkIsShadow(width, height) && (
        nepGame == NEP_RB1 && (tex == 0 || tex == 8 || tex == 9) ||
        nepGame == NEP_RB2 && (tex == 0 || tex == 8 || tex == 9) ||
        nepGame == NEP_RB3 && tex == 0)) {
        width = targetShadowSize;
        height = targetShadowSize;
    }
        
    // Maps/UI
    if (resControl && ((x > 0 && y > 0) || y < 0)) {
        x = x * targetWidth / DEF_W;
        y = y * targetHeight / DEF_H;
        width = width * targetWidth / DEF_W;
        height = height * targetHeight / DEF_H;
    }

    auto ret = TGLFUNC_CALL(glScissor, x, y, width, height);
    NEP_LOGV("glScissor exit\n");
    return ret;
}

GLPROXY_EXTERN PROC GLPROXY_DECL wglGetProcAddress(LPCSTR funcName) {
    static GLProxy::TGLFunc<PROC, LPCSTR> TGLFUNC_DECL(wglGetProcAddress);
    static bool vsyncControl = nepCfg.getb("Enable VSync control");
    NEP_LOGV("wglGetProcAddress: %s\n", funcName)
    if (strcmp(funcName, "glRenderbufferStorageEXT") == 0) {
        glRenderbufferStorageEXT_real = (glRenderbufferStorageEXT_t)TGLFUNC_CALL(wglGetProcAddress, funcName);
        return (PROC)glRenderbufferStorageEXT;
    }
    else if (vsyncControl && strcmp(funcName, "wglSwapIntervalEXT") == 0) {
        wglSwapIntervalEXT_real = (wglSwapIntervalEXT_t)TGLFUNC_CALL(wglGetProcAddress, funcName);
        return (PROC)wglSwapIntervalEXT;
    }

    return TGLFUNC_CALL(wglGetProcAddress, funcName);
}