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

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "CellImpl.h"
#include "Containers.h"
#include "Conversation.h"
#include "ConversationAI.h"
#include "CreatureAIImpl.h"
#include "EventProcessor.h"
#include "GridNotifiersImpl.h"
#include "MapUtils.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "PathGenerator.h"
#include "PassiveAI.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "TemporarySummon.h"

#define QUEST_THE_SHADOW_GRAVE 28608
#define NPC_DARNEL   49141

enum Texts {
    SAY_SPAWN = 0,
    SAY_THIS_WAY_1 = 1,
    SAY_THIS_WAY_2 = 2,
    SAY_RANDOM_MIN = 3,
    SAY_RANDOM_MAX = 8
};

// 49141 - darnell
struct npc_darnell_grave : public ScriptedAI
{
    npc_darnell_grave(Creature* creature) : ScriptedAI(creature)
    {
        checkTimer = 500;
        isWaiting = false;
        waitingForTrigger = true;
        isRandomPatrol = false;
        currentStep = 0;
    }

    ObjectGuid playerGUID;
    uint32 checkTimer;
    bool isWaiting;
    bool waitingForTrigger;
    bool isRandomPatrol;
    uint8 currentStep;

    const Position startPos = { 1695.540f, 1680.510f, 134.857f, 0.0f };

    void Reset() override
    {
        checkTimer = 500;
        isWaiting = false;
        waitingForTrigger = true;
        isRandomPatrol = false;
        currentStep = 0;
        me->SetReactState(REACT_PASSIVE);

        me->StopMoving();
        me->GetMotionMaster()->Clear();
        me->GetMotionMaster()->MoveIdle();
    }

    void IsSummonedBy(WorldObject* summoner) override
    {
        Player* player = nullptr;

        if (summoner->ToPlayer())
            player = summoner->ToPlayer();
        else
            player = me->SelectNearestPlayer(10.0f);

        if (player)
        {
            playerGUID = player->GetGUID();
            Talk(SAY_SPAWN);

            me->StopMoving();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
        }
        else
        {
            me->DespawnOrUnsummon(5000ms);
        }
    }

    void MovementInform(uint32 moveType, uint32 /*pointId*/) override
    {
        if (moveType != POINT_MOTION_TYPE)
            return;

        isWaiting = true;
        me->StopMoving();
        me->GetMotionMaster()->MoveIdle();

        if (isRandomPatrol)
        {
            Talk(urand(SAY_RANDOM_MIN, SAY_RANDOM_MAX));
        }
    }

    void UpdateAI(uint32 diff) override
    {
        Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
        if (!player)
            return;

        if (waitingForTrigger)
        {
            if (checkTimer <= diff)
            {
                if (player->GetMapId() == 0)
                {
                    if (player->IsWithinDist3d(startPos.GetPositionX(), startPos.GetPositionY(), startPos.GetPositionZ(), 5.0f))
                    {
                        waitingForTrigger = false;
                        StartEscort();
                    }
                }
                checkTimer = 500;
            }
            else
                checkTimer -= diff;

            return;
        }

        if (!isWaiting)
            return;

        if (checkTimer <= diff)
        {
            if (me->IsWithinDist(player, 2.0f))
            {
                ProcessNextStep();
            }
            checkTimer = 500;
        }
        else
            checkTimer -= diff;
    }

    void StartEscort()
    {
        currentStep = 1;
        Talk(SAY_THIS_WAY_1);
        me->GetMotionMaster()->MovePoint(1, 1665.368896f, 1662.722656f, 141.850983f);
    }

    void ProcessNextStep()
    {
        isWaiting = false;

        switch (currentStep)
        {
        case 1:
            Talk(SAY_THIS_WAY_2);
            me->GetMotionMaster()->MovePoint(2, 1642.761963f, 1662.547729f, 132.477753f);
            currentStep = 2;
            break;
        case 2:
            Talk(SAY_THIS_WAY_2);
            me->GetMotionMaster()->MovePoint(4, 1656.714478f, 1678.538330f, 120.718788f);
            currentStep = 3;
            break;
        case 3:
            isRandomPatrol = true;
            [[fallthrough]];
        case 4:
            MoveRandomPoint();
            currentStep = 4;
            break;
        }
    }

    void MoveRandomPoint()
    {
        switch (urand(1, 4))
        {
        case 1:
            me->GetMotionMaster()->MovePoint(4, 1663.849609f, 1694.495239f, 120.719284f);
            break;
        case 2:
            me->GetMotionMaster()->MovePoint(5, 1672.939331f, 1668.029541f, 120.719307f);
            break;
        case 3:
            me->GetMotionMaster()->MovePoint(6, 1656.963379f, 1667.456299f, 120.719093f);
            break;
        case 4:
            me->GetMotionMaster()->MovePoint(7, 1656.098999f, 1688.312866f, 120.719093f);
            break;
        }
    }
};

// 28608 - the shadow grave
class quest_the_shadow_grave : public QuestScript
{
public:
    quest_the_shadow_grave() : QuestScript("quest_the_shadow_grave") {}

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_COMPLETE)
        {
            std::list<Creature*> creatures;
            player->GetCreatureListWithEntryInGrid(creatures, NPC_DARNEL, 150.0f);
            for (Creature* c : creatures)
            {
                if (c->GetOwnerGUID() == player->GetGUID())
                    c->DespawnOrUnsummon();
            }
        }
    }
};

void AddSC_zone_tirisfal_glades()
{
    RegisterCreatureAI(npc_darnell_grave);
    new quest_the_shadow_grave();
}
