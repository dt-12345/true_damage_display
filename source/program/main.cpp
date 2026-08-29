#define TRUE_DAMAGE_DISPLAY
// #define NO_SAVE_IN_COMBAT

#ifdef TRUE_DAMAGE_DISPLAY
#   include "weapon.h"
#endif
#ifdef NO_SAVE_IN_COMBAT
#   include "gamebalance.h"
#endif

#include "config.h"
#include "binaryoffsethelper.h"

#include "lib.hpp"
#include "utils.hpp"

#include <cmath>
#include <cstring>

u64 main_offset;

#ifdef TRUE_DAMAGE_DISPLAY
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

// calcAttack is inlined in WeaponComponent's sensor register function (0x71011117d4 on 1.2.1) so we need to manually fix it
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
            attachment_damage = static_cast<int>(std::floor(static_cast<float>(aai_row->attachment_dmg) * 1.0526316));
        } else if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "Spear", 5) == 0) {
            attachment_damage = static_cast<int>(std::ceil(static_cast<float>(aai_row->attachment_dmg) * 0.7536613));
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
        PouchActorInfoRow* pai_row = reinterpret_cast<PouchActorInfoRow*>(version < 6 ? ctx->X[23] : ctx->X[22]);
        AttachmentActorInfoRow* aai_row = reinterpret_cast<AttachmentActorInfoRow*>(ctx->X[0]);

        int attachment_damage;
        if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "LargeSword", 10) == 0) {
            attachment_damage = static_cast<int>(std::floor(static_cast<float>(aai_row->attachment_dmg) * 1.0526316));
        } else if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "Spear", 5) == 0) {
            attachment_damage = static_cast<int>(std::ceil(static_cast<float>(aai_row->attachment_dmg) * 0.7536613));
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
            attachment_damage = static_cast<int>(std::floor(static_cast<float>(aai_row->attachment_dmg) * 1.0526316));
        } else if (pai_row->weapon_type && strncmp(pai_row->weapon_type, "Spear", 5) == 0) {
            attachment_damage = static_cast<int>(std::ceil(static_cast<float>(aai_row->attachment_dmg) * 0.7536613));
        } else {
            attachment_damage = aai_row->attachment_dmg;
        }

        if (version > 5) {
            ctx->W[22] = static_cast<int>(std::ceil(static_cast<float>(attachment_damage) * pai_row->attach_mul_value));
            ctx->W[23] = 0; // get rid of the ceiling add value because we called std::ceil ourselves
        } else {
            ctx->W[23] = static_cast<int>(std::ceil(static_cast<float>(attachment_damage) * pai_row->attach_mul_value));
            ctx->W[24] = 0; // get rid of the ceiling add value because we called std::ceil ourselves
        }
    }
};

// set the WeaponType to SmallSword so the UI damage is calculated as such
HOOK_DEFINE_INLINE(SetWeaponType) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (version > 5)
            ctx->X[8] = ctx->X[11]; // they optimized away the string to enum conversion and just directly do string comparisons
        else
            ctx->W[8] = static_cast<int>(WeaponType::SmallSword);
    }
};

// #include "config.hpp"
// #include "version.hpp"

#include <array>
#include <cmath>

#define DEFINE_ATTR(Name) Name,
enum ExternalDamageAttributes {
#include "damage_attrs.inc"
};
#undef DEFINE_ATTR

#define DEFINE_ATTR(NAME) #NAME,
static constexpr auto cAttributeNames = std::to_array<const char*>({
#include "damage_attrs.inc"
});
#undef DEFINE_ATTR
static_assert(cAttributeNames.size() > 0 && cAttributeNames.size() <= 0x40); // attributes are stored as a 64-bit mask

enum DamageElement {
    Fire,
    Ice,
    Electric,
    Wind,
    Water,
    Light,
    Miasma,
    Confuse,
    Bomb,
};

struct ExternalHitInfo {
    char _00[0x70];
    u16 dmg_element_mask;
};

struct TgHitInfo {
    char _00[0x1b0];
    u64 dmg_attr_mask;
};

// adds Miasma element for MildlyHardMiasma attacks which is required to even consider reducing max life
HOOK_DEFINE_TRAMPOLINE(EvalTgHit) {
    static void Callback(void* calc, void* arg, ExternalHitInfo& info, const TgHitInfo& tg_hit) {
        Orig(calc, arg, info, tg_hit);
        if ((tg_hit.dmg_attr_mask >> MildlyHardMiasma & 1) != 0) {
            info.dmg_element_mask |= 1 << Miasma;
        }
    }
};

struct Life {
    char _00[0x1d0];
    u64 dmg_attr_mask;
};

// makes MildlyHardMiasma pass the same check as HardMiasma for actually reducing max health
HOOK_DEFINE_INLINE(BreakHeart) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        Life* life = reinterpret_cast<Life*>(ctx->X[19]);
        if ((life->dmg_attr_mask >> MildlyHardMiasma & 1) != 0) {
            ctx->W[8] |= 0x10;
        }
    }
};

// makes MildlyHardMiasma be treated the same way as HardMiasma by the UI
HOOK_DEFINE_INLINE(BreakHeartUI) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        Life* life = reinterpret_cast<Life*>(ctx->X[8]);
        if ((life->dmg_attr_mask >> MildlyHardMiasma & 1) != 0) {
            ctx->W[9] |= 0x10;
        }
    }
};

class Animator {
public:
    virtual void* GetRuntimeTypeInfo() const;
    virtual ~Animator();
    // I cannot be bothered to add the correct signatures for all of these
    virtual void UpdateFrame();
    virtual void SetEnabled();
    virtual void Animate();
    virtual void AnimatePane();
    virtual void AnimateMaterial();
    virtual void SetResource();
    virtual void SetResource1();
    virtual void BindPane();
    virtual void BindGroup();
    virtual void BindMaterial();
    virtual void ForceBindPane();
    virtual void UnbindPane();
    virtual void UnbindGroup();
    virtual void UnbindMaterial();
    virtual void UnbindAll();
    virtual void f0x90();
    virtual void f0x98();
    virtual void AnimatePaneImpl();
    virtual void AnimateMaterialImpl();
    virtual void AnimateExtUserDataImpl();
    virtual void Play(bool, float);
    virtual void PlayAuto(float);
    virtual void PlayFromCurrent(bool, float);
    virtual void Stop(float);
    virtual void StopCurrent();
    virtual void StopAtMin();
    virtual void StopAtMax();
};

struct Vector2f { float x, y; };
struct Vector3f { float x, y, z; };

struct Pane {
    char _00[0x18];
    Pane* parent;
    char _20[0x10];
    Vector3f translate;
    char _3c[0x58 - 0x3c];
    u8 flags;
};

struct Layout {
    char _00[0x18];
    Pane* rootPane;
};

struct PartsScreen {
    char _00[0x20];
    Layout* layout;
    char _28[8];
};

struct UIBreakHeartPartsScreen : public PartsScreen {
    char _30[0x50 - 0x30];
    Animator* animator;
};

struct PaneHeartGauge : public PartsScreen {
    PartsScreen* noGauge[40];
    Pane* noGaugePane;
    UIBreakHeartPartsScreen* breakHearts[40];
    Pane* breakPane;
    char _2c0[0x300 - 0x2c0];
    Vector2f trans;
    Vector2f width;
    float lastLife;
    int life;
    float lastMaxLife;
    int maxLife;
    char _320[0x354 - 0x320];
    u16 flags;
};

using PlayNullFunc = void (PartsScreen*, int);
using GetPositionFunc = void (PaneHeartGauge*, Vector2f&, int);
using PlayHardHeartBreakFunc = void (UIBreakHeartPartsScreen*, int, bool);
using PlayAnimFunc = void (Layout*, int);
using StartAnimFunc = void (UIBreakHeartPartsScreen*, int);
using AppendChildFunc = void (Pane*, Pane*);
using RemoveChildFunc = void (Pane*, Pane*);

PlayNullFunc* PlayNull = nullptr;
GetPositionFunc* GetPosition = nullptr;
PlayHardHeartBreakFunc* PlayHardHeartBreak = nullptr;
PlayAnimFunc* PlayAnim = nullptr;
StartAnimFunc* StartAnim = nullptr;
AppendChildFunc* AppendChild = nullptr;
RemoveChildFunc* RemoveChild = nullptr;

using GetBoolFunc = bool (void*, bool&, u32);
GetBoolFunc* GetBool = nullptr;
void** GameDataMgr = nullptr;
// honestly should use this for every version but I already got the offsets so whatever
void GetPositionImpl(PaneHeartGauge* gauge, Vector2f& pos, int index) {
    bool watchedCutscene = false;
    const auto heartsPerRow = GetBool(*GameDataMgr, watchedCutscene, 0x2af1b8bd) && watchedCutscene ? 20 : 15;
    pos = {
        gauge->trans.x + gauge->width.x * static_cast<float>(index % heartsPerRow),
        gauge->trans.y + gauge->width.y * static_cast<float>(index / heartsPerRow),
    };
}

static bool IsNewVersion() {
    return version >= 6;
}

// handles making each heart disappear from the hp display after it's broken
HOOK_DEFINE_INLINE(PlayDisappear) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        PaneHeartGauge* gauge = reinterpret_cast<PaneHeartGauge*>(ctx->X[19]);
        const auto maxIndex = static_cast<int>(IsNewVersion() ? ctx->W[8] : ctx->W[22]);
        const auto currentMaxLife = std::min(static_cast<float>(gauge->maxLife), gauge->lastMaxLife);
        const auto minIndex = static_cast<int>(std::ceil(currentMaxLife / 4));
        for (int i = minIndex; i <= maxIndex; ++i) {
            PartsScreen* part = gauge->noGauge[i];
            if (part == nullptr) {
                continue;
            }
            PlayNull(part, 0);
            // the outer function is inlined on earlier versions but I'm lazy so we'll do this
            PlayAnim(IsNewVersion() ? reinterpret_cast<Layout*>(part) : part->layout, 1);
            if (part->layout->rootPane->parent == gauge->breakPane) {
                RemoveChild(part->layout->rootPane->parent, part->layout->rootPane);
            }
        }

        ctx->X[21] = 0;
    }
};

// handles playing the heart breaking animation
HOOK_DEFINE_INLINE(PlayBreak) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        PaneHeartGauge* gauge = reinterpret_cast<PaneHeartGauge*>(ctx->X[19]);
        const auto maxIndex = static_cast<int>(IsNewVersion() ? ctx->W[20] : ctx->W[22]);
        const auto currentMaxLife = std::min(static_cast<float>(gauge->maxLife), gauge->lastMaxLife);
        const auto minIndex = static_cast<int>(std::ceil(currentMaxLife / 4));
        for (int i = minIndex; i <= maxIndex; ++i) {
            UIBreakHeartPartsScreen* part = gauge->breakHearts[i];
            if (part == nullptr) {
                continue;
            }
            Vector2f pos;
            GetPosition(gauge, pos, i);
            part->layout->rootPane->translate = { pos.x, pos.y, 0.f };
            part->layout->rootPane->flags |= 0x10;
            part->animator->Stop(0.f);
            PlayHardHeartBreak(part, 0, false);
            StartAnim(part, 1);
            if (part->layout->rootPane->parent == nullptr) {
                AppendChild(gauge->breakPane, part->layout->rootPane);
            }
        }
        gauge->flags |= 8;

        // cause the normal check to fail since we just handled the logic
        ctx->X[21] = 0;
    }
};

// prevents fairies from healing the player more than their max life
HOOK_DEFINE_INLINE(OverrideFairy) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        ctx->W[9] = 0;
    }
};

HOOK_DEFINE_INLINE(FixPtr1) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        ctx->X[9] = reinterpret_cast<u64>(cAttributeNames.data()) - 0x428;
    }
};

HOOK_DEFINE_INLINE(FixPtr2) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        ctx->X[16] = reinterpret_cast<u64>(cAttributeNames.data()) - 0x428;
    }
};
#endif

#ifdef NO_SAVE_IN_COMBAT
HOOK_DEFINE_INLINE(DisableSave) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        ctx->W[0] |= isInBattle();
    }
};
#endif

extern "C" void exl_main(void* x0, void* x1) {
    exl::hook::Initialize();

    main_offset = exl::util::modules::GetTargetStart();
    version = InitializeAppVersion();

    if (version == 0xffffffff || version > 9) {
        EXL_ABORT(0x69);
    }

    #define INSTALL(CLASS, OFFSET)      \
    if (OFFSET != 0) {                  \
        CLASS::InstallAtOffset(OFFSET); \
    }

#ifdef TRUE_DAMAGE_DISPLAY
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
    getAttachZonauAttackValue = reinterpret_cast<GetAttack*>(exl::util::modules::GetTargetOffset(sZonauAttachValueOffsets[version]));
    if (version < 6) {
        getAttachMulAttackValue = reinterpret_cast<GetAttack*>(exl::util::modules::GetTargetOffset(sAttachMulValueOffsets[version]));
    } else {
        getAttachMulAttackValue1 = reinterpret_cast<GetAttack1*>(exl::util::modules::GetTargetOffset(sAttachMulValueOffsets[version]));
    }

    #define OFFSET(X) c ## X ## Offsets[static_cast<int>(version)]

    using namespace exl::armv8::reg;
    using namespace exl::armv8::inst;

    auto patcher = exl::patch::StreamPatcher(0);
    if (IsNewVersion()) {
        FixPtr1::InstallAtOffset(OFFSET(FixPtr1));
        FixPtr2::InstallAtOffset(OFFSET(FixPtr2));

        const auto cmp = CmpImmediate(Register(RegisterKind::W, 11), cAttributeNames.size()).Value();
        patcher.Seek(OFFSET(ExtraCompare1));
        patcher.Write(cmp);
        patcher.Seek(OFFSET(ExtraCompare2));
        patcher.Write(cmp);
    } else {
        patcher.Seek(OFFSET(EnumName));
        patcher.Write(reinterpret_cast<u64>(cAttributeNames.data()) - 0x428);
    }

    const auto cmpx = IsNewVersion()
        ? CmpImmediate(Register(RegisterKind::W, 11), cAttributeNames.size() - 1).Value()
        : CmpImmediate(Register(RegisterKind::X, 8), cAttributeNames.size()).Value();
    const auto cmpw = CmpImmediate(Register(RegisterKind::W, 8), cAttributeNames.size() - 1).Value();

    patcher.Seek(OFFSET(CompareX));
    patcher.Write(cmpx);
    patcher.Seek(OFFSET(CompareW));
    patcher.Write(cmpw);

    EvalTgHit::InstallAtOffset(OFFSET(EvalTgHit));
    BreakHeart::InstallAtOffset(OFFSET(BreakHeart));
    BreakHeartUI::InstallAtOffset(OFFSET(BreakHeartUI));
    PlayDisappear::InstallAtOffset(OFFSET(PlayDisappear));
    PlayBreak::InstallAtOffset(OFFSET(PlayBreak));
    OverrideFairy::InstallAtOffset(OFFSET(OverrideFairy));

    PlayNull = reinterpret_cast<PlayNullFunc*>(exl::util::modules::GetTargetOffset(OFFSET(PlayNull)));
    if (IsNewVersion()) {
        GetPosition = GetPositionImpl;
        GameDataMgr = reinterpret_cast<void**>(exl::util::modules::GetTargetOffset(OFFSET(GameDataMgr)));
        GetBool = reinterpret_cast<GetBoolFunc*>(exl::util::modules::GetTargetOffset(OFFSET(GetBool)));
    } else {
        GetPosition = reinterpret_cast<GetPositionFunc*>(exl::util::modules::GetTargetOffset(OFFSET(GetPosition)));
    }
    PlayHardHeartBreak = reinterpret_cast<PlayHardHeartBreakFunc*>(exl::util::modules::GetTargetOffset(OFFSET(PlayHardHeartBreak)));
    PlayAnim = reinterpret_cast<PlayAnimFunc*>(exl::util::modules::GetTargetOffset(OFFSET(PlayAnim)));
    StartAnim = reinterpret_cast<StartAnimFunc*>(exl::util::modules::GetTargetOffset(OFFSET(StartAnim)));
    AppendChild = reinterpret_cast<AppendChildFunc*>(exl::util::modules::GetTargetOffset(OFFSET(AppendChild)));
    RemoveChild = reinterpret_cast<RemoveChildFunc*>(exl::util::modules::GetTargetOffset(OFFSET(RemoveChild)));

    #undef OFFSET
#endif

#ifdef NO_SAVE_IN_COMBAT
    INSTALL(DisableSave, sDisableSaveOffsets[version])
    gGameBalanceModulePtr = reinterpret_cast<GameBalanceModule**>(exl::util::modules::GetTargetOffset(sGameBalanceModuleOffsets[version]));
#endif

    #undef INSTALL
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}