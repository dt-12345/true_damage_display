#pragma once

#include "types.h"

inline u32 version;

// for reference, an offset of 0 usually means that hook is unnecessary for that version (bc the function wasn't inlined or whatever)

// vtable function
static constexpr u64 sWeaponDamageOffsets1[] = {
    0x010f9474, 0x0111c33c, 0x01127cc4, 0x01123460, 0x01121ff4, 0x01111f6c, 0, 0, 0, 0,
};

// not vtable function
static constexpr u64 sWeaponDamageOffsets2[] = {
    0x01544bbc, 0x015850fc, 0x01587128, 0x015778cc, 0 /* does not exist */, 0x015714f4, 0, 0, 0, 0,
};

static constexpr u64 sAttachmentDamageOffsets[] = {
    0x0163e38c, 0x01685314, 0x016872c4, 0x01679f3c, 0x01666ee0, 0x01674bc4, 0x00b94a98, 0x00b346c0, 0x00b26fbc, 0x00b21330,
};

static constexpr u64 sFixWeaponDamageOffsets[] = {
    0x010f8e30, 0x0111bcf4, 0x0112767c, 0x01122e1c, 0, 0x01111924, 0, 0, 0, 0,
};

// x0 and x22
static constexpr u64 sUIAttachmentOffsets1[] = {
    0x0175abd0, 0x017a53b0, 0x017a5f90, 0x01799ae0, 0x01785cf0, 0x01795740, 0x01da7dcc, 0x01d99d4c, 0x01d98b8c, 0x01d98b8c,
};

// x0 and x23
static constexpr u64 sUIAttachmentOffsets2[] = {
    0x0175afec, 0x017a57cc, 0x017a63ac, 0x01799efc, 0x0178610c, 0x01795b5c, 0x01da8354, 0x01d9a2d4, 0x01d99114, 0x01d9cbf4,
};

// w23 and w24
static constexpr u64 sUIAttachmentOffsets3[] = {
    0x01759cd4, 0x017a44b4, 0x017a5094, 0x01798be4, 0x01784df4, 0x01794844, 0x01da68fc, 0x01d9887c, 0x01d976bc, 0x01d9b19c,
};

// goes with ui attachment offsets 1
static constexpr u64 sSetWeaponTypeOffsets1[] = {
    0x0175a868, 0x017a5048, 0x017a5c28, 0x01799778, 0x01785988, 0x017953d8, 0x01da7ce4, 0x01d99c64, 0x01d98aa4, 0x01d9c588,
};

// goes with ui attachment offsets 2
static constexpr u64 sSetWeaponTypeOffsets2[] = {
    0x0175ae5c, 0x017a563c, 0x017a621c, 0x01799d6c, 0x01785f7c, 0x017959cc, 0x01da82a8, 0x01d9a228, 0x01d99068, 0x01d9cb4c,
};

// goes with ui attachment offsets 3
static constexpr u64 sSetWeaponTypeOffsets3[] = {
    0x01759c40, 0x017a4420, 0x017a5000, 0x01798b50, 0x01784d60, 0x017947b0, 0x01da6720, 0x01d986a0, 0x01d974e0, 0x01d9afc4,
};

static constexpr u64 sZonauAttachValueOffsets[] = {
    0x010f921c, 0x0111c0e4, 0x01127a6c, 0x0112320c, 0x01667024, 0x01111d14, 0x00b94dec, 0x00b34a14, 0x00b27310, 0x00b21684,
};

static constexpr u64 sAttachMulValueOffsets[] = {
    0x010f8fe8, 0x0111beb0, 0x01127838, 0x01122fd8, 0x01122144, 0x01111ae0, 0x00e1b554, 0x00e18734, 0x00e181e4, 0x00e17874,
};

static constexpr u64 sDisableSaveOffsets[] = {
    0x01a74f50, 0x01ad0e0c, 0x01ace5fc, 0x01ac4f7c, 0x01ab6df4, 0x01ac1fcc, 0x02123b54, 0x021137f8, 0x021133b8, 0x02118e5c,
};

static constexpr u64 sGameBalanceModuleOffsets[] = {
    0x045d6770, 0x046b1bc8, 0x046b9af8, 0x046abf48, 0x046a02e8, 0x046af328, 0x03a55670, 0x03a50670, 0x03a52670, 0x03a64670,
};

#include <array>
#include <cstdint>

inline constexpr const std::array<uintptr_t, 10> cEnumNameOffsets = {
    0, 0x04636798, 0x0463e6d8, 0x04630b08, 0x04624eb0, 0x04633ea8, 0, 0, 0, 0,
};

inline constexpr const std::array<uintptr_t, 10> cFixPtr1Offsets = {
    0, 0, 0, 0, 0, 0, 0x01af31f4, 0x01ae6044, 0x01ae2b9c, 0x01ae2d6c,
};

inline constexpr const std::array<uintptr_t, 10> cFixPtr2Offsets = {
    0, 0, 0, 0, 0, 0, 0x01af33a0, 0x01ae61f0, 0x01ae2d48, 0x01ae2f18,
};

inline constexpr const std::array<uintptr_t, 10> cExtraCompare1Offsets = {
    0, 0, 0, 0, 0, 0, 0x01af33d4, 0x01ae6224, 0x01ae2d7c, 0x01ae2f4c,
};

inline constexpr const std::array<uintptr_t, 10> cExtraCompare2Offsets = {
    0, 0, 0, 0, 0, 0, 0x01af33dc, 0x01ae622c, 0x01ae2d84, 0x01ae2f54,
};

inline constexpr const std::array<uintptr_t, 10> cCompareXOffsets = {
    0, 0x0155e110, 0x01560570, 0x01550e5c, 0x0153db64, 0x0154a894, 0x01af3398, 0x01ae61e8, 0x01ae2d40, 0x01ae2f10,
};

inline constexpr const std::array<uintptr_t, 10> cCompareWOffsets = {
    0, 0x0155df84, 0x0156037c, 0x01550cd0, 0x0153d9d8, 0x0154a708, 0x01af31ac, 0x01ae5ffc, 0x01ae2b54, 0x01ae2d24,
};

inline constexpr const std::array<uintptr_t, 10> cEvalTgHitOffsets = {
    0, 0x0170c440, 0x0170d1f0, 0x01700b20, 0x016ed340, 0x016fc7f0, 0x01cde654, 0x01cd03d4, 0x01ccf53c, 0x01cd263c,
};

inline constexpr const std::array<uintptr_t, 10> cBreakHeartOffsets = {
    0, 0x006ab8d0, 0x00995d30, 0x006a4b68, 0x0066867c, 0x0064c830, 0x00096b0c, 0x004ff6fc, 0x00522584, 0x00441628,
};

inline constexpr const std::array<uintptr_t, 10> cBreakHeartUIOffsets = {
    0, 0x00c26c60, 0x00b2a0c0, 0x00b3c254, 0x00a7818c, 0x00b77a50, 0x0083f2e8, 0x00845678, 0x0066c6c8, 0x00724748,
};

inline constexpr const std::array<uintptr_t, 10> cPlayDisappearOffsets = {
    0, 0x010ddb98, 0x010eaa6c, 0x010df1cc, 0x010c89d0, 0x010cfe54, 0x00b49c04, 0x00b43560, 0x00b2e2f4, 0x00b645b8,
};

inline constexpr const std::array<uintptr_t, 10> cPlayBreakOffsets = {
    0, 0x010dde38, 0x010eabe4, 0x010df344, 0x010c8c70, 0x010cffcc, 0x00b4b310, 0x00b44c6c, 0x00b2fa00, 0x00b65cc4,
};

inline constexpr const std::array<uintptr_t, 10> cOverrideFairyOffsets = {
    0, 0x006aa9f0, 0x00994d50, 0x006a3bb8, 0x006676b8, 0x0064b960, 0x00096034, 0x004fec14, 0x00521aa4, 0x00440b64,
};

inline constexpr const std::array<uintptr_t, 10> cPlayNullOffsets = {
    0, 0x010de6a0, 0x010eb414, 0x010dfb74, 0x010c94d8, 0x010d07fc, 0x00b4bac4, 0x00b45420, 0x00b301b4, 0x00b66478,
};

inline constexpr const std::array<uintptr_t, 10> cGetPositionOffsets = {
    0, 0x010deda0, 0x010ebb14, 0x010e0274, 0x010c9bd8, 0x010d0efc, 0, 0, 0, 0,
};

inline constexpr const std::array<uintptr_t, 10> cGameDataMgrOffsets = {
    0, 0, 0, 0, 0, 0, 0x03ac76b0, 0x03ac26b0, 0x03ac46b0, 0x03ad66b0,
};

inline constexpr const std::array<uintptr_t, 10> cGetBoolOffsets = {
    0, 0, 0, 0, 0, 0, 0x00034cc0, 0x000fa748, 0x00011490, 0x0004561c,
};

inline constexpr const std::array<uintptr_t, 10> cPlayHardHeartBreakOffsets = {
    0, 0x010dec98, 0x010eba0c, 0x010e016c, 0x010c9ad0, 0x010d0df4, 0x020fa28c, 0x020e99e8, 0x020e95a8, 0x020ef1d8,
};

inline constexpr const std::array<uintptr_t, 10> cPlayAnimOffsets = {
    0, 0x00e0608c, 0x00e130d8, 0x00dec7e0, 0x00dafca0, 0x00de00bc, 0x00b7f62c, 0x00b82d9c, 0x00b730e8, 0x00b55a58,
};

inline constexpr const std::array<uintptr_t, 10> cStartAnimOffsets = {
    0, 0x00d3b3a4, 0x00d6dc34, 0x00d31d04, 0x00cfb60c, 0x00d25064, 0x00d27350, 0x00d29238, 0x00d24558, 0x00d3b420,
};

inline constexpr const std::array<uintptr_t, 10> cAppendChildOffsets = {
    0, 0x0063d3e0, 0x0063d5a0, 0x0063d670, 0x0063c498, 0x00700480, 0x0000f4a0, 0x000111a4, 0x00241754, 0x00406094,
};

inline constexpr const std::array<uintptr_t, 10> cRemoveChildOffsets = {
    0, 0x00db2f24, 0x00dc63e4, 0x00d96b1c, 0x00da7b80, 0x00d84d30, 0x00636d3c, 0x0065f3cc, 0x007ecbdc, 0x0081b074,
};
