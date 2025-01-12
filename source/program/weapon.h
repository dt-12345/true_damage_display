#pragma once

#include <basis/seadTypes.h>

enum class WeaponType : u32 {
    None, SmallSword, LargeSword, Spear, Bow
};

enum class ExEffectType : u32 {
    None, AttackUp, AttackUpPlus, DurabilityUp, DurabilityUpPlus, FinishBlow,
    LongThrow, RapidFire, ThreeWayZoom, FiveWay, GuardUp, GuardUpPlus
};

struct WeaponComponent {
    char _00[0x218];
    int attachment_dmg;
    char _21c[0x2dc];
    ExEffectType ex_effect;
    int ex_effect_value;
    char _500[0x27c];
    WeaponType weapon_type;
    char _780[0x64];
    int base_attack;
    int awakened_attack;

    int calcAttack();
    int calcAttachmentAttack();
};

using GetAttack = float (void*); // should be WeaponComponent* but this is easier
inline GetAttack* getAttachZonauAttackValue = nullptr;
inline GetAttack* getAttachMulAttackValue = nullptr;

struct PouchActorInfoRow {
    char _00[0xe0];
    const char* weapon_type;
    char _e8[0x14];
    float attach_mul_value;
};
static_assert(offsetof(PouchActorInfoRow, attach_mul_value) == 0xfc);

struct AttachmentActorInfoRow {
    char _00[0x40];
    int attachment_dmg;
};

// handling version differences in a single binary so here we go, 1.0.0 just had to be different smh

// versions 1.0.0 only
struct WeaponComponent100 {
    char _00[0x218];
    int attachment_dmg;
    char _21c[0x2d8];
    ExEffectType ex_effect;
    int ex_effect_value;
    char _4fc[0x278];
    WeaponType weapon_type;
    char _778[0x64];
    int base_attack;
    int awakened_attack;

    int calcAttack();
    int calcAttachmentAttack();
};