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

enum {
    NPC_BROTHER_PAXTON = 951,

    NPC_HEAL_TARGET = 49869,
    NPC_WOLF = 49871,

    SPELL_HEAL_1 = 93091,
    SPELL_HEAL_2 = 93094,

    ACTION_TALK_EVENT = 1
};

// 49869
struct npc_stormwind_infantry : public ScriptedAI
{
    explicit npc_stormwind_infantry(Creature* creature) : ScriptedAI(creature) {}

    TaskScheduler _scheduler;
    uint32 talkCooldown = 0;

    void JustAppeared() override
    {
        ScriptedAI::JustAppeared();
        talkCooldown = urand(10000, 30000);
        ScheduleCombatCheck();
    }

    void Reset() override
    {
        me->SetSheath(SHEATH_STATE_MELEE);
    }

    void ScheduleCombatCheck()
    {
        _scheduler.Schedule(2s, [this](TaskContext context)
            {
                if (!me->IsInCombat())
                {
                    if (me->GetDistance(me->GetHomePosition()) < 2.0f)
                    {
                        if (Creature* wolf = me->FindNearestCreature(NPC_WOLF, 10.0f))
                        {
                            if (wolf->IsAlive() && !wolf->IsInCombat())
                            {
                                AttackStart(wolf);

                                if (wolf->IsAIEnabled())
                                    wolf->AI()->AttackStart(me);
                            }
                        }
                    }
                }

                context.Repeat(2s);
            });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);

        if (talkCooldown <= diff)
        {
            Talk(0);

            if (Creature* paxton = me->FindNearestCreature(NPC_BROTHER_PAXTON, 30.0f))
            {
                if (paxton->IsAIEnabled())
                    paxton->AI()->DoAction(ACTION_TALK_EVENT);
            }

            talkCooldown = urand(30000, 120000);
        }
        else
        {
            talkCooldown -= diff;
        }

        if (!UpdateVictim())
            return;

        if (me->isAttackReady() && me->IsWithinMeleeRange(me->GetVictim()))
        {
            me->AttackerStateUpdate(me->GetVictim());
            me->resetAttackTimer();
        }
    }
};

// 951
struct npc_brother_paxton : public ScriptedAI
{
    explicit npc_brother_paxton(Creature* creature) : ScriptedAI(creature) {}

    void DoAction(int32 action) override
    {
        if (action == ACTION_TALK_EVENT)
        {
            std::list<Creature*> targets;
            me->GetCreatureListWithEntryInGrid(targets, NPC_HEAL_TARGET, 30.0f);

            for (Creature* target : targets)
            {
                if (target->IsAlive())
                {
                    Talk(0);
                    me->CastSpell(target, RAND(SPELL_HEAL_1, SPELL_HEAL_2), true);
                }
            }
        }
    }
};

void AddSC_zone_elwyn_forest()
{
    // Northshire zone
    RegisterCreatureAI(npc_stormwind_infantry);
    RegisterCreatureAI(npc_brother_paxton);
}
