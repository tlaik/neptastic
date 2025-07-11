
// ================================================================================================
// -*- C++ -*-
// File: opengl_proxy.cpp
// Author: Guilherme R. Lampert
// Created on: 22/11/15
// Brief: GLProxy intercepts all calls to the real OpenGL library.
//
// Source code licensed under the MIT license.
// Copyright (C) 2015 Guilherme R. Lampert
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that this copyright text
// is included in the resulting source code.
// ================================================================================================

#include "defs.h"
#include "def_funcs.h"
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include "nep_main.h"
#include "nep_config.h"

// ========================================================
// GLProxy utilities:
// ========================================================

namespace GLProxy
{

static std::string getRealGLLibPath()
{
    char defaultGLLibName[1024] = {'\0'};
    GetSystemDirectoryA(defaultGLLibName, sizeof(defaultGLLibName));

    std::string result;
    if (defaultGLLibName[0] != '\0')
    {
        result += defaultGLLibName;
        result += "\\opengl32.dll";
    }
    else // Something wrong... Try a hardcoded path...
    {
        result = "C:\\windows\\system32\\opengl32.dll";
    }
    return result;
}

static HMODULE getSelfModuleHandle()
{
    //
    // This is somewhat hackish, but should work.
    // We try to get this module's address from the address
    // of one of its functions, this very function actually.
    // Worst case it fails and we return null.
    //
    // There's also the '__ImageBase' hack, but that seems even more precarious...
    // http://stackoverflow.com/a/6924293/1198654
    //
    HMODULE selfHMod = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                       GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCSTR)&getSelfModuleHandle,
                       &selfHMod);
    return selfHMod;
}

DECLSPEC_NORETURN static void fatalError(const std::string & message)
{
    MessageBoxA(nullptr, message.c_str(), "GLProxy Fatal Error", MB_OK | MB_ICONERROR);

    std::exit(EXIT_FAILURE);
}

// ========================================================
// class OpenGLDll:
//  Simple helper class to manage loading the real OpenGL
//  Dynamic Library and fetching function pointers from it.
// ========================================================

class OpenGLDll final
{
    HMODULE     dllHandle;

public:

    // Not copyable.
    OpenGLDll(const OpenGLDll &) = delete;
    OpenGLDll & operator = (const OpenGLDll &) = delete;

    OpenGLDll()
        : dllHandle{ nullptr }
    {
        load();
    }

    ~OpenGLDll()
    {
        unload();
    }

    void load()
    {
        if (isLoaded())
        {
            fatalError("Real OpenGL DLL is already loaded!");
        }

        const char* override = nepCfg.gets("Override opengl dll name");
        if (override && override[0])
        {
            NEP_LOGV("Override enabled\n");
            dllHandle = LoadLibraryA(override);

            if (dllHandle)
            {
                NEP_LOGI("Using %s instead of opengl32.dll\n", override);
                return;
            }
        }

        const auto glDllFilePath = getRealGLLibPath();

        dllHandle = LoadLibraryExA(glDllFilePath.c_str(), nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (dllHandle == nullptr)
        {
            fatalError("GLProxy unable to load the real OpenGL DLL!\nError code: " + GetLastError());
        }

        const auto selfHMod = getSelfModuleHandle();
        if (dllHandle == selfHMod)
        {
            fatalError("GLProxy trying to load itself as the real opengl32.dll!");
        }

        NEP_LOGI("Using system's opengl32.dll\n");
    }

    void unload()
    {
        if (isLoaded())
        {
            FreeLibrary(dllHandle);
            dllHandle = nullptr;
        }
    }

    bool isLoaded() const
    {
        return dllHandle != nullptr;
    }

    void * getFuncPtr(const char * funcName) const
    {
        if (!isLoaded())
        {
            //GLProxy_LOG("Error! Real opengl32.dll not loaded. Can't get function " << funcName);
            return nullptr;
        }

        auto fptr = GetProcAddress(dllHandle, funcName);
        if (fptr == nullptr)
        {
            //GLProxy_LOG("Error! Unable to find " << funcName);
        }

        return reinterpret_cast<void *>(fptr);
    }

    // Just one instance per process.
    // Also only attempt to load the DLL on the first reference.
    static OpenGLDll & getInstance()
    {
        static OpenGLDll glDll;
        return glDll;
    }
};

void * getRealGLFunc(const char * funcName)
{
    auto & glDll = OpenGLDll::getInstance();
    void * addr  = glDll.getFuncPtr(funcName);
    return addr;
}
} // namespace GLProxy {}

// ========================================================
// DllMain:
//  Note: Threads are not supported.
//  Probably a non issue, since OpenGL is single-threaded.
// ========================================================

BOOL WINAPI DllMain(HINSTANCE /* hInstDll */, DWORD reasonForDllLoad, LPVOID /* reserved */)
{
    switch (reasonForDllLoad)
    {
    case DLL_PROCESS_ATTACH :
        //GLProxy_LOG("\nDllMain: DLL_PROCESS_ATTACH\n");
        break;

    case DLL_PROCESS_DETACH :
        //GLProxy_LOG("\nDllMain: DLL_PROCESS_DETACH\n");
        break;

    default :
        break;
    } // switch (reasonForDllLoad)

    nep_main();

    return TRUE;
}