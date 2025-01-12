#pragma once

#include "types.h"

inline u32 version;

// vtable function
static constexpr u64 sWeaponDamageOffsets1[] = {
    0x010f9474, 0x0111c33c, 0x01127cc4, 0x01123460, 0x01121ff4, 0x01111f6c
};

// not vtable function
static constexpr u64 sWeaponDamageOffsets2[] = {
    0x01544bbc, 0x015850fc, 0x01587128, 0x015778cc, 0 /* does not exist */, 0x015714f4
};

static constexpr u64 sAttachmentDamageOffsets[] = {
    0x0163e38c, 0x01685314, 0x016872c4, 0x01679f3c, 0x01666ee0, 0x01674bc4
};

static constexpr u64 sFixWeaponDamageOffsets[] = {
    0x010f8e30, 0x0111bcf4, 0x0112767c, 0x01122e1c, 0 /* not inlined so unnecessary */, 0x01111924
};

// x0 and x22
static constexpr u64 sUIAttachmentOffsets1[] = {
    0x0175abd0, 0x017a53b0, 0x017a5f90, 0x01799ae0, 0x01785cf0, 0x01795740
};

// x0 and x23
static constexpr u64 sUIAttachmentOffsets2[] = {
    0x0175afec, 0x017a57cc, 0x017a63ac, 0x01799efc, 0x0178610c, 0x01795b5c
};

// w23 and w24
static constexpr u64 sUIAttachmentOffsets3[] = {
    0x01759cd4, 0x017a44b4, 0x017a5094, 0x01798be4, 0x01784df4, 0x01794844
};

// goes with ui attachment offsets 1
static constexpr u64 sSetWeaponTypeOffsets1[] = {
    0x0175a868, 0x017a5048, 0x017a5c28, 0x01799778, 0x01785988, 0x017953d8
};

// goes with ui attachment offsets 2
static constexpr u64 sSetWeaponTypeOffsets2[] = {
    0x0175ae5c, 0x017a563c, 0x017a621c, 0x01799d6c, 0x01785f7c, 0x017959cc
};

// goes with ui attachment offsets 3
static constexpr u64 sSetWeaponTypeOffsets3[] = {
    0x01759c40, 0x017a4420, 0x017a5000, 0x01798b50, 0x01784d60, 0x017947b0
};

static constexpr u64 sZonauAttachValueOffsets[] = {
    0x010f921c, 0x0111c0e4, 0x01127a6c, 0x0112320c, 0x01667024, 0x01111d14
};

static constexpr u64 sAttachMulValueOffsets[] = {
    0x010f8fe8, 0x0111beb0, 0x01127838, 0x01122fd8, 0x01122144, 0x01111ae0
};