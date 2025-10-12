#pragma once

#include "types.h"

inline u32 version;

// for reference, an offset of 0 usually means that hook is unnecessary for that version (bc the function wasn't inlined or whatever)

// vtable function
static constexpr u64 sWeaponDamageOffsets1[] = {
    0x010f9474, 0x0111c33c, 0x01127cc4, 0x01123460, 0x01121ff4, 0x01111f6c, 0, 0, 0,
};

// not vtable function
static constexpr u64 sWeaponDamageOffsets2[] = {
    0x01544bbc, 0x015850fc, 0x01587128, 0x015778cc, 0 /* does not exist */, 0x015714f4, 0, 0, 0,
};

static constexpr u64 sAttachmentDamageOffsets[] = {
    0x0163e38c, 0x01685314, 0x016872c4, 0x01679f3c, 0x01666ee0, 0x01674bc4, 0x00b94a98, 0x00b346c0, 0x00b26fbc,
};

static constexpr u64 sFixWeaponDamageOffsets[] = {
    0x010f8e30, 0x0111bcf4, 0x0112767c, 0x01122e1c, 0, 0x01111924, 0, 0, 0,
};

// x0 and x22
static constexpr u64 sUIAttachmentOffsets1[] = {
    0x0175abd0, 0x017a53b0, 0x017a5f90, 0x01799ae0, 0x01785cf0, 0x01795740, 0x01da7dcc, 0x01d99d4c, 0x01d98b8c,
};

// x0 and x23
static constexpr u64 sUIAttachmentOffsets2[] = {
    0x0175afec, 0x017a57cc, 0x017a63ac, 0x01799efc, 0x0178610c, 0x01795b5c, 0x01da8354, 0x01d9a2d4, 0x01d99114,
};

// w23 and w24
static constexpr u64 sUIAttachmentOffsets3[] = {
    0x01759cd4, 0x017a44b4, 0x017a5094, 0x01798be4, 0x01784df4, 0x01794844, 0x01da68fc, 0x01d9887c, 0x01d976bc,
};

// goes with ui attachment offsets 1
static constexpr u64 sSetWeaponTypeOffsets1[] = {
    0x0175a868, 0x017a5048, 0x017a5c28, 0x01799778, 0x01785988, 0x017953d8, 0x01da7ce4, 0x01d99c64, 0x01d98aa4,
};

// goes with ui attachment offsets 2
static constexpr u64 sSetWeaponTypeOffsets2[] = {
    0x0175ae5c, 0x017a563c, 0x017a621c, 0x01799d6c, 0x01785f7c, 0x017959cc, 0x01da82a8, 0x01d9a228, 0x01d99068,
};

// goes with ui attachment offsets 3
static constexpr u64 sSetWeaponTypeOffsets3[] = {
    0x01759c40, 0x017a4420, 0x017a5000, 0x01798b50, 0x01784d60, 0x017947b0, 0x01da6720, 0x01d986a0, 0x01d974e0,
};

static constexpr u64 sZonauAttachValueOffsets[] = {
    0x010f921c, 0x0111c0e4, 0x01127a6c, 0x0112320c, 0x01667024, 0x01111d14, 0x00b94dec, 0x00b34a14, 0x00b27310,
};

static constexpr u64 sAttachMulValueOffsets[] = {
    0x010f8fe8, 0x0111beb0, 0x01127838, 0x01122fd8, 0x01122144, 0x01111ae0, 0x00e1b554, 0x00e18734, 0x00e181e4,
};

static constexpr u64 sDisableSaveOffsets[] = {
    0x01a74f50, 0x01ad0e0c, 0x01ace5fc, 0x01ac4f7c, 0x01ab6df4, 0x01ac1fcc, 0x02123b54, 0x021137f8, 0x021133b8,
};

static constexpr u64 sGameBalanceModuleOffsets[] = {
    0x045d6770, 0x046b1bc8, 0x046b9af8, 0x046abf48, 0x046a02e8, 0x046af328, 0x03a55670, 0x03a50670, 0x03a52670,
};