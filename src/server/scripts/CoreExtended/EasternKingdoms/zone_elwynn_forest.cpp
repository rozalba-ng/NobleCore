#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ObjectMgr.h"
#include "World.h"
#include "PetAI.h"
#include "PassiveAI.h"
#include "CombatAI.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "Player.h"
#include "SpellScript.h"
#include "CreatureAI.h"
#include "TemporarySummon.h"

// 49869
struct npc_stormwind_infantry : public ScriptedAI
{
    explicit npc_stormwind_infantry(Creature* creature) : ScriptedAI(creature) {}

    uint32 waitTime = 0;
    uint32 talkCooldown = 0;
    uint32 swingTimer = 0;
    ObjectGuid wolfTarget;

    void Reset() override
    {
        wolfTarget.Clear();
        me->SetSheath(SHEATH_STATE_MELEE);

        swingTimer = me->GetBaseAttackTime(BASE_ATTACK);

        waitTime = urand(3000, 8000);
    }

    void DamageTaken(Unit* /*doneBy*/, uint32& /*damage*/, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override
    {
        if (talkCooldown > 0)
            return;

        if (me->GetHealthPct() <= 70.0f)
        {
            Talk(urand(0, 3));
            talkCooldown = 25000;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (wolfTarget.IsEmpty())
        {
            if (waitTime)
            {
                if (waitTime <= diff)
                    waitTime = 0;
                else
                {
                    waitTime -= diff;
                    return;
                }
            }
        }

        if (!wolfTarget.IsEmpty())
        {
            Creature* wolf = me->GetMap()->GetCreature(wolfTarget);

            if (!wolf || !wolf->IsAlive())
            {
                wolfTarget.Clear();
                waitTime = urand(5000, 10000);
                me->AttackStop();
                me->GetMotionMaster()->MoveIdle();
                return;
            }

            if (me->GetVictim() != wolf)
            {
                me->Attack(wolf, true);
                me->GetMotionMaster()->MoveChase(wolf);
            }

            if (wolf->IsAIEnabled() && wolf->GetVictim() != me)
            {
                wolf->Attack(me, true);
                wolf->GetMotionMaster()->MoveChase(me);
            }

            if (swingTimer <= diff)
            {
                if (!me->HasUnitState(UNIT_STATE_CASTING))
                {
                    if (me->IsWithinMeleeRange(wolf))
                        me->AttackerStateUpdate(wolf, BASE_ATTACK);

                    me->setAttackTimer(BASE_ATTACK, me->GetBaseAttackTime(BASE_ATTACK));

                    me->EngageWithTarget(wolf);
                }
                else
                    swingTimer = 500;
            }
            else
            {
                swingTimer -= diff;
            }

            return;
        }

        if (wolfTarget.IsEmpty() && waitTime == 0)
        {
            if (Creature* wolf = me->FindNearestCreature(49871, 15.0f))
            {
                if (wolf->IsAlive())
                {
                    wolfTarget = wolf->GetGUID();

                    me->Attack(wolf, true);
                    me->GetMotionMaster()->MoveChase(wolf);

                    if (wolf->IsAIEnabled())
                    {
                        wolf->Attack(me, true);
                        wolf->GetMotionMaster()->MoveChase(me);
                    }

                    swingTimer = me->GetBaseAttackTime(BASE_ATTACK);

                    me->setAttackTimer(BASE_ATTACK, me->GetBaseAttackTime(BASE_ATTACK));
                }
            }
            else
            {
                waitTime = 5000;
            }
        }
    }
};

void AddSC_zone_elwyn_forest()
{
    // Northshire zone
    RegisterCreatureAI(npc_stormwind_infantry);
}
