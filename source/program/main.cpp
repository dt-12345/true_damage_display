#include "weapon.h"
#include "config.h"
#include "binaryoffsethelper.h"

#include "lib.hpp"
#include "utils.hpp"

#include <cmath>
#include <cstring>

u64 main_offset;

HOOK_DEFINE_REPLACE(CalcWeaponDamage) {
    static int Callback(void* _this) {
        if (version == 0) {
            return reinterpret_cast<WeaponComponent100*>(_this)->calcAttack();
        } else {
            return reinterpret_cast<WeaponComponent*>(_this)->calcAttack();
        }
    }
};

HOOK_DEFINE_REPLACE(CalcAttachmentDamage) {
    static int Callback(void* _this) {
        if (version == 0) {
            return reinterpret_cast<WeaponComponent100*>(_this)->calcAttachmentAttack();
        } else {
            return reinterpret_cast<WeaponComponent*>(_this)->calcAttachmentAttack();
        }
    }
};

// calcAttack is inlined the WeaponComponent's sensor register function (0x71011117d4 on 1.2.1) so we need to manually fix it
HOOK_DEFINE_INLINE(FixWeaponDamage) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (version == 0) {
            ctx->W[8] = reinterpret_cast<WeaponComponent100*>(ctx->X[20])->calcAttack();
        } else {
            ctx->W[8] = reinterpret_cast<WeaponComponent*>(ctx->X[20])->calcAttack();
        }
    }
};

// fun fact, the UI does (fuse * strong fusion + zonai boost) while the actual damage calculation does ((fuse + zonai boost) * strong fusion)
// I will not bother to fix this because there is no case where both apply without mods
HOOK_DEFINE_INLINE(UIAttachmentDamage) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        // these should never be null because this hook exists within a conditional where it is checked
        PouchActorInfoRow* pai_row = reinterpret_cast<PouchActorInfoRow*>(ctx->X[22]);
        AttachmentActorInfoRow* aai_row = reinterpret_cast<AttachmentActorInfoRow*>(ctx->X[0]);

        int attachment_damage;
        if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "LargeSword", 10) == 0) {
            attachment_damage = static_cast<int>(std::floor(aai_row->attachment_dmg * 1.0526316));
        } else if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "Spear", 5) == 0) {
            attachment_damage = static_cast<int>(std::ceil(aai_row->attachment_dmg * 0.7536613));
        } else {
            attachment_damage = aai_row->attachment_dmg;
        }

        // another difference is the actual damage calculation does ceiling here but the UI normally does static_cast<int> which truncates
        // I will fix this to be consistent
        ctx->W[8] = static_cast<int>(std::ceil(static_cast<float>(attachment_damage) * pai_row->attach_mul_value));
    }
};
HOOK_DEFINE_INLINE(UIAttachmentDamage1) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        PouchActorInfoRow* pai_row = reinterpret_cast<PouchActorInfoRow*>(ctx->X[23]);
        AttachmentActorInfoRow* aai_row = reinterpret_cast<AttachmentActorInfoRow*>(ctx->X[0]);

        int attachment_damage;
        if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "LargeSword", 10) == 0) {
            attachment_damage = static_cast<int>(std::floor(aai_row->attachment_dmg * 1.0526316));
        } else if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "Spear", 5) == 0) {
            attachment_damage = static_cast<int>(std::ceil(aai_row->attachment_dmg * 0.7536613));
        } else {
            attachment_damage = aai_row->attachment_dmg;
        }

        ctx->W[8] = static_cast<int>(std::ceil(static_cast<float>(attachment_damage) * pai_row->attach_mul_value));
    }
};
HOOK_DEFINE_INLINE(UIAttachmentDamage2) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        PouchActorInfoRow* pai_row = reinterpret_cast<PouchActorInfoRow*>(ctx->X[0]);
        AttachmentActorInfoRow* aai_row = reinterpret_cast<AttachmentActorInfoRow*>(ctx->X[1]);

        int attachment_damage;
        if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "LargeSword", 10) == 0) {
            attachment_damage = static_cast<int>(std::floor(aai_row->attachment_dmg * 1.0526316));
        } else if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "Spear", 5) == 0) {
            attachment_damage = static_cast<int>(std::ceil(aai_row->attachment_dmg * 0.7536613));
        } else {
            attachment_damage = aai_row->attachment_dmg;
        }

        ctx->W[23] = static_cast<int>(std::ceil(static_cast<float>(attachment_damage) * pai_row->attach_mul_value));
        ctx->W[24] = 0; // get rid of the ceiling add value because we called std::ceil ourselves
    }
};

// set the WeaponType to SmallSword so the UI damage is calculated as such
HOOK_DEFINE_INLINE(SetWeaponType) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        ctx->W[8] = static_cast<int>(WeaponType::SmallSword);
    }
};

extern "C" void exl_main(void* x0, void* x1) {
    exl::hook::Initialize();

    main_offset = exl::util::modules::GetTargetStart();
    version = InitializeAppVersion();

    if (version == 0xffffffff) {
        EXL_ABORT(0x69);
    }

    #define INSTALL(CLASS, OFFSET)      \
    if (OFFSET != 0) {                  \
        CLASS::InstallAtOffset(OFFSET); \
    }

    INSTALL(CalcWeaponDamage, sWeaponDamageOffsets1[version])
    INSTALL(CalcWeaponDamage, sWeaponDamageOffsets2[version])
    INSTALL(CalcAttachmentDamage, sAttachmentDamageOffsets[version])
    INSTALL(FixWeaponDamage, sFixWeaponDamageOffsets[version])
    INSTALL(UIAttachmentDamage, sUIAttachmentOffsets1[version])
    INSTALL(UIAttachmentDamage1, sUIAttachmentOffsets2[version])
    INSTALL(UIAttachmentDamage2, sUIAttachmentOffsets3[version])
    INSTALL(SetWeaponType, sSetWeaponTypeOffsets1[version])
    INSTALL(SetWeaponType, sSetWeaponTypeOffsets2[version])
    INSTALL(SetWeaponType, sSetWeaponTypeOffsets3[version])

    #undef INSTALL

    getAttachZonauAttackValue = reinterpret_cast<GetAttack*>(exl::util::modules::GetTargetOffset(sZonauAttachValueOffsets[version]));
    getAttachMulAttackValue = reinterpret_cast<GetAttack*>(exl::util::modules::GetTargetOffset(sAttachMulValueOffsets[version]));
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}