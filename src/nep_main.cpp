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
int nepBase = 0;
const char* nepGameName[NEP_UNKNOWN_GAME] = { "RB1", "RB2", "RB3" };
FILE* nepLog = NULL;
bool safeMode = false;

typedef void* (*malloc_t)(size_t size);
malloc_t malloc_real;
subhook_t malloc_hook;
void* malloc_custom(size_t size) {
    subhook_remove(malloc_hook);

    static void* chunk = NULL;
    static size_t chunkSize = nepGame == NEP_RB1 ? 0x9600000 : (nepGame == NEP_RB2 ? 0xB400000 : 0);
    static bool chunkUsed = false;

    if(!chunkUsed && (nepGame == NEP_RB1 || nepGame == NEP_RB2)) {
        // Preallocate early - Game requests this chunk late into the start and can fail to find continuous memory of this size if shadows/render are too hi-res
        if(!chunk) {
            if(nepGame == NEP_RB1) chunk = malloc_real(chunkSize);
            else if (nepGame == NEP_RB2) chunk = malloc_real(chunkSize);
            if(chunk)
                NEP_LOG("Preallocating %u bytes @ %#010x\n", chunkSize, (uint32_t)chunk)
            else
                NEP_LOG("Failed to preallocate %u bytes\n", chunkSize)
        }

        if(size == chunkSize) {
            NEP_LOG("Returning preallocated chunk @ %#010x\n", (uint32_t)chunk)
            void* tmp = chunk;
            chunk = NULL;
            chunkUsed = true;
            return tmp;
        }
    }

    void* res = malloc_real(size);
    if(!res) {
        MessageBoxA(NULL, "Out of memory, time to die", "Nepu!", MB_ICONWARNING | MB_OK);
        NEP_LOG("Allocation of %u bytes failed\n", size)
    }

    subhook_install(malloc_hook);

    return res;
}

NepGame getNepGame() {
    if((nepBase = (int)GetModuleHandleA("NeptuniaReBirth1.exe")) != 0)
        return NEP_RB1;
    if((nepBase = (int)GetModuleHandleA("NeptuniaReBirth2.exe")) != 0)
        return NEP_RB2;
    if((nepBase = (int)GetModuleHandleA("NeptuniaReBirth3.exe")) != 0)
        return NEP_RB3;
    return NEP_UNKNOWN_GAME;
}

bool nep_main() {
    static bool initialized = false;
    if (!initialized) {
        if((nepGame = getNepGame()) == NEP_UNKNOWN_GAME) {
            MessageBoxA(NULL, "Unknown game, was expecting Nep RB1 / RB2 /  RB3!\n", "Nepu!", MB_OK | MB_ICONERROR);
            ExitProcess(0);
        }

        nepLog = fopen(NEP_PATH("nep.log"), "w");
        NEP_LOG("Commence the Nep log for %s\n", nepGameName[nepGame])

        cgCreateProgram_real = (cgCreateProgram_t)GetProcAddress(GetModuleHandleA("cg.dll"), "cgCreateProgram");
        cgCreateProgram_hook = subhook_new((void*)cgCreateProgram_real, (void*)cgCreateProgram, SUBHOOK_NONE);
        subhook_install(cgCreateProgram_hook);

        // Literally breaking into malloc to make this ass of a game work with hi-res shadows
        malloc_real = (malloc_t)GetProcAddress(GetModuleHandleA(nepGame == NEP_RB1 ? "MSVCR110.dll" : "MSVCR120.dll"), "malloc");
        malloc_hook = subhook_new((void*)malloc_real, (void*)malloc_custom, SUBHOOK_NONE);
        subhook_install(malloc_hook);

        nepCfg.loadConfig();
        safeMode = nepCfg.getb("Safe mode");

        initialized = true;
    }

    return true;
}