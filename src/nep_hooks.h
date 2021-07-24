#pragma once

#include "subhook.h"

// Rendering is done at 1920 x 1088 (sic) resolution by default. What the fuck.
#define DEF_W 1920
#define DEF_H 1088
#define DEF_SHADOW_RB1 1024
#define DEF_SHADOW_RB2 2048
#define DEF_SHADOW_RB3 512  // They actually dropped shadow res in RB3 to miserable 512x512. What. The. Fuck.
#define SHADOW_RES_CFG 1024 // Base custom shadow resolution for all games, scaled by config value (1.0, 2.0 etc.)

typedef int (*cgCreateProgram_t)(int context, int program_type, const char* program, int profile, const char* entry, const char** args);

extern cgCreateProgram_t cgCreateProgram_real;
extern subhook_t cgCreateProgram_hook;

int cgCreateProgram(int context, int program_type, const char* program, int profile, const char* entry, const char** args);

extern int wndWidth, wndHeight;
extern int targetWidth;
extern int targetHeight;
extern int targetShadowSize;

extern HWND wnd;