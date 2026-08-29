#include "config.h"
#include "weapon.h"

#include <cmath>

#include "utils.hpp"

static float getAttachMulAttackValueThunk(void* cmp) {
    if (version < 6)
        return getAttachMulAttackValue(cmp);
    WeaponComponent* comp = reinterpret_cast<WeaponComponent*>(cmp);
    if (!comp->is_attached)
        return 1.f;
    return *getAttachMulAttackValue1(comp->document->typed_param);
}

// replaces 0x7101674bc4 on 1.2.1
int WeaponComponent::calcAttachmentAttack() {
    int additional_atk;

    // exclude zonai attack up + the gerudo weapon boost from the weapon type multiplier
    switch (weapon_type) {
        case WeaponType::LargeSword:
            additional_atk = static_cast<int>(std::floor(attachment_dmg * 1.0526316));
            break;
        case WeaponType::Spear:
            additional_atk = static_cast<int>(std::ceil(attachment_dmg * 0.7536613));
            break;
        default:
            additional_atk = attachment_dmg;
            break;
    }

    additional_atk += static_cast<int>(getAttachZonauAttackValue(this));
    additional_atk = static_cast<int>(std::ceil(static_cast<float>(additional_atk) * getAttachMulAttackValueThunk(this)));
    if (ex_effect == ExEffectType::AttackUp || ex_effect == ExEffectType::AttackUpPlus) {
        additional_atk += ex_effect_value;
    }

    return additional_atk;
}

// replaces 0x7101111f6c and 0x71015714f4 on 1.2.1
int WeaponComponent::calcAttack() {
    return base_attack + awakened_attack + calcAttachmentAttack();
}

int WeaponComponent100::calcAttachmentAttack() {
    int additional_atk;

    // exclude zonai attack up + the gerudo weapon boost from the weapon type multiplier
    switch (weapon_type) {
        case WeaponType::LargeSword:
            additional_atk = static_cast<int>(std::floor(attachment_dmg * 1.0526316));
            break;
        case WeaponType::Spear:
            additional_atk = static_cast<int>(std::ceil(attachment_dmg * 0.7536613));
            break;
        default:
            additional_atk = attachment_dmg;
            break;
    }

    additional_atk += static_cast<int>(getAttachZonauAttackValue(this));
    additional_atk = static_cast<int>(std::ceil(static_cast<float>(additional_atk) * getAttachMulAttackValueThunk(this)));
    if (ex_effect == ExEffectType::AttackUp || ex_effect == ExEffectType::AttackUpPlus) {
        additional_atk += ex_effect_value;
    }

    return additional_atk;
}

int WeaponComponent100::calcAttack() {
    return base_attack + awakened_attack + calcAttachmentAttack();
}