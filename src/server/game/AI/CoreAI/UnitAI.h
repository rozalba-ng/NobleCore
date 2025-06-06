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

#ifndef TRINITY_UNITAI_H
#define TRINITY_UNITAI_H

#include "Errors.h"
#include "Hash.h"
#include "ObjectGuid.h"
#include "SharedDefines.h"
#include "SpellDefines.h"
#include "UnitAICommon.h"
#include <unordered_map>

#define CAST_AI(a, b)   (dynamic_cast<a*>(b))
#define ENSURE_AI(a,b)  (EnsureAI<a>(b))

template<class T, class U>
T* EnsureAI(U* ai)
{
    T* cast_ai = dynamic_cast<T*>(ai);
    ASSERT(cast_ai);
    return cast_ai;
}

class Player;
class Quest;
class SpellInfo;
class Unit;
struct AISpellInfoType;
enum DamageEffectType : uint8;
enum Difficulty : uint8;
enum MovementGeneratorType : uint8;
enum SpellEffIndex : uint8;

class TC_GAME_API UnitAI
{
    protected:
        Unit* const me;
    public:
        explicit UnitAI(Unit* unit) : me(unit) { }
        virtual ~UnitAI() { }

        virtual bool CanAIAttack(Unit const* /*target*/) const { return true; }
        virtual void AttackStart(Unit* victim);
        virtual void UpdateAI(uint32 diff) = 0;

        virtual void InitializeAI();

        virtual void Reset() { }

        // Called when unit's charm state changes with isNew = false
        // Implementation should call me->ScheduleAIChange() if AI replacement is desired
        // If this call is made, AI will be replaced on the next tick
        // When replacement is made, OnCharmed is called with isNew = true
        virtual void OnCharmed(bool isNew);

        // Pass parameters between AI
        virtual void DoAction([[maybe_unused]] int32 param) { }
        virtual uint32 GetData([[maybe_unused]] uint32 id) const { return 0; }
        virtual void SetData([[maybe_unused]] uint32 id, [[maybe_unused]] uint32 value) { }
        virtual void SetGUID([[maybe_unused]] ObjectGuid const& guid, [[maybe_unused]] int32 id) { }
        virtual ObjectGuid GetGUID([[maybe_unused]] int32 id) const { return ObjectGuid::Empty; }

        // Select the best target (in <targetType> order) from the threat list that fulfill the following:
        // - Not among the first <offset> entries in <targetType> order (or SelectTargetMethod::MaxThreat order,
        //   if <targetType> is SelectTargetMethod::Random).
        // - Within at most <dist> yards (if dist > 0.0f)
        // - At least -<dist> yards away (if dist < 0.0f)
        // - Is a player (if playerOnly = true)
        // - Not the current tank (if withTank = false)
        // - Has aura with ID <aura> (if aura > 0)
        // - Does not have aura with ID -<aura> (if aura < 0)
        Unit* SelectTarget(SelectTargetMethod targetType, uint32 offset = 0, float dist = 0.0f, bool playerOnly = false, bool withTank = true, int32 aura = 0);

        // Select the best target (in <targetType> order) satisfying <predicate> from the threat list.
        // If <offset> is nonzero, the first <offset> entries in <targetType> order (or SelectTargetMethod::MaxThreat
        // order, if <targetType> is SelectTargetMethod::Random) are skipped.
        template<class PREDICATE>
        Unit* SelectTarget(SelectTargetMethod targetType, uint32 offset, PREDICATE const& predicate)
        {
            std::list<Unit*> targetList;
            SelectTargetList(targetList, std::numeric_limits<uint32>::max(), targetType, offset, predicate);

            return FinalizeTargetSelection(targetList, targetType);
        }

        // Select the best (up to) <num> targets (in <targetType> order) from the threat list that fulfill the following:
        // - Not among the first <offset> entries in <targetType> order (or SelectTargetMethod::MaxThreat order,
        //   if <targetType> is SelectTargetMethod::Random).
        // - Within at most <dist> yards (if dist > 0.0f)
        // - At least -<dist> yards away (if dist < 0.0f)
        // - Is a player (if playerOnly = true)
        // - Not the current tank (if withTank = false)
        // - Has aura with ID <aura> (if aura > 0)
        // - Does not have aura with ID -<aura> (if aura < 0)
        // The resulting targets are stored in <targetList> (which is cleared first).
        void SelectTargetList(std::list<Unit*>& targetList, uint32 num, SelectTargetMethod targetType, uint32 offset = 0, float dist = 0.0f, bool playerOnly = false, bool withTank = true, int32 aura = 0);

        // Select the best (up to) <num> targets (in <targetType> order) satisfying <predicate> from the threat list and stores them in <targetList> (which is cleared first).
        // If <offset> is nonzero, the first <offset> entries in <targetType> order (or SelectTargetMethod::MaxThreat
        // order, if <targetType> is SelectTargetMethod::Random) are skipped.
        template <class PREDICATE>
        void SelectTargetList(std::list<Unit*>& targetList, uint32 num, SelectTargetMethod targetType, uint32 offset, PREDICATE const& predicate)
        {
            if (!PrepareTargetListSelection(targetList, targetType, offset))
                return;

            // then finally filter by predicate
            targetList.remove_if([&predicate](Unit* target) { return !predicate(target); });

            FinalizeTargetListSelection(targetList, num, targetType);
        }

        // Called when the unit enters combat
        // (NOTE: Creature engage logic should NOT be here, but in JustEngagedWith, which happens once threat is established!)
        virtual void JustEnteredCombat(Unit* /*who*/) { }

        // Called when the unit leaves combat
        virtual void JustExitedCombat() { }

        // Called when the unit is about to be removed from the world (despawn, grid unload, corpse disappearing, player logging out etc.)
        virtual void OnDespawn() { }

        // Called at any Damage to any victim (before damage apply)
        virtual void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType /*damageType*/) { }

        // Called at any Damage from any attacker (before damage apply)
        // Note: it for recalculation damage or special reaction at damage
        virtual void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) { }

        // Called when the creature receives heal
        virtual void HealReceived(Unit* /*done_by*/, uint32& /*addhealth*/) { }

        // Called when the unit heals
        virtual void HealDone(Unit* /*done_to*/, uint32& /*addhealth*/) { }

        /// Called when a spell is interrupted by Spell::EffectInterruptCast
        /// Use to reschedule next planned cast of spell.
        virtual void SpellInterrupted(uint32 /*spellId*/, uint32 /*unTimeMs*/) { }

        void AttackStartCaster(Unit* victim, float dist);

        SpellCastResult DoCast(uint32 spellId);
        SpellCastResult DoCast(Unit* victim, uint32 spellId, CastSpellExtraArgs const& args = {});
        SpellCastResult DoCastSelf(uint32 spellId, CastSpellExtraArgs const& args = {}) { return DoCast(me, spellId, args); }
        SpellCastResult DoCastVictim(uint32 spellId, CastSpellExtraArgs const& args = {});
        SpellCastResult DoCastAOE(uint32 spellId, CastSpellExtraArgs const& args = {}) { return DoCast(nullptr, spellId, args); }

        bool DoSpellAttackIfReady(uint32 spellId);

        static std::unordered_map<std::pair<uint32, Difficulty>, AISpellInfoType> AISpellInfo;
        static void FillAISpellInfo();

        // Called when a game event starts or ends
        virtual void OnGameEvent(bool /*start*/, uint16 /*eventId*/) { }

        virtual std::string GetDebugInfo() const;

    private:
        UnitAI(UnitAI const& right) = delete;
        UnitAI& operator=(UnitAI const& right) = delete;

        Unit* FinalizeTargetSelection(std::list<Unit*>& targetList, SelectTargetMethod targetType);
        bool PrepareTargetListSelection(std::list<Unit*>& targetList, SelectTargetMethod targetType, uint32 offset);
        void FinalizeTargetListSelection(std::list<Unit*>& targetList, uint32 num, SelectTargetMethod targetType);

    public:
        /// Add timed delayed operation
        /// @p_Timeout  : Delay time
        /// @p_Function : Callback function
        void AddTimedDelayedOperation(uint32 p_Timeout, std::function<void()>&& p_Function)
        {
            m_EmptyWarned = false;
            m_TimedDelayedOperations.push_back(std::pair<uint32, std::function<void()>>(p_Timeout, p_Function));
        }

        /// Called after last delayed operation was deleted
        /// Do whatever you want
        virtual void LastOperationCalled() { }

        void ClearDelayedOperations()
        {
            m_TimedDelayedOperations.clear();
            m_EmptyWarned = false;
        }

        std::vector<std::pair<int32, std::function<void()>>>    m_TimedDelayedOperations;   ///< Delayed operations
        bool                                                    m_EmptyWarned;              ///< Warning when there are no more delayed operations
        void SetBaseAttackSpell(uint32 spellId) { _baseAttackSpell = spellId; }
        uint32 GetBaseAttackSpell() { return _baseAttackSpell; }

       private:
           uint32 _baseAttackSpell = 0;
};

namespace Trinity
{
    // Binary predicate for sorting Units based on percent value of a power
    class PowerPctOrderPred
    {
    public:
        PowerPctOrderPred(Powers power, bool ascending = true) : _power(power), _ascending(ascending) { }

        bool operator()(WorldObject const* objA, WorldObject const* objB) const
        {
            Unit const* a = objA->ToUnit();
            Unit const* b = objB->ToUnit();
            float rA = a ? a->GetPowerPct(_power) : 0.0f;
            float rB = b ? b->GetPowerPct(_power) : 0.0f;
            return _ascending ? rA < rB : rA > rB;
        }

        bool operator()(Unit const* a, Unit const* b) const
        {
            float rA = a->GetPowerPct(_power);
            float rB = b->GetPowerPct(_power);
            return _ascending ? rA < rB : rA > rB;
        }

    private:
        Powers const _power;
        bool const _ascending;
    };

    // Binary predicate for sorting Units based on percent value of health
    class HealthPctOrderPred
    {
    public:
        HealthPctOrderPred(bool ascending = true) : _ascending(ascending) { }

        bool operator()(WorldObject const* objA, WorldObject const* objB) const
        {
            Unit const* a = objA->ToUnit();
            Unit const* b = objB->ToUnit();
            float rA = (a && a->GetMaxHealth()) ? float(a->GetHealth()) / float(a->GetMaxHealth()) : 0.0f;
            float rB = (b && b->GetMaxHealth()) ? float(b->GetHealth()) / float(b->GetMaxHealth()) : 0.0f;
            return _ascending ? rA < rB : rA > rB;
        }

        bool operator() (Unit const* a, Unit const* b) const
        {
            float rA = a->GetMaxHealth() ? float(a->GetHealth()) / float(a->GetMaxHealth()) : 0.0f;
            float rB = b->GetMaxHealth() ? float(b->GetHealth()) / float(b->GetMaxHealth()) : 0.0f;
            return _ascending ? rA < rB : rA > rB;
        }

    private:
        bool const _ascending;
    };
}

#endif
