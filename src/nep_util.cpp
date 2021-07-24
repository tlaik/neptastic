// Utils used by nep_hooks.cpp
#include "defs.h"
#include "def_funcs.h"
#include "nep_main.h"
#include "nep_hooks.h"
#include "nep_config.h"
#include "nep_util.h"

// Original bloom is done using 4 low res screenshots slapped together to produce blur.
// It looks like shit.
// New bloom does its job in a single pass over one screenshot, 3 smaller textures are minimized and left unused.
const int bloomSize[][2] = {
    961, 545,
    481, 273,
    256, 146,
    128, 72 };

void getNepWindow() {
    while ((wnd = FindWindowExA(NULL, wnd, NULL, NULL)) != NULL) {
        char buf[1024];
        GetWindowTextA(wnd, buf, sizeof(buf));
        if (nepGame == NEP_RB1 && strstr(buf, "Re;Birth1") ||
            nepGame == NEP_RB2 && strstr(buf, "Re;Birth2") ||
            nepGame == NEP_RB3 && strstr(buf, "Re;Birth3")) {
            RECT size;
            GetClientRect(wnd, &size);
            wndWidth = size.right;
            wndHeight = size.bottom;
            NEP_LOG("Window @ %#010x - client size %d x %d\n", (uint32_t)wnd, wndWidth, wndHeight)
            return;
        }
    }
}

void fpsUnlock() {
    const int frameIntervalTarget = 10; // us
    const int ofs[2] = { 0x23A687, 0x2836A9 };

    // What right and proper fix doth not possess a machine code injection?
    int32_t fpsCodeOrig = nepBase + ofs[nepGame];
    int32_t fpsRet = fpsCodeOrig + 5;
    uint8_t* hookBody = NULL;

    // Replaces: 
    // 8B 7E 1C | mov edi, [esi+1C]
    // 85 FF    | test edi, edi
    uint8_t hook[] = { 0xE9, 0, 0, 0, 0 };

    uint8_t hookBodyTemplate[] = {
        0xBF, 0x00, 0x00, 0x00, 0x00, // mov edi, [frame interval]
        0x85, 0xFF,                   // test edi, edi
        0xE9, 0x00, 0x00, 0x00, 0x00  // jmp [original code]
    };

    hookBody = (uint8_t*)malloc(sizeof(hookBodyTemplate));

    for (int i = 0; i < 4; i++)
        hook[1 + i] = (uint8_t)((int32_t)(hookBody - (fpsCodeOrig + 5)) >> 8 * i);

    for (int i = 0; i < 4; i++)
        hookBodyTemplate[1 + i] = (uint8_t)(frameIntervalTarget >> 8 * i);
    for (int i = 0; i < 4; i++)
        hookBodyTemplate[8 + i] = (uint8_t)((fpsRet - (int32_t)(hookBody + sizeof(hookBodyTemplate))) >> 8 * i);

    memcpy(hookBody, hookBodyTemplate, sizeof(hookBodyTemplate));

    DWORD oldFlags;
    VirtualProtect((void*)fpsCodeOrig, sizeof(hook), PAGE_EXECUTE_READWRITE, &oldFlags);
    VirtualProtect((void*)hookBody, sizeof(hookBodyTemplate), PAGE_EXECUTE_READWRITE, &oldFlags);
    // FPS go brrrr
    memcpy((void*)fpsCodeOrig, hook, sizeof(hook));

    NEP_LOG("FPS unlocked\n")
}

void computeSettings() {
    bool sizesComputed = false;
    if(sizesComputed) return;

    targetWidth = (int)(wndWidth * nepCfg.getf("Resolution scaling"));
    targetHeight = (int)(wndHeight * nepCfg.getf("Resolution scaling"));
    targetShadowSize = (int)(SHADOW_RES_CFG * nepCfg.getf("Shadow resolution"));
    NEP_LOG("Resolution: %d x %d, shadow size: %d\n", targetWidth, targetHeight, targetShadowSize)

    sizesComputed = true;
}

void printGlErrors() {
    GLenum err;
    while ((err = glGetError()) != 0) {
        NEP_LOG("GL error: %#06x\n", err)
    }
}

bool checkSize(GLsizei w, GLsizei h) {
    return w == DEF_W && h == DEF_H;
}

bool checkIsBloom(GLsizei w, GLsizei h) {
    for (int i = 0; i < sizeof(bloomSize) / sizeof(bloomSize[0]); i++)
        if (w == bloomSize[i][0] && h == bloomSize[i][1])
            return true;

    return false;
}

void setBloomSize(GLsizei* w, GLsizei* h) {
    if (*w == bloomSize[0][0] && *h == bloomSize[0][1]) {
        *w = 1920;
        *h = 1080;
    }
    else {
        *w = 0;
        *h = 0;
    }
}

// Dynamic shadow covers the area of ~10m around player-controlled nepgirl.
bool checkIsShadow(GLsizei w, GLsizei h) {
    bool res = false;
    switch(nepGame) {
        case NEP_RB1: res = w == DEF_SHADOW_RB1 && h == DEF_SHADOW_RB1; break;
        case NEP_RB2: res = w == DEF_SHADOW_RB2 && h == DEF_SHADOW_RB2; break;
        case NEP_RB3: res = w == DEF_SHADOW_RB3 && h == DEF_SHADOW_RB3; break;
    }
    return res;
}