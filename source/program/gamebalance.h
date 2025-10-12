#pragma once

#include "types.h"
#include "config.h"

struct BattleMgr {
    char _00[0x10];
    u32 battleState;
};

struct GameBalanceModule {
    char _00[0x4500];
    BattleMgr battleMgr;
};

struct GameBalanceModule140 {
    char _00[0x4558];
    u32 battleState;
};

inline GameBalanceModule** gGameBalanceModulePtr = nullptr;

inline bool isInBattle() {
    if (version < 6)
        return (gGameBalanceModulePtr && *gGameBalanceModulePtr) ? ((*gGameBalanceModulePtr)->battleMgr.battleState == 1) : false;
    if (gGameBalanceModulePtr && *gGameBalanceModulePtr)
        return reinterpret_cast<GameBalanceModule140*>(*gGameBalanceModulePtr)->battleState == 1;
    return false;
}