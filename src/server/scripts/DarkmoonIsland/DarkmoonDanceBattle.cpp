/*
 * This file is part of the RoleplayCore Project. See AUTHORS file for Copyright information
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
 
#include "ScriptMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "ScriptedGossip.h"
#include "MotionMaster.h"
#include "GameObject.h"
#include "Transport.h"
#include "DarkmoonIsland.h"
#include "AchievementMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "ScriptedEscortAI.h"
#include "WorldSession.h"
#include "Item.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "GameEventMgr.h"
#include "AchievementPackets.h"
#include "DB2HotfixGenerator.h"
#include "DB2Stores.h"
#include "ChatTextBuilder.h"
#include "Containers.h"
#include "DatabaseEnv.h"
#include "GameTime.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Language.h"
#include "Mail.h"
#include "ObjectMgr.h"
#include "RBAC.h"
#include "StringConvert.h"
#include "World.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "CreatureAI.h"
#include "CreatureAIImpl.h"
#include "SharedDefines.h"
#include "TemporarySummon.h"
#include <sstream>

// npc - 181097 WIP
class npc_dance_battle_simon_sezdans : public CreatureScript
{
public:
    npc_dance_battle_simon_sezdans() : CreatureScript("npc_dance_battle_simon_sezdans") { }

    struct npc_dance_battle_simon_sezdansAI : public ScriptedAI
    {
        npc_dance_battle_simon_sezdansAI(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            AddGossipItemFor(player, 26818, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, 26818, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

            player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(me), me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
                //Info
            case GOSSIP_ACTION_INFO_DEF + 1:
                AddGossipItemFor(player, 16972, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    SendGossipMenuFor(player, 42770, me->GetGUID());
                break;
                // Ready to play
            case GOSSIP_ACTION_INFO_DEF + 2:
                AddGossipItemFor(player, 26888, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);                   
                AddGossipItemFor(player, 26888, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);                   
                AddGossipItemFor(player, 26888, 2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);                   
                AddGossipItemFor(player, 26888, 3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                    SendGossipMenuFor(player, 42798, me->GetGUID());
                break;
                // Understand
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->PlayerTalkClass->ClearMenus();
                return OnGossipHello(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->CastSpell(player, 349094, true);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->CastSpell(player, 351278, true);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->CastSpell(player, 351277, true);
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                player->PlayerTalkClass->ClearMenus();
                return OnGossipHello(player);
                break;
            }

            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dance_battle_simon_sezdansAI(creature);
    }
};

// 2709 - Darkmoon Dance Scene
class scene_darkmoon_dance_battle : public SceneScript
{
public:
    scene_darkmoon_dance_battle() : SceneScript("scene_darkmoon_dance_battle") { }

    void OnSceneTriggerEvent(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/, std::string const& triggerName) override
    {
        if (triggerName == "Game Over Easy Victory")
        {
            player->KilledMonsterCredit(181137);

            if (!player->HasAchieved(ACHIEVEMENT_YOU_GOT_THE_BEAT))
            {
                AchievementEntry const* achiev = sAchievementStore.LookupEntry(ACHIEVEMENT_YOU_GOT_THE_BEAT);
                if (player)
                    player->CompletedAchievement(achiev);
            }
        }
        else if (triggerName == "Game Over Medium Victory")
        {
            player->KilledMonsterCredit(181139);

            if (!player->HasAchieved(ACHIEVEMENT_WHAT_A_FEELING))
            {
                AchievementEntry const* achiev = sAchievementStore.LookupEntry(ACHIEVEMENT_WHAT_A_FEELING);
                if (player)
                    player->CompletedAchievement(achiev);
            }
        }
        else if (triggerName == "Game Over Hard Victory")
        {
            player->KilledMonsterCredit(181141);

            if (!player->HasAchieved(ACHIEVEMENT_MAKE_YOU_SWEAT))
            {
                AchievementEntry const* achiev = sAchievementStore.LookupEntry(ACHIEVEMENT_MAKE_YOU_SWEAT);
                if (player)
                    player->CompletedAchievement(achiev);
            }
        }
        else if (triggerName == "Game Over Easy Pass")
        {
            player->KilledMonsterCredit(181136);
        }
        else if (triggerName == "Game Over Medium Pass")
        {
            player->KilledMonsterCredit(181138);
        }
        else if (triggerName == "Game Over Hard Pass")
        {
            player->KilledMonsterCredit(181140);
        }
        else if (triggerName == "Eject")
        {
            player->KilledMonsterCredit(181142);
        }
    }

    void OnSceneComplete(Player* player, uint32 /*sceneInstanceID*/, SceneTemplate const* /*sceneTemplate*/) override
    {
        if (!player->HasAchieved(ACHIEVEMENT_FIRST_DANCE))
        {
            AchievementEntry const* achiev = sAchievementStore.LookupEntry(ACHIEVEMENT_FIRST_DANCE);
            if (player)
                player->CompletedAchievement(achiev);
        }
        else if (player->HasAchieved(ACHIEVEMENT_FIRST_DANCE) && player->HasAchieved(ACHIEVEMENT_YOU_GOT_THE_BEAT) && player->HasAchieved(ACHIEVEMENT_WHAT_A_FEELING) && player->HasAchieved(ACHIEVEMENT_MAKE_YOU_SWEAT))
        {
            if (!player->HasAchieved(ACHIEVEMENT_DANCING_MACHINE))
            {
                AchievementEntry const* achiev = sAchievementStore.LookupEntry(ACHIEVEMENT_DANCING_MACHINE);
                if (player)
                    player->CompletedAchievement(achiev);
            }
        }
    }
};

void AddSC_darkmoon_dance_battle()
{
    new scene_darkmoon_dance_battle();
    new npc_dance_battle_simon_sezdans();
};
