#pragma once

#include "types.h"

const char GAME_VERSION_1_0_0[] = "1.0.0";
const char GAME_VERSION_1_1_0[] = "1.1.0";
const char GAME_VERSION_1_1_1[] = "1.1.1";
const char GAME_VERSION_1_1_2[] = "1.1.2";
const char GAME_VERSION_1_2_0[] = "1.2.0";
const char GAME_VERSION_1_2_1[] = "1.2.1";
const char GAME_VERSION_1_4_0[] = "1.4.0";
const char GAME_VERSION_1_4_1[] = "1.4.1";
const char GAME_VERSION_1_4_2[] = "1.4.2";

extern char sAppVersion[0x10];
extern u32  sAppVersionIndex;

u32 InitializeAppVersion();