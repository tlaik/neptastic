#pragma once

enum NepGame {
	NEP_RB1,
	NEP_RB2,
	NEP_RB3,
	NEP_UNKNOWN_GAME
};

// RB3 dll loading is retarded thanks to ; in path - opengl32.dll needs to be placed in a "Birth3" subdirectory to get picked up on start.
#define NEP_PATH(path) nepGame == NEP_RB3 ? "Birth3\\" path : path
#define NEP_LOG(...) { fprintf(nepLog, __VA_ARGS__); fflush(nepLog); }

bool nep_main();

extern NepGame nepGame;
extern int nepBase;
extern const char* nepGameName[NEP_UNKNOWN_GAME];
extern FILE* nepLog;
extern bool safeMode;