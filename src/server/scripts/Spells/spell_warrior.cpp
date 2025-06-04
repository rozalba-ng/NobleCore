/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warr_".
 */

#include "ScriptMgr.h"
#include "Map.h"
#include "MoveSpline.h"
#include "PathGenerator.h"
#include "Player.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellScript.h"

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "AreaTriggerTemplate.h"
#include "Creature.h"
#include "Item.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Spell.h"
#include "SpellPackets.h"
#include "Unit.h"
#include "Cell.h"
#include "DB2Stores.h"
#include "PetPackets.h"
#include "TemporarySummon.h"

enum WarriorSpells
{
    SPELL_WARRIOR_BLADESTORM_PERIODIC_WHIRLWIND     = 50622,
    SPELL_WARRIOR_BLOODTHIRST_HEAL                  = 117313,
    SPELL_WARRIOR_CHARGE                            = 34846,
    SPELL_WARRIOR_CHARGE_EFFECT                     = 218104,
    SPELL_WARRIOR_CHARGE_EFFECT_BLAZING_TRAIL       = 198337,
    SPELL_WARRIOR_CHARGE_PAUSE_RAGE_DECAY           = 109128,
    SPELL_WARRIOR_CHARGE_ROOT_EFFECT                = 105771,
    SPELL_WARRIOR_CHARGE_SLOW_EFFECT                = 236027,
    SPELL_WARRIOR_COLOSSUS_SMASH                    = 167105,
    SPELL_WARRIOR_COLOSSUS_SMASH_AURA               = 208086,
    SPELL_WARRIOR_CRITICAL_THINKING_ENERGIZE        = 392776,
    SPELL_WARRIOR_EXECUTE                           = 20647,
    SPELL_WARRIOR_FUELED_BY_VIOLENCE_HEAL           = 383104,
    SPELL_WARRIOR_GLYPH_OF_THE_BLAZING_TRAIL        = 123779,
    SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP              = 159708,
    SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP_BUFF         = 133278,
    SPELL_WARRIOR_HEROIC_LEAP_JUMP                  = 94954,
    SPELL_WARRIOR_IGNORE_PAIN                       = 190456,
    SPELL_WARRIOR_IN_FOR_THE_KILL                   = 248621,
    SPELL_WARRIOR_IN_FOR_THE_KILL_HASTE             = 248622,
    SPELL_WARRIOR_IMPENDING_VICTORY                 = 202168,
    SPELL_WARRIOR_IMPENDING_VICTORY_HEAL            = 202166,
    SPELL_WARRIOR_IMPROVED_HEROIC_LEAP              = 157449,
    SPELL_WARRIOR_MORTAL_STRIKE                     = 12294,
    SPELL_WARRIOR_MORTAL_WOUNDS                     = 213667,
    SPELL_WARRIOR_RALLYING_CRY                      = 97463,
    SPELL_WARRIOR_RUMBLING_EARTH                    = 275339,
    SPELL_WARRIOR_SHIELD_BLOCK_AURA                 = 132404,
    SPELL_WARRIOR_SHIELD_CHARGE_EFFECT              = 385953,
    SPELL_WARRIOR_SHIELD_SLAM                       = 23922,
    SPELL_WARRIOR_SHIELD_SLAM_MARKER                = 224324,
    SPELL_WARRIOR_SHOCKWAVE                         = 46968,
    SPELL_WARRIOR_SHOCKWAVE_STUN                    = 132168,
    SPELL_WARRIOR_STOICISM                          = 70845,
    SPELL_WARRIOR_STORM_BOLT_STUN                   = 132169,
    SPELL_WARRIOR_STORM_BOLTS                       = 436162,
    SPELL_WARRIOR_STRATEGIST                        = 384041,
    SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_1   = 12723,
    SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_2   = 26654,
    SPELL_WARRIOR_TAUNT                             = 355,
    SPELL_WARRIOR_TRAUMA_EFFECT                     = 215537,
    SPELL_WARRIOR_VICTORIOUS                        = 32216,
    SPELL_WARRIOR_VICTORY_RUSH_HEAL                 = 118779,
    SPELL_WARRIOR_RAVAGER_SUMMON                    = 227876,
    SPELL_WARRIOR_RAVAGER_DAMAGE                    = 156287,
    SPELL_WARRIOR_RAVAGER_ENERGIZE                  = 334934,
    SPELL_WARRIOR_RAVAGER_PARRY                     = 227744,
    NPC_WARRIOR_RAVAGER                             = 76168,
    SPELL_WARRIOR_SHIELD_BLOCKC_TRIGGERED           = 132404,
    SPELL_WARRIOR_HEAVY_REPERCUSSIONS               = 203177,
    SPELL_WARRIOR_RENEWED_FURY                      = 202288,
    SPELL_WARRIOR_RENEWED_FURY_EFFECT               = 202289,
    SPELL_WARRIOR_VENGEANCE_FOCUSED_RAGE            = 202573,
    SPELL_WARRIOR_VENGEANCE_AURA                    = 202572,
    SPELL_WARRIOR_LAST_STAND                        = 12975,
    SPELL_WARRIOR_SLAM_ARMS                         = 1464,
    SPELL_WARRIOR_SUDDEN_DEATH                      = 280721,
    SPELL_WARRIOR_SUDDEN_DEATH_PROC                 = 280776,
    SPELL_WARRIOR_BOUNDING_STRIDE                   = 202163,
    SPELL_WARRIOR_BOUNDING_STRIDE_SPEED             = 202164,
    SPELL_WARRIOR_LAST_STAND_TRIGGERED              = 12976,
    SPELL_WARRIOR_WRECKING_BALL_EFFECT              = 215570,
    SPELL_WARRIOR_MEAT_CLEAVER                      = 280392,
    SPELL_WARRIOR_ENRAGE_AURA                       = 184362,
    SPELL_WARRIOR_THIRST_FOR_BATTLE                 = 199202,
    SPELL_WARRIOR_THIRST_FOR_BATTLE_BUFF            = 199203,
    SPELL_WARRIOR_BLOODTHIRST_DAMAGE                = 23881,
    SPELL_WARRIOR_ENDLESS_RAGE                      = 202296,
    SPELL_WARRIOR_ENDLESS_RAGE_GIVE_POWER           = 280283,
    SPELL_WARRIOR_UNCHACKLED_FURY                   = 76856,
    SPELL_WARRIOR_FROTHING_BERSERKER                = 215572,
    SPELL_WARRIOR_FRESH_MEAT                        = 215568,
    SPELL_WARRIOR_SUDDEN_DEATH_PROCS                = 280776,
    SPELL_WARRIOR_ANGER_MANAGEMENT                  = 152278,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_1        = 46859,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_2        = 46860,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_1     = 64849,
    SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_2     = 64850,
    SPELL_WARRIOR_WEAKENED_BLOWS                    = 213913,
    SPELL_WARRIOR_THUNDERSTRUCK                     = 199045,
    SPELL_WARRIOR_THUNDERSTRUCK_STUN                = 199042,
    SPELL_WARRIOR_CLEAVE                            = 845,
    TALENT_WARRIOR_BURSTING_EARTH                   = 275339,
};

enum WarriorMisc
{
    SPELL_VISUAL_BLAZING_CHARGE = 26423
};

// 107574 - Avatar
class spell_warr_avatar : public SpellScript
{
    void HandleRemoveImpairingAuras(SpellEffIndex /*effIndex*/) const
    {
        GetCaster()->RemoveMovementImpairingAuras(true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_avatar::HandleRemoveImpairingAuras, EFFECT_5, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 23881 - Bloodthirst
class spell_warr_bloodthirst : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_BLOODTHIRST_HEAL });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetCaster(), SPELL_WARRIOR_BLOODTHIRST_HEAL, true);
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (!caster || !target)
            return;

        if (target != ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
            SetHitDamage(GetHitDamage() / 2);

        int32 heal = CalculatePct(caster->GetMaxHealth(), 3);
            SetHitHeal(heal);

        if (caster->HasAura(SPELL_WARRIOR_FRESH_MEAT))
            if (roll_chance_f(15))
                caster->CastSpell(nullptr, SPELL_WARRIOR_ENRAGE_AURA, true);

        if (caster->HasAura(SPELL_WARRIOR_THIRST_FOR_BATTLE))
        {
            caster->AddAura(SPELL_WARRIOR_THIRST_FOR_BATTLE_BUFF, caster);
            if (AuraEffect* thirst = caster->GetAura(SPELL_WARRIOR_THIRST_FOR_BATTLE_BUFF)->GetEffect(0))
                thirst->GetAmount();
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_warr_bloodthirst::HandleDummy, EFFECT_3, SPELL_EFFECT_DUMMY);
        OnHit += SpellHitFn(spell_warr_bloodthirst::HandleOnHit);
    }
};

// 384036 - Brutal Vitality
class spell_warr_brutal_vitality : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_IGNORE_PAIN });
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        _damageAmount += CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());
    }

    void HandleDummyTick(AuraEffect const* /*aurEff*/)
    {
        if (_damageAmount == 0)
            return;

        if (AuraEffect* ignorePainAura = GetTarget()->GetAuraEffect(SPELL_WARRIOR_IGNORE_PAIN, EFFECT_0))
            ignorePainAura->ChangeAmount(ignorePainAura->GetAmount() + _damageAmount);

        _damageAmount = 0;
    }

    void Register() override
    {
        AfterEffectProc += AuraEffectProcFn(spell_warr_brutal_vitality::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warr_brutal_vitality::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }

private:
    uint32 _damageAmount = 0;
};

// 100 - Charge
class spell_warr_charge : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_WARRIOR_CHARGE_EFFECT,
            SPELL_WARRIOR_CHARGE_EFFECT_BLAZING_TRAIL
        });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        uint32 spellId = SPELL_WARRIOR_CHARGE_EFFECT;
        if (GetCaster()->HasAura(SPELL_WARRIOR_GLYPH_OF_THE_BLAZING_TRAIL))
            spellId = SPELL_WARRIOR_CHARGE_EFFECT_BLAZING_TRAIL;

        GetCaster()->CastSpell(GetHitUnit(), spellId, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_charge::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 126661 - Warrior Charge Drop Fire Periodic
class spell_warr_charge_drop_fire_periodic : public AuraScript
{
    void DropFireVisual(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (GetTarget()->IsSplineEnabled())
        {
            for (uint32 i = 0; i < 5; ++i)
            {
                int32 timeOffset = 6 * i * aurEff->GetPeriod() / 25;
                Movement::Location loc = GetTarget()->movespline->ComputePosition(timeOffset);
                GetTarget()->SendPlaySpellVisual(Position(loc.x, loc.y, loc.z), SPELL_VISUAL_BLAZING_CHARGE, 0, 0, 1.f, true);
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warr_charge_drop_fire_periodic::DropFireVisual, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

// 198337 - Charge Effect (dropping Blazing Trail)
// 218104 - Charge Effect
class spell_warr_charge_effect : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            SPELL_WARRIOR_CHARGE_PAUSE_RAGE_DECAY,
            SPELL_WARRIOR_CHARGE_ROOT_EFFECT,
            SPELL_WARRIOR_CHARGE_SLOW_EFFECT
        });
    }

    void HandleCharge(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        caster->CastSpell(caster, SPELL_WARRIOR_CHARGE_PAUSE_RAGE_DECAY, CastSpellExtraArgs(TRIGGERED_FULL_MASK).AddSpellMod(SPELLVALUE_BASE_POINT0, 0));
        caster->CastSpell(target, SPELL_WARRIOR_CHARGE_ROOT_EFFECT, true);
        caster->CastSpell(target, SPELL_WARRIOR_CHARGE_SLOW_EFFECT, true);
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_warr_charge_effect::HandleCharge, EFFECT_0, SPELL_EFFECT_CHARGE);
    }
};

// 167105 - Colossus Smash
// 262161 - Warbreaker
class spell_warr_colossus_smash : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_COLOSSUS_SMASH_AURA, SPELL_WARRIOR_IN_FOR_THE_KILL, SPELL_WARRIOR_IN_FOR_THE_KILL_HASTE })
            && ValidateSpellEffect({ { SPELL_WARRIOR_IN_FOR_THE_KILL, EFFECT_2 } });
    }

    void HandleHit()
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();

        GetCaster()->CastSpell(GetHitUnit(), SPELL_WARRIOR_COLOSSUS_SMASH_AURA, true);

        if (caster->HasAura(SPELL_WARRIOR_IN_FOR_THE_KILL))
        {
            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_IN_FOR_THE_KILL, DIFFICULTY_NONE))
            {
                if (target->HealthBelowPct(spellInfo->GetEffect(EFFECT_2).CalcValue(caster)))
                    _bonusHaste = true;
            }
        }
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARRIOR_IN_FOR_THE_KILL, DIFFICULTY_NONE);
        if (!spellInfo)
            return;

        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellBP0(spellInfo->GetEffect(EFFECT_0).CalcValue(caster));
        if (_bonusHaste)
            args.AddSpellBP0(spellInfo->GetEffect(EFFECT_1).CalcValue(caster));
        caster->CastSpell(caster, SPELL_WARRIOR_IN_FOR_THE_KILL_HASTE, args);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_colossus_smash::HandleHit);
        AfterCast += SpellCastFn(spell_warr_colossus_smash::HandleAfterCast);
    }

private:
    bool _bonusHaste = false;
};

// 389306 - Critical Thinking
class spell_warr_critical_thinking : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_CRITICAL_THINKING_ENERGIZE });
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        if (Optional<int32> rageCost = eventInfo.GetProcSpell()->GetPowerTypeCostAmount(POWER_RAGE))
            GetTarget()->CastSpell(nullptr, SPELL_WARRIOR_CRITICAL_THINKING_ENERGIZE, CastSpellExtraArgs(TRIGGERED_FULL_MASK)
                .AddSpellBP0(CalculatePct(*rageCost, aurEff->GetAmount())));
    }

    void Register() override
    {
        AfterEffectProc += AuraEffectProcFn(spell_warr_critical_thinking::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

// 236279 - Devastator
class spell_warr_devastator : public AuraScript
{
    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellEffect({ { spellInfo->Id, EFFECT_1 } }) && ValidateSpellInfo({ SPELL_WARRIOR_SHIELD_SLAM, SPELL_WARRIOR_SHIELD_SLAM_MARKER });
    }

    void OnProc(AuraEffect const* /*aurEff*/, ProcEventInfo const& /*eventInfo*/) const
    {
        if (GetTarget()->GetSpellHistory()->HasCooldown(SPELL_WARRIOR_SHIELD_SLAM))
        {
            if (roll_chance_i(GetEffectInfo(EFFECT_1).CalcValue()))
            {
                GetTarget()->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_SHIELD_SLAM, true);
                GetTarget()->CastSpell(GetTarget(), SPELL_WARRIOR_SHIELD_SLAM_MARKER, TRIGGERED_IGNORE_CAST_IN_PROGRESS);
            }
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warr_devastator::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 260798 - Execute (Arms, Protection)
class spell_warr_execute_damage : public SpellScript
{
    static void CalculateExecuteDamage(SpellEffectInfo const& /*spellEffectInfo*/, Unit const* /*victim*/, int32 const& /*damageOrHealing*/, int32 const& /*flatMod*/, float& pctMod)
    {
        // tooltip has 2 multiplier hardcoded in it $damage=${2.0*$260798s1}
        pctMod *= 2.0f;
    }

    void Register() override
    {
        CalcDamage += SpellCalcDamageFn(spell_warr_execute_damage::CalculateExecuteDamage);
    }
};

// 383103  - Fueled by Violence
class spell_warr_fueled_by_violence : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_FUELED_BY_VIOLENCE_HEAL });
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        _nextHealAmount += CalculatePct(eventInfo.GetDamageInfo() ? eventInfo.GetDamageInfo()->GetDamage() : 0, GetEffectInfo(EFFECT_0).CalcValue(GetTarget()));
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (_nextHealAmount == 0)
            return;

        Unit* target = GetTarget();
        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellBP0(_nextHealAmount);

        target->CastSpell(target, SPELL_WARRIOR_FUELED_BY_VIOLENCE_HEAL, args);
        _nextHealAmount = 0;
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_warr_fueled_by_violence::HandleProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warr_fueled_by_violence::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }

private:
    uint32 _nextHealAmount = 0;
};

// 6544 - Heroic leap
class spell_warr_heroic_leap : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_HEROIC_LEAP_JUMP });
    }

    SpellCastResult CheckElevation()
    {
        if (WorldLocation const* dest = GetExplTargetDest())
        {
            if (GetCaster()->HasUnitMovementFlag(MOVEMENTFLAG_ROOT))
                return SPELL_FAILED_ROOTED;

            if (GetCaster()->GetMap()->Instanceable())
            {
                float range = GetSpellInfo()->GetMaxRange(true, GetCaster()) * 1.5f;

                PathGenerator generatedPath(GetCaster());
                generatedPath.SetPathLengthLimit(range);

                bool result = generatedPath.CalculatePath(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ(), false);
                if (generatedPath.GetPathType() & PATHFIND_SHORT)
                    return SPELL_FAILED_OUT_OF_RANGE;
                else if (!result || generatedPath.GetPathType() & PATHFIND_NOPATH)
                    return SPELL_FAILED_NOPATH;
            }
            else if (dest->GetPositionZ() > GetCaster()->GetPositionZ() + 4.0f)
                return SPELL_FAILED_NOPATH;

            return SPELL_CAST_OK;
        }

        return SPELL_FAILED_NO_VALID_TARGETS;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (WorldLocation* dest = GetHitDest())
            GetCaster()->CastSpell(*dest, SPELL_WARRIOR_HEROIC_LEAP_JUMP, true);

        if (Unit* caster = GetCaster())
        {
            caster->m_Events.AddEventAtOffset([caster]()
            {
                if (caster->HasAura(SPELL_WARRIOR_BOUNDING_STRIDE) &&
                    !caster->IsFlying() &&
                    !caster->IsFalling())
                {
                    caster->CastSpell(caster, SPELL_WARRIOR_BOUNDING_STRIDE_SPEED, true);
                }
            }, 500ms);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warr_heroic_leap::CheckElevation);
        OnEffectHit += SpellEffectFn(spell_warr_heroic_leap::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Heroic Leap (triggered by Heroic Leap (6544)) - 178368
class spell_warr_heroic_leap_jump : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP,
            SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP_BUFF,
            SPELL_WARRIOR_IMPROVED_HEROIC_LEAP,
            SPELL_WARRIOR_TAUNT
        });
    }

    void AfterJump(SpellEffIndex /*effIndex*/)
    {
        if (GetCaster()->HasAura(SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP))
            GetCaster()->CastSpell(GetCaster(), SPELL_WARRIOR_GLYPH_OF_HEROIC_LEAP_BUFF, true);
        if (GetCaster()->HasAura(SPELL_WARRIOR_IMPROVED_HEROIC_LEAP))
            GetCaster()->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_TAUNT, true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_warr_heroic_leap_jump::AfterJump, EFFECT_1, SPELL_EFFECT_JUMP_DEST);
    }
};

// 202168 - Impending Victory
class spell_warr_impending_victory : public SpellScript
{
    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_WARRIOR_IMPENDING_VICTORY_HEAL, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_warr_impending_victory::HandleOnHit);
    }
};

// 5246 - Intimidating Shout
class spell_warr_intimidating_shout : public SpellScript
{
    void FilterTargets(std::list<WorldObject*>& unitList)
    {
        unitList.remove(GetExplTargetWorldObject());
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_intimidating_shout::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_intimidating_shout::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

// 70844 - Item - Warrior T10 Protection 4P Bonus
class spell_warr_item_t10_prot_4p_bonus : public AuraScript
{
    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_STOICISM })
            && ValidateSpellEffect({ { spellInfo->Id, EFFECT_1 } });
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* target = eventInfo.GetActionTarget();
        int32 bp0 = CalculatePct(target->GetMaxHealth(), GetEffectInfo(EFFECT_1).CalcValue());
        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellBP0(bp0);
        target->CastSpell(nullptr, SPELL_WARRIOR_STOICISM, args);
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_warr_item_t10_prot_4p_bonus::HandleProc);
    }
};

// 12294 - Mortal Strike
class spell_warr_mortal_strike : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_MORTAL_WOUNDS });
    }

    void HandleOnHit()
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->AddAura(SPELL_WARRIOR_MORTAL_WOUNDS, target);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_mortal_strike::HandleOnHit);
    }
};

// 97462 - Rallying Cry
class spell_warr_rallying_cry : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_RALLYING_CRY });
    }

    bool Load() override
    {
        return GetCaster()->GetTypeId() ==  TYPEID_PLAYER;
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellMod(SPELLVALUE_BASE_POINT0, int32(GetHitUnit()->CountPctFromMaxHealth(GetEffectValue())));

        GetCaster()->CastSpell(GetHitUnit(), SPELL_WARRIOR_RALLYING_CRY, args);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_rallying_cry::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 275339 - (attached to 46968 - Shockwave)
class spell_warr_rumbling_earth : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellEffect({ { SPELL_WARRIOR_RUMBLING_EARTH, EFFECT_1 } });
    }

    bool Load() override
    {
        return GetCaster()->HasAura(SPELL_WARRIOR_RUMBLING_EARTH);
    }

    void HandleCooldownReduction(SpellEffIndex /*effIndex*/) const
    {
        Unit* caster = GetCaster();
        Aura const* rumblingEarth = caster->GetAura(SPELL_WARRIOR_RUMBLING_EARTH);
        if (!rumblingEarth)
            return;

        AuraEffect const* minTargetCount = rumblingEarth->GetEffect(EFFECT_0);
        AuraEffect const* cooldownReduction = rumblingEarth->GetEffect(EFFECT_1);
        if (!minTargetCount || !cooldownReduction)
            return;

        if (GetUnitTargetCountForEffect(EFFECT_0) >= minTargetCount->GetAmount())
            GetCaster()->GetSpellHistory()->ModifyCooldown(GetSpellInfo()->Id, Seconds(-cooldownReduction->GetAmount()));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_rumbling_earth::HandleCooldownReduction, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 2565 - Shield Block
class spell_warr_shield_block : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_SHIELD_BLOCK_AURA });
    }

    void HandleHitTarget(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetCaster(), SPELL_WARRIOR_SHIELD_BLOCK_AURA, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_shield_block::HandleHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 385952 - Shield Charge
class spell_warr_shield_charge : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_SHIELD_CHARGE_EFFECT });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetHitUnit(), SPELL_WARRIOR_SHIELD_CHARGE_EFFECT, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_shield_charge::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 46968 - Shockwave
class spell_warr_shockwave : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_SHOCKWAVE_STUN });
    }

    void HandleStun(SpellEffIndex /*effIndex*/) const
    {
        GetCaster()->CastSpell(GetHitUnit(), SPELL_WARRIOR_SHOCKWAVE_STUN, CastSpellExtraArgsInit{
            .TriggerFlags = TRIGGERED_IGNORE_CAST_IN_PROGRESS | TRIGGERED_DONT_REPORT_CAST_ERROR,
            .TriggeringSpell = GetSpell()
        });
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_shockwave::HandleStun, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 107570 - Storm Bolt
class spell_warr_storm_bolt : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_STORM_BOLT_STUN });
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/) const
    {
        GetCaster()->CastSpell(GetHitUnit(), SPELL_WARRIOR_STORM_BOLT_STUN, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_storm_bolt::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 107570 - Storm Bolt
class spell_warr_storm_bolts: public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_STORM_BOLTS });
    }

    bool Load() override
    {
        return !GetCaster()->HasAura(SPELL_WARRIOR_STORM_BOLTS);
    }

    void FilterTargets(std::list<WorldObject*>& targets) const
    {
        targets.clear();

        if (Unit* target = GetExplTargetUnit())
            targets.push_back(target);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_storm_bolts::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 384041 - Strategist
class spell_warr_strategist : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_SHIELD_SLAM, SPELL_WARRIOR_SHIELD_SLAM_MARKER })
            && ValidateSpellEffect({ { SPELL_WARRIOR_STRATEGIST, EFFECT_0 } });
    }

    static bool CheckProc(AuraEffect const* aurEff, ProcEventInfo const& /*procEvent*/)
    {
        return roll_chance_i(aurEff->GetAmount());
    }

    void HandleCooldown(AuraEffect const* /*aurEff*/, ProcEventInfo const& /*procEvent*/) const
    {
        Unit* caster = GetTarget();
        caster->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_SHIELD_SLAM, true);
        caster->CastSpell(caster, SPELL_WARRIOR_SHIELD_SLAM_MARKER, TRIGGERED_IGNORE_CAST_IN_PROGRESS);
    }

    void Register() override
    {
        DoCheckEffectProc += AuraCheckEffectProcFn(spell_warr_strategist::CheckProc, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectProc += AuraEffectProcFn(spell_warr_strategist::HandleCooldown, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 52437 - Sudden Death
class spell_warr_sudden_death : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_COLOSSUS_SMASH });
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // Remove cooldown on Colossus Smash
        if (Player* player = GetTarget()->ToPlayer())
            player->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_COLOSSUS_SMASH, true);
    }

    void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        GetTarget()->CastSpell(GetTarget(), SPELL_WARRIOR_SUDDEN_DEATH_PROCS, true);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectRemoveFn(spell_warr_sudden_death::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL); // correct?
        OnEffectProc += AuraEffectProcFn(spell_warr_sudden_death::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 12328, 18765, 35429 - Sweeping Strikes
class spell_warr_sweeping_strikes : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_1, SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_2 });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        _procTarget = eventInfo.GetActor()->SelectNearbyTarget(eventInfo.GetProcTarget());
        return _procTarget != nullptr;
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo())
        {
            SpellInfo const* spellInfo = damageInfo->GetSpellInfo();
            if (spellInfo && (spellInfo->Id == SPELL_WARRIOR_BLADESTORM_PERIODIC_WHIRLWIND || (spellInfo->Id == SPELL_WARRIOR_EXECUTE && !_procTarget->HasAuraState(AURA_STATE_WOUNDED_20_PERCENT))))
            {
                // If triggered by Execute (while target is not under 20% hp) or Bladestorm deals normalized weapon damage
                GetTarget()->CastSpell(_procTarget, SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_2, aurEff);
            }
            else
            {
                CastSpellExtraArgs args(aurEff);
                args.AddSpellMod(SPELLVALUE_BASE_POINT0, damageInfo->GetDamage());
                GetTarget()->CastSpell(_procTarget, SPELL_WARRIOR_SWEEPING_STRIKES_EXTRA_ATTACK_1, args);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warr_sweeping_strikes::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warr_sweeping_strikes::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }

    Unit* _procTarget = nullptr;
};

// 215538 - Trauma
class spell_warr_trauma : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_TRAUMA_EFFECT });
    }

    void HandleProc(AuraEffect* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActionTarget();
        //Get 25% of damage from the spell casted (Slam & Whirlwind) plus Remaining Damage from Aura
        int32 damage = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount()) / sSpellMgr->AssertSpellInfo(SPELL_WARRIOR_TRAUMA_EFFECT, GetCastDifficulty())->GetMaxTicks());
        CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
        args.AddSpellMod(SPELLVALUE_BASE_POINT0, damage);
        GetCaster()->CastSpell(target, SPELL_WARRIOR_TRAUMA_EFFECT, args);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warr_trauma::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 28845 - Cheat Death
class spell_warr_t3_prot_8p_bonus : public AuraScript
{
    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetActionTarget()->HealthBelowPct(20))
            return true;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (damageInfo && damageInfo->GetDamage())
            if (GetTarget()->HealthBelowPctDamaged(20, damageInfo->GetDamage()))
                return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warr_t3_prot_8p_bonus::CheckProc);
    }
};

// 32215 - Victorious State
class spell_warr_victorious_state : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_IMPENDING_VICTORY });
    }

    void HandleOnProc(AuraEffect* /*aurEff*/, ProcEventInfo& procInfo)
    {
        if (procInfo.GetActor()->GetTypeId() == TYPEID_PLAYER && procInfo.GetActor()->ToPlayer()->GetPrimarySpecialization() == ChrSpecialization::WarriorFury)
            PreventDefaultAction();

        procInfo.GetActor()->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_IMPENDING_VICTORY, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warr_victorious_state::HandleOnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 34428 - Victory Rush (all script)
class victory_rush_kill_event : public PlayerScript
{
public:
    victory_rush_kill_event() : PlayerScript("victory_rush_kill_event") {}

    void OnCreatureKill(Player* killer, Creature* killed) override
    {
        if (killer->GetClass() != CLASS_WARRIOR)
            return;

        if (!killer->isHonorOrXPTarget(killed))
            return;

        _HandleVictorious(killer);
    }

    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (killer->GetClass() != CLASS_WARRIOR)
            return;

        if (!killer->isHonorOrXPTarget(killed))
            return;

        _HandleVictorious(killer);
    }

private:
    void _HandleVictorious(Player* player)
    {
        player->CastSpell(player, SPELL_WARRIOR_VICTORIOUS, TRIGGERED_FULL_MASK);

        if (player->HasSpell(SPELL_WARRIOR_IMPENDING_VICTORY))
            player->GetSpellHistory()->ResetCooldown(SPELL_WARRIOR_IMPENDING_VICTORY, true);
    }
};

class spell_warr_victory_rush : public SpellScript
{
    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        caster->CastSpell(caster, SPELL_WARRIOR_VICTORY_RUSH_HEAL, TRIGGERED_FULL_MASK);

        if (GetCaster()->HasAura(SPELL_WARRIOR_VICTORIOUS))
            GetCaster()->RemoveAura(SPELL_WARRIOR_VICTORIOUS);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_warr_victory_rush::HandleOnHit);
    }
};

// 23920 Spell Reflect
class spell_warr_spell_reflect : public SpellScriptLoader
{
public:
    spell_warr_spell_reflect() : SpellScriptLoader("spell_warr_spell_reflect") { }

    class spell_warr_spell_reflect_AuraScript : public AuraScript
    {

        void OnApply(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            Item* item = caster->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
            if (item && item->GetTemplate()->GetInventoryType() == INVTYPE_SHIELD)
                caster->CastSpell(caster, 146120, true);
            else if (caster->GetFaction() == 1732) // Alliance
                caster->CastSpell(caster, 147923, true);
            else // Horde
                caster->CastSpell(caster, 146122, true);
        }

        void OnRemove(const AuraEffect* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            // Visuals
            caster->RemoveAura(146120);
            caster->RemoveAura(147923);
            caster->RemoveAura(146122);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_warr_spell_reflect_AuraScript::OnApply, EFFECT_0, SPELL_AURA_REFLECT_SPELLS, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            OnEffectRemove += AuraEffectRemoveFn(spell_warr_spell_reflect_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_REFLECT_SPELLS, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_spell_reflect_AuraScript();
    }
};

// Ravager - 152277 (aura)
// Ravager - 228920 (aura)
class aura_warr_ravager : public AuraScript
{
public:
    void SetVisualDummy(TempSummon* summon)
    {
        _visualDummy = summon->GetGUID();
        _dest = summon->GetPosition();
    }

private:
    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Player* player = GetCaster()->ToPlayer())
            if (player->GetPrimarySpecialization() == ChrSpecialization::WarriorProtection)
                player->CastSpell(player, SPELL_WARRIOR_RAVAGER_PARRY, true);
    }

    void HandleEffectPeriodic(AuraEffect const* aurEff)
    {
        GetTarget()->CastSpell(_dest, SPELL_WARRIOR_RAVAGER_DAMAGE, aurEff);
    }

    void HandleEffecRemoved(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Creature* summon = ObjectAccessor::GetCreature(*GetTarget(), _visualDummy))
            summon->DespawnOrUnsummon();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(aura_warr_ravager::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectRemove += AuraEffectRemoveFn(aura_warr_ravager::HandleEffecRemoved, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(aura_warr_ravager::HandleEffectPeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }

    ObjectGuid _visualDummy;
    Position _dest;
};

// Ravager - 152277
// Ravager - 228920
class spell_warr_ravager : public SpellScript
{
    void InitializeVisualStalker()
    {
        if (Aura* aura = GetHitAura())
        {
            if (WorldLocation const* dest = GetExplTargetDest())
            {
                Milliseconds duration = Milliseconds(GetSpellInfo()->CalcDuration(GetOriginalCaster()));
                TempSummon* summon = GetCaster()->GetMap()->SummonCreature(NPC_WARRIOR_RAVAGER, *dest, nullptr, duration, GetOriginalCaster());
                if (!summon)
                    return;

                if (aura_warr_ravager* script = aura->GetScript<aura_warr_ravager>())
                    script->SetVisualDummy(summon);
            }
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_warr_ravager::InitializeVisualStalker);
    }
};

// Ravager Damage - 156287
class spell_warr_ravager_damage : public SpellScript
{

    void HandleOnHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (!_alreadyProc)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_WARRIOR_RAVAGER_ENERGIZE, true);
            _alreadyProc = true;
        }
        if (GetCaster()->HasAura(262304)) // Deep Wounds
            GetCaster()->CastSpell(GetHitUnit(), 262115, true); // Deep Wounds
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_ravager_damage::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }

private:
    bool _alreadyProc = false;
};

// Ravager - 76168
struct npc_warr_ravager : public ScriptedAI
{
    npc_warr_ravager(Creature* creature) : ScriptedAI(creature) { }

    enum eDatas
    {
        RAVAGER_DISPLAYID = 55644,
        SPELL_RAVAGER_VISUAL = 153709
    };

    void IsSummonedBy(WorldObject* summoner) override
    {
        me->SetDisplayId(RAVAGER_DISPLAYID);
        me->CastSpell(me, SPELL_RAVAGER_VISUAL, true);
        me->SetReactState(ReactStates::REACT_PASSIVE);
        me->AddUnitState(UnitState::UNIT_STATE_ROOT);
        me->SetUnitFlag(UnitFlags(UNIT_FLAG_UNINTERACTIBLE |
            UNIT_FLAG_NON_ATTACKABLE_2 |
            UNIT_FLAG_PLAYER_CONTROLLED));

        if (summoner == nullptr || !summoner->IsPlayer())
            return;

        if (Player* player = summoner->ToPlayer())
        {
            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EquipmentSlots::EQUIPMENT_SLOT_MAINHAND))
            {
                if (ItemTemplate const* l_Proto = sObjectMgr->GetItemTemplate(item->GetModifier(ITEM_MODIFIER_TRANSMOG_APPEARANCE_ALL_SPECS)))
                    me->SetVirtualItem(0, l_Proto->GetId());
                else
                    me->SetVirtualItem(0, item->GetTemplate()->GetId());
            }

            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EquipmentSlots::EQUIPMENT_SLOT_OFFHAND))
            {
                if (ItemTemplate const* l_Proto = sObjectMgr->GetItemTemplate(item->GetModifier(ITEM_MODIFIER_TRANSMOG_APPEARANCE_ALL_SPECS)))
                    me->SetVirtualItem(2, l_Proto->GetId());
                else
                    me->SetVirtualItem(2, item->GetTemplate()->GetId());
            }
        }
    }
};

//190456 - Ignore Pain
class spell_warr_ignore_pain : public SpellScript
{

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARRIOR_RENEWED_FURY, SPELL_WARRIOR_VENGEANCE_FOCUSED_RAGE });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_WARRIOR_RENEWED_FURY))
                caster->CastSpell(caster, SPELL_WARRIOR_RENEWED_FURY_EFFECT, true);
            if (caster->HasAura(SPELL_WARRIOR_VENGEANCE_AURA))
                caster->CastSpell(caster, SPELL_WARRIOR_VENGEANCE_FOCUSED_RAGE, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_ignore_pain::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

//190456 - Ignore Pain
class aura_warr_ignore_pain : public AuraScript
{

    int32 m_ExtraSpellCost;

    bool Load() override
    {
        Unit* caster = GetCaster();
        // In this phase the initial 20 Rage cost is removed already
        // We just check for bonus.
        m_ExtraSpellCost = std::min(caster->GetPower(POWER_RAGE), 400);
        return true;
    }

    void CalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
        {
            amount = (float)(22.3f * caster->GetTotalAttackPowerValue(BASE_ATTACK)) * (float(m_ExtraSpellCost + 200) / 600.0f);
            int32 m_newRage = caster->GetPower(POWER_RAGE) - m_ExtraSpellCost;
            if (m_newRage < 0)
                m_newRage = 0;
            caster->SetPower(POWER_RAGE, m_newRage);
            /*if (Player* player = caster->ToPlayer())
                player->SendPowerUpdate(POWER_RAGE, m_newRage);*/
        }
    }

    void OnAbsorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& /*absorbAmount*/)
    {
        if (Unit* caster = GetCaster())
        {
            SpellInfo const* spellInfo = GetSpellInfo();
            if (!spellInfo)
                return;

            SpellNonMeleeDamage spell(caster, caster->GetVictim(), spellInfo, { static_cast<uint32>(spellInfo->GetSpellXSpellVisualId(caster)), 0 }, spellInfo->GetSchoolMask());
            spell.damage = dmgInfo.GetDamage() - dmgInfo.GetDamage() * 0.9f;
            spell.cleanDamage = spell.damage;
            caster->DealSpellDamage(&spell, false);
            caster->SendSpellNonMeleeDamageLog(&spell);
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(aura_warr_ignore_pain::CalcAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(aura_warr_ignore_pain::OnAbsorb, EFFECT_0);
    }
};

/// Updated 8.3.7
// 12975 - Last Stand
class spell_warr_last_stand : public SpellScriptLoader
{
public:
    spell_warr_last_stand() : SpellScriptLoader("spell_warr_last_stand") { }

    class spell_warr_last_stand_SpellScript : public SpellScript
    {

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_WARRIOR_LAST_STAND_TRIGGERED });
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
            args.AddSpellBP0(caster->CountPctFromMaxHealth(GetEffectValue()));
            caster->CastSpell(caster, SPELL_WARRIOR_LAST_STAND_TRIGGERED, args);
        }

        void Register() override
        {
            // add dummy effect spell handler to Last Stand
            OnEffectHit += SpellEffectFn(spell_warr_last_stand_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_last_stand_SpellScript();
    }
};

/// Shattering Throw - 64382
class spell_warr_shattering_throw : public SpellScriptLoader
{
public:
    spell_warr_shattering_throw() : SpellScriptLoader("spell_warr_shattering_throw") { }

    class spell_warr_shattering_throw_SpellScript : public SpellScript
    {

        enum eSpells
        {
            ShatteringThrowDispel = 64380,
        };

        void HandleDamage(SpellEffIndex /*p_EffIndex*/)
        {
            Player* l_Player = GetCaster()->ToPlayer();
            Unit* l_Target = GetHitUnit();

            if (l_Player == nullptr || l_Target == nullptr)
                return;

            if (l_Target->IsImmunedToDamage(l_Player, GetSpellInfo()))
            {
                l_Player->CastSpell(l_Target, eSpells::ShatteringThrowDispel, true);
                return;
            }

            if (l_Player->GetPrimarySpecialization() == ChrSpecialization::WarriorFury)
                SetHitDamage(GetHitDamage() * 1.2f);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_shattering_throw_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_shattering_throw_SpellScript();
    }
};

/// Commanding Shout - 469,  Battle Shout - 6673
class spell_warr_shout : public SpellScriptLoader
{
public:
    spell_warr_shout() : SpellScriptLoader("spell_warr_shout") { }

    class spell_warr_shout_AuraScript : public AuraScript
    {

        enum eSpells
        {
            CommandingShout = 469,
            BattleShout = 6673
        };

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* l_Target = GetTarget();
            Unit* l_Caster = GetCaster();

            if (l_Caster == nullptr)
                return;

            if (GetSpellInfo()->Id == eSpells::BattleShout && l_Target->HasAura(eSpells::CommandingShout, l_Caster->GetGUID()))
                l_Target->RemoveAura(eSpells::CommandingShout, l_Caster->GetGUID());
            else if (GetSpellInfo()->Id == eSpells::CommandingShout && l_Target->HasAura(eSpells::BattleShout, l_Caster->GetGUID()))
                l_Target->RemoveAura(eSpells::BattleShout, l_Caster->GetGUID());
        }

        void Register() override
        {
            switch (m_scriptSpellId)
            {
            case eSpells::BattleShout:
                OnEffectApply += AuraEffectApplyFn(spell_warr_shout_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_ATTACK_POWER_PCT, AURA_EFFECT_HANDLE_REAL);
                break;
            case eSpells::CommandingShout:
                OnEffectApply += AuraEffectApplyFn(spell_warr_shout_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE, AURA_EFFECT_HANDLE_REAL);
                break;
            default:
                break;
            }
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_shout_AuraScript();
    }
};

// 1680 Whirlwind
class spell_warr_wirlwind_dmg : public SpellScript
{

    void HandleOnHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Player* caster = GetCaster()->ToPlayer())
        {
            if (caster->HasAura(202316)) // Fervor of Battle
            {
                if (Unit* target = caster->GetSelectedUnit())
                {
                    if (caster->IsValidAttackTarget(target))
                    {
                        caster->CastSpell(target, SPELL_WARRIOR_SLAM_ARMS, true);
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_wirlwind_dmg::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
    }
};


// 163201  - Execute
// 217955  - Execute
// 281000  - Execute
class spell_warr_execute : public SpellScript
{

    float m_powerTaken = 0.f;

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (Unit* target = GetHitUnit())
            if (target->IsAlive() && caster)
                caster->ModifyPower(POWER_RAGE, CalculatePct(m_powerTaken, GetEffectInfo(EFFECT_1).BasePoints));

        caster->Variables.Remove("spell_warr_execute_damages::multiplier");
        caster->RemoveAurasDueToSpell(SPELL_WARRIOR_SUDDEN_DEATH);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_warr_execute::HandleAfterHit);
    }
};


// 260798  - Executes damages
class spell_warr_execute_damages : public SpellScript
{

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        float damageMultiplier = GetCaster()->Variables.GetValue<float>("spell_warr_execute_damages::multiplier", 1.f);
        SetHitDamage(GetHitDamage() * damageMultiplier);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_execute_damages::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};


//385952 - Shield Charge
class spell_warr_shiel_charge : public SpellScript
{

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo
        ({
            385953
            });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetHitUnit(), 385953, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_shiel_charge::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};


// Whirlwind - 190411
class spell_warr_whirlwind : public SpellScript
{

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (!caster)
            return;

        if (caster->HasAura(SPELL_WARRIOR_WRECKING_BALL_EFFECT))
            caster->RemoveAura(SPELL_WARRIOR_WRECKING_BALL_EFFECT);

        if (caster->HasAura(SPELL_WARRIOR_MEAT_CLEAVER))
            if (roll_chance_f(10))
                caster->CastSpell(nullptr, SPELL_WARRIOR_ENRAGE_AURA, true);

        if (caster->HasAura(SPELL_WARRIOR_THIRST_FOR_BATTLE))
        {
            caster->AddAura(SPELL_WARRIOR_THIRST_FOR_BATTLE_BUFF, caster);
            if (AuraEffect* thirst = caster->GetAura(SPELL_WARRIOR_THIRST_FOR_BATTLE_BUFF)->GetEffect(0))
                thirst->GetAmount();
        }

        caster->AddAura(85739, caster);

        if (caster->HasAura(12950))
        {
            if (_targetCount == 0)
            {
                caster->ModifyPower(POWER_RAGE, 30);
            }
            else if (_targetCount <= 5)
            {
                caster->ModifyPower(POWER_RAGE, _power * 10 + 30);
            }
            else if (_targetCount >= 5)
            {
                caster->ModifyPower(POWER_RAGE, 80);
            }
        }
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        ++_targetCount;
        ++_power;
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warr_whirlwind::HandleAfterCast);
        OnEffectHitTarget += SpellEffectFn(spell_warr_whirlwind::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }

    uint32 _power = 0;
    uint32 _targetCount = 0;
};


// Unshackled Fury - 76856
class spell_warr_unshackled_fury : public SpellScriptLoader
{
public:
    spell_warr_unshackled_fury() : SpellScriptLoader("spell_warr_unshackled_fury") { }

    class spell_warr_unshackled_fury_AuraScript : public AuraScript
    {

        void CalculateAmount(const AuraEffect* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* caster = GetCaster())
                if (!caster->HasAuraState(AURA_STATE_ENRAGED))
                    amount = 0;
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_unshackled_fury_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_unshackled_fury_AuraScript();
    }
};

// Enrage - 184361
class spell_warr_enrage : public SpellScriptLoader
{
public:
    spell_warr_enrage() : SpellScriptLoader("spell_warr_enrage") {}

    class spell_warr_enrage_AuraScript : public AuraScript
    {

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_BLOODTHIRST_DAMAGE &&
                eventInfo.GetHitMask() & PROC_HIT_CRITICAL)
                return true;
            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_warr_enrage_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_enrage_AuraScript();
    }
};


// Enrage Aura - 184362
class spell_warr_enrage_aura : public AuraScript
{

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_WARRIOR_ENDLESS_RAGE))
                caster->CastSpell(nullptr, SPELL_WARRIOR_ENDLESS_RAGE_GIVE_POWER, true);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        caster->RemoveAurasDueToSpell(SPELL_WARRIOR_UNCHACKLED_FURY);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warr_enrage_aura::OnApply, EFFECT_0, SPELL_AURA_MELEE_SLOW, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_warr_enrage_aura::HandleRemove, EFFECT_0, SPELL_AURA_MELEE_SLOW, AURA_EFFECT_HANDLE_REAL);
    }
};

//215571 Frothing Berserker
class spell_warr_frothing_berserker : public SpellScriptLoader
{
public:
    spell_warr_frothing_berserker() : SpellScriptLoader("spell_warr_frothing_berserker") { }

    class spell_warr_frothing_berserker_AuraScript : public AuraScript
    {

        void HandleProc(AuraEffect* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_WARRIOR_FROTHING_BERSERKER, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_warr_frothing_berserker_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            OnEffectProc += AuraEffectProcFn(spell_warr_frothing_berserker_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_ADD_FLAT_MODIFIER);
            OnEffectProc += AuraEffectProcFn(spell_warr_frothing_berserker_AuraScript::HandleProc, EFFECT_2, SPELL_AURA_ADD_FLAT_MODIFIER);
            OnEffectProc += AuraEffectProcFn(spell_warr_frothing_berserker_AuraScript::HandleProc, EFFECT_3, SPELL_AURA_ADD_FLAT_MODIFIER);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_frothing_berserker_AuraScript();
    }
};

//214871 - Odyn's fury
class spell_warr_odyns_fury : public SpellScriptLoader
{
public:
    spell_warr_odyns_fury() : SpellScriptLoader("spell_warr_odyns_fury") { }

    class spell_warr_odyns_fury_AuraScript : public AuraScript
    {

        void Absorb(AuraEffect* /*aurEff*/, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
        {
            absorbAmount = 0;
        }

        void Register() override
        {
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_warr_odyns_fury_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warr_odyns_fury_AuraScript();
    }
};

//152278 Anger Management
class anger_management : public PlayerScript
{
public:
    anger_management() : PlayerScript("anger_management") { }

    void OnSpellCast(Player* player, Spell* spell, bool) override
    {
        if (player->GetClass() != CLASS_WARRIOR)
            return;

        if (Aura* anger = player->GetAura(SPELL_WARRIOR_ANGER_MANAGEMENT))
        {

            std::vector<SpellPowerCost> const& costs = spell->GetPowerCost();
            auto m = std::find_if(costs.begin(), costs.end(), [](SpellPowerCost const& cost) { return cost.Power == POWER_RAGE; });
            if (m == costs.end())
                return;

            //int32 mod = powerCost->Amount * 100 / anger->GetEffect(EFFECT_0).GetAmount();
            //int32 mod = std::max(powerCost->Amount * 100, anger->GetEffect(EFFECT_0).GetAmount()) / 2;
            if (player->GetPrimarySpecialization() == ChrSpecialization::WarriorArms)
            {
                player->GetSpellHistory()->ModifyCooldown(262161, (Milliseconds)-1000); // Warbreaker
                player->GetSpellHistory()->ModifyCooldown(46924, (Milliseconds)-1000); // Bladestorm
                player->GetSpellHistory()->ModifyCooldown(227847, (Milliseconds)-1000); // Bladestorm
                player->GetSpellHistory()->ModifyCooldown(SPELL_WARRIOR_COLOSSUS_SMASH, (Milliseconds)-1000); // Colossus Smash
            }
            else if (player->GetPrimarySpecialization() == ChrSpecialization::WarriorFury)
            {
                player->GetSpellHistory()->ModifyCooldown(1719, (Milliseconds)-1000); // Recklessness
            }
            else if (player->GetPrimarySpecialization() == ChrSpecialization::WarriorProtection)
            {
                player->GetSpellHistory()->ModifyCooldown(107574, (Milliseconds)-1000); // Avatar
                player->GetSpellHistory()->ModifyCooldown(SPELL_WARRIOR_LAST_STAND, (Milliseconds)-1000); // Last Stand
                player->GetSpellHistory()->ModifyCooldown(871, (Milliseconds)-1000); // Shield Wall
                player->GetSpellHistory()->ModifyCooldown(1160, (Milliseconds)-1000); // Demoralizing Shout
            }

        }
    }
};

// 7384 - Overpower
class spell_warr_overpower : public SpellScriptLoader
{
public:
    spell_warr_overpower() : SpellScriptLoader("spell_warr_overpower") { }

    class spell_warr_overpower_SpellScript : public SpellScript
    {

        void HandleEffect(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster())
                return;

            uint32 spellId = 0;
            if (GetCaster()->HasAura(SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_1))
                spellId = SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_1;
            else if (GetCaster()->HasAura(SPELL_WARRIOR_UNRELENTING_ASSAULT_RANK_2))
                spellId = SPELL_WARRIOR_UNRELENTING_ASSAULT_TRIGGER_2;

            if (!spellId)
                return;

            if (Player* target = GetHitPlayer())
                if (target->IsNonMeleeSpellCast(false, false, true)) // UNIT_STATE_CASTING should not be used here, it's present during a tick for instant casts
                    target->CastSpell(target, spellId, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_warr_overpower_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_ANY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_overpower_SpellScript();
    }
};

// 6343 - Thunder Clap
class spell_warr_thunder_clap : public SpellScriptLoader
{
public:
    spell_warr_thunder_clap() : SpellScriptLoader("spell_warr_thunder_clap") { }

    class spell_warr_thunder_clap_SpellScript : public SpellScript
    {

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {

                    _player->CastSpell(target, SPELL_WARRIOR_WEAKENED_BLOWS, true);
                    if (Aura* aura = target->GetAura(SPELL_WARRIOR_WEAKENED_BLOWS))
                        aura->SetDuration(4000);

                    if (_player->GetPrimarySpecialization() == ChrSpecialization::WarriorFury)
                    {
                        if (_player->HasSpell(772))
                            _player->CastSpell(target, 772, true);
                    }
                    else if (_player->GetPrimarySpecialization() == ChrSpecialization::WarriorProtection)
                    {
                        if (_player->HasSpell(394062))
                            _player->CastSpell(target, 394062, true);
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warr_thunder_clap_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_warr_thunder_clap_SpellScript();
    }
};

// 845 - Cleave
class spell_warr_cleave_dmg : public SpellScript
{

    void HandleOnHitTarget(SpellEffIndex /*effIndex*/)
    {
        if (Player* caster = GetCaster()->ToPlayer())
        {
            if (caster->HasAura(202316)) // Fervor of Battle
            {
                if (Unit* target = caster->GetSelectedUnit())
                {
                    if (caster->IsValidAttackTarget(target))
                    {
                        caster->CastSpell(target, SPELL_WARRIOR_SLAM_ARMS, true);
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warr_cleave_dmg::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

void AddSC_warrior_spell_scripts()
{
    RegisterSpellScript(spell_warr_avatar);
    RegisterSpellScript(spell_warr_bloodthirst);
    RegisterSpellScript(spell_warr_brutal_vitality);
    RegisterSpellScript(spell_warr_charge);
    RegisterSpellScript(spell_warr_charge_drop_fire_periodic);
    RegisterSpellScript(spell_warr_charge_effect);
    RegisterSpellScript(spell_warr_colossus_smash);
    RegisterSpellScript(spell_warr_critical_thinking);
    RegisterSpellScript(spell_warr_devastator);
    RegisterSpellScript(spell_warr_execute_damage);
    RegisterSpellScript(spell_warr_fueled_by_violence);
    RegisterSpellScript(spell_warr_heroic_leap);
    RegisterSpellScript(spell_warr_heroic_leap_jump);
    RegisterSpellScript(spell_warr_impending_victory);
    RegisterSpellScript(spell_warr_intimidating_shout);
    RegisterSpellScript(spell_warr_item_t10_prot_4p_bonus);
    RegisterSpellScript(spell_warr_mortal_strike);
    RegisterSpellScript(spell_warr_rallying_cry);
    RegisterSpellScript(spell_warr_rumbling_earth);
    RegisterSpellScript(spell_warr_shield_block);
    RegisterSpellScript(spell_warr_shield_charge);
    RegisterSpellScript(spell_warr_shockwave);
    RegisterSpellScript(spell_warr_storm_bolt);
    RegisterSpellScript(spell_warr_storm_bolts);
    RegisterSpellScript(spell_warr_strategist);
    RegisterSpellScript(spell_warr_sudden_death);
    RegisterSpellScript(spell_warr_sweeping_strikes);
    RegisterSpellScript(spell_warr_trauma);
    RegisterSpellScript(spell_warr_t3_prot_8p_bonus);
    RegisterSpellScript(spell_warr_victorious_state);
    RegisterSpellScript(spell_warr_victory_rush);

    //new
    new spell_warr_spell_reflect();
    RegisterSpellAndAuraScriptPair(spell_warr_ravager, aura_warr_ravager);
    RegisterCreatureAI(npc_warr_ravager);
    RegisterSpellScript(spell_warr_ravager_damage);
    RegisterSpellAndAuraScriptPair(spell_warr_ignore_pain, aura_warr_ignore_pain);
    new spell_warr_last_stand();
    new spell_warr_shattering_throw();
    new spell_warr_shout();
    RegisterSpellScript(spell_warr_wirlwind_dmg);
    RegisterSpellScript(spell_warr_shiel_charge);
    RegisterSpellScript(spell_warr_whirlwind);
    new spell_warr_unshackled_fury();
    new spell_warr_enrage();
    RegisterSpellScript(spell_warr_enrage_aura);
    new spell_warr_frothing_berserker();
    new spell_warr_odyns_fury();
    new anger_management();
    new spell_warr_overpower();
    new spell_warr_thunder_clap();
    RegisterSpellScript(spell_warr_cleave_dmg);
    new victory_rush_kill_event();
}
