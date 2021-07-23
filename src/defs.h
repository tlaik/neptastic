#pragma once

// Trim down the WinAPI crap. We also don't want WinGDI.h
// to interfere with our WGL wrapper declarations.
#define NOGDI
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define SUBHOOK_STATIC

#include <windows.h>
#include <string>

#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_RED                            0x1903
#define GL_VERTEX_PROGRAM_ARB             0x8620
#define GL_FRAGMENT_PROGRAM_ARB           0x8804

// We are not including 'WinGDI.h' and 'gl.h', so the
// required types must be redefined in this source file.
#define GLPROXY_NEED_OGL_TYPES
#define GLPROXY_NEED_WGL_STRUCTS

// ========================================================
// Local helper macros:
// ========================================================

// To pass the silly "constant expression" warning from Visual Studio...
#define END_MACRO while (0,0)

// Local log stream output:
//#define Neptastic_LOG(message) do { GLProxy::getLogStream() << message << std::endl; } END_MACRO

// Appends a pair tokens into a single name/identifier.
// Normally used to declared internal/built-in functions and variables.
#define STRING_JOIN2_HELPER(a, b) a ## b
#define STRING_JOIN2(a, b) STRING_JOIN2_HELPER(a, b)

// Code/text to string:
#define STRINGIZE_HELPER(str) #str
#define STRINGIZE(str) STRINGIZE_HELPER(str)

//
// Calling convention used by OGL functions on Windows is stdcall.
// OpenGL is also a C API, so the 'extern C' should be the correct approach.
// However, these qualifiers alone don't seem enough to prevent the linker from
// decorating our function names, so an additional '.def' file is also required.
//
#define GLPROXY_DECL   __stdcall
#define GLPROXY_EXTERN extern "C"

// ================================================================================================
// "Classic OpenGL" and WGL wrappers:
// ================================================================================================

//
// Standard OpenGL data types.
//
// We don't include gl.h to avoid conflicting definitions, so these
// types are defined here in the same way they would be by gl.h.
//
#ifdef GLPROXY_NEED_OGL_TYPES
typedef double         GLclampd;
typedef double         GLdouble;
typedef float          GLclampf;
typedef float          GLfloat;
typedef int            GLint;
typedef int            GLsizei;
typedef short          GLshort;
typedef signed char    GLbyte;
typedef unsigned char  GLboolean;
typedef unsigned char  GLubyte;
typedef unsigned int   GLbitfield;
typedef unsigned int   GLenum;
typedef unsigned int   GLuint;
typedef unsigned short GLushort;
typedef void           GLvoid;
typedef char           GLchar;
#endif // GLPROXY_NEED_OGL_TYPES

//
// WGL structures.
//
// They are defined here because including WinGDI.h would produce
// warnings or even errors about our redefined WGL function proxies.
//
#ifdef GLPROXY_NEED_WGL_STRUCTS
struct PIXELFORMATDESCRIPTOR
{
    WORD  nSize;
    WORD  nVersion;
    DWORD dwFlags;
    BYTE  iPixelType;
    BYTE  cColorBits;
    BYTE  cRedBits;
    BYTE  cRedShift;
    BYTE  cGreenBits;
    BYTE  cGreenShift;
    BYTE  cBlueBits;
    BYTE  cBlueShift;
    BYTE  cAlphaBits;
    BYTE  cAlphaShift;
    BYTE  cAccumBits;
    BYTE  cAccumRedBits;
    BYTE  cAccumGreenBits;
    BYTE  cAccumBlueBits;
    BYTE  cAccumAlphaBits;
    BYTE  cDepthBits;
    BYTE  cStencilBits;
    BYTE  cAuxBuffers;
    BYTE  iLayerType;
    BYTE  bReserved;
    DWORD dwLayerMask;
    DWORD dwVisibleMask;
    DWORD dwDamageMask;
};
struct LAYERPLANEDESCRIPTOR
{
    WORD  nSize;
    WORD  nVersion;
    DWORD dwFlags;
    BYTE  iPixelType;
    BYTE  cColorBits;
    BYTE  cRedBits;
    BYTE  cRedShift;
    BYTE  cGreenBits;
    BYTE  cGreenShift;
    BYTE  cBlueBits;
    BYTE  cBlueShift;
    BYTE  cAlphaBits;
    BYTE  cAlphaShift;
    BYTE  cAccumBits;
    BYTE  cAccumRedBits;
    BYTE  cAccumGreenBits;
    BYTE  cAccumBlueBits;
    BYTE  cAccumAlphaBits;
    BYTE  cDepthBits;
    BYTE  cStencilBits;
    BYTE  cAuxBuffers;
    BYTE  iLayerPlane;
    BYTE  bReserved;
    COLORREF crTransparent;
};
struct GLYPHMETRICSFLOAT
{
    float gmfBlackBoxX;
    float gmfBlackBoxY;
    struct
    {
        float x;
        float y;
    } gmfptGlyphOrigin;
    float gmfCellIncX;
    float gmfCellIncY;
};
struct WGLSWAP
{
    HDC  hdc;
    UINT flags;
};
/* pixel types */
#define PFD_TYPE_RGBA        0
#define PFD_TYPE_COLORINDEX  1

/* layer types */
#define PFD_MAIN_PLANE       0
#define PFD_OVERLAY_PLANE    1
#define PFD_UNDERLAY_PLANE   (-1)
/* PIXELFORMATDESCRIPTOR flags */
#define PFD_DOUBLEBUFFER            0x00000001
#define PFD_STEREO                  0x00000002
#define PFD_DRAW_TO_WINDOW          0x00000004
#define PFD_DRAW_TO_BITMAP          0x00000008
#define PFD_SUPPORT_GDI             0x00000010
#define PFD_SUPPORT_OPENGL          0x00000020
#define PFD_GENERIC_FORMAT          0x00000040
#define PFD_NEED_PALETTE            0x00000080
#define PFD_NEED_SYSTEM_PALETTE     0x00000100
#define PFD_SWAP_EXCHANGE           0x00000200
#define PFD_SWAP_COPY               0x00000400
#define PFD_SWAP_LAYER_BUFFERS      0x00000800
#define PFD_GENERIC_ACCELERATED     0x00001000
#define PFD_SUPPORT_DIRECTDRAW      0x00002000
#define PFD_DIRECT3D_ACCELERATED    0x00004000
#define PFD_SUPPORT_COMPOSITION     0x00008000
#endif // GLPROXY_NEED_WGL_STRUCTS

namespace GLProxy
{
    static std::string getRealGLLibPath();
    static HMODULE getSelfModuleHandle();
    DECLSPEC_NORETURN static void fatalError(const std::string& message);
    class OpenGLDll;
    void* getRealGLFunc(const char* funcName);

    // ========================================================
    // GL function pointers database:
    // ========================================================

    //
    // Registry for the real functions from the GL DLL.
    //
    struct GLFuncBase
    {
        const char* name;       // Pointer to static string. OGL function name, like "glEnable".
        const GLFuncBase* next; // Pointer to next static instance in the global list.
    };

    // Linked list of TGLFuncs, pointing to the actual OpenGL DLL methods.
    static GLFuncBase* g_RealGLFunctions = nullptr;

    //
    // Each function requires a different signature...
    // These are always declared as static instances.
    //
    template<class RetType, class... ParamTypes>
    struct TGLFunc : GLFuncBase
    {
        typedef RetType(GLPROXY_DECL* PtrType)(ParamTypes...);
        PtrType funcPtr; // Pointer to a GL function inside the actual OpenGL DLL.

        TGLFunc(const char* funcName)
        {
            name = funcName;
            funcPtr = reinterpret_cast<PtrType>(getRealGLFunc(funcName));

            // Link to the global list:
            this->next = g_RealGLFunctions;
            g_RealGLFunctions = this;
        }
    };
}