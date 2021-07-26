#pragma once

enum NepGame {
	NEP_RB1,
	NEP_RB2,
	NEP_RB3,
	NEP_UNKNOWN_GAME
};

enum NepLogLevel {
	NEP_LOG_OFF,
	NEP_LOG_ERROR,
	NEP_LOG_WARNING,
	NEP_LOG_INFO,
	NEP_LOG_VERBOSE
};

// RB3 dll loading is retarded thanks to ; in path - opengl32.dll needs to be placed in a "Birth3" subdirectory to get picked up on start.
#define NEP_PATH(path) nepGame == NEP_RB3 ? "Birth3\\" path : path
#define _NEP_LOG(ID, ...) { fprintf(nepLog, "[" #ID "]: "); fprintf(nepLog, __VA_ARGS__); fflush(nepLog); }
#define NEP_LOGE(...) { if(nepLogLevel >= NEP_LOG_ERROR) _NEP_LOG(E, __VA_ARGS__); }
#define NEP_LOGW(...) { if(nepLogLevel >= NEP_LOG_WARNING) _NEP_LOG(W, __VA_ARGS__); }
#define NEP_LOGI(...) { if(nepLogLevel >= NEP_LOG_INFO) _NEP_LOG(I, __VA_ARGS__); }
#define NEP_LOGV(...) { if(nepLogLevel >= NEP_LOG_VERBOSE) _NEP_LOG(V,  __VA_ARGS__); }

bool nep_main();

extern NepGame nepGame;
extern int nepBase;
extern const char* nepGameName[NEP_UNKNOWN_GAME];
extern FILE* nepLog;
extern NepLogLevel nepLogLevel;
extern bool safeMode;