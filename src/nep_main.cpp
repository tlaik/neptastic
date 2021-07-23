#include "defs.h"
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <Psapi.h>
#include "subhook.h"
#include "nep_main.h"
#include "nep_hooks.h"
#include "nep_config.h"

NepGame nepGame = NEP_UNKNOWN_GAME;
FILE* nepLog = NULL;

typedef void* (*malloc_t)(size_t size);
malloc_t malloc_real;
subhook_t malloc_hook;
void* malloc_custom(size_t size) {
    subhook_remove(malloc_hook);

    // Preallocate early - RB2 requests this chunk late into the start and fails to find continuous memory of this size if shadows/render are too hi-res
    static void* b4chunk = malloc_real(0xB400000);

    if(size == 0xB400000) {
        if(!b4chunk)
            NEP_LOG("B4 Chunk requested more than once!\n")
        else {
            NEP_LOG("Returning preallocated chunk @ %#010x\n", (uint32_t)b4chunk)
            void* tmp = b4chunk;
            b4chunk = NULL;
            return tmp;
        }
        fflush(nepLog);
    }

    void* res = malloc_real(size);
    if(!res) {
        MessageBoxA(NULL, "Out of memory, time to die", "Nepu!", MB_ICONWARNING | MB_OK);
        NEP_LOG("Allocation of %u bytes failed\n", size)
        fflush(nepLog);
    }

    subhook_install(malloc_hook);

    return res;
}

NepGame getNepGame() {
    if(GetModuleHandleA("NeptuniaReBirth2.exe"))
        return NEP_RB2;
    if(GetModuleHandleA("NeptuniaReBirth3.exe"))
        return NEP_RB3;
    return NEP_UNKNOWN_GAME;
}

bool nep_main() {
    static bool initialized = false;
    if (!initialized) {
        if((nepGame = getNepGame()) == NEP_UNKNOWN_GAME) {
            MessageBoxA(NULL, "Unknown game, was expecting Nep RB2 or RB3!\n", "Nepu!", MB_OK | MB_ICONERROR);
            ExitProcess(0);
        }

        nepLog = fopen(NEP_PATH("nep.log"), "w");
        NEP_LOG("Commence the Nep log for %s\n", nepGame == NEP_RB2 ? "RB2" : (nepGame == NEP_RB3 ? "RB3" : ""))

        cgCreateProgram_real = (cgCreateProgram_t)GetProcAddress(GetModuleHandleA("cg.dll"), "cgCreateProgram");
        cgCreateProgram_hook = subhook_new((void*)cgCreateProgram_real, (void*)cgCreateProgram, SUBHOOK_NONE);
        subhook_install(cgCreateProgram_hook);

        if(nepGame == NEP_RB2) {
            // Literally breaking into malloc to make this ass of a game work with hi-res shadows
            malloc_real = (malloc_t)GetProcAddress(GetModuleHandleA("MSVCR120.dll"), "malloc");
            malloc_hook = subhook_new((void*)malloc_real, (void*)malloc_custom, SUBHOOK_NONE);
            subhook_install(malloc_hook);
        }

        nepCfg.loadConfig();

        initialized = true;
    }

    return true;
}