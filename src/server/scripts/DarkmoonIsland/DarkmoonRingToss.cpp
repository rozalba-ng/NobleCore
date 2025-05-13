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

// 54485 - Jessica Rogers
class npc_jessica_rogers : public CreatureScript
{
public:
    npc_jessica_rogers() : CreatureScript("npc_jessica_rogers") { }

    struct npc_jessica_rogersAI : public ScriptedAI
    {
        npc_jessica_rogersAI(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            AddGossipItemFor(player, 13012, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);            
            AddGossipItemFor(player, 13012, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                
            player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(me), me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                AddGossipItemFor(player, 13013, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    SendGossipMenuFor(player, 18286, me->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                if (player->HasItemCount(ITEM_DARKMOON_TOKEN, 1))
                {
                    CloseGossipMenuFor(player);

                    player->DestroyItemCount(ITEM_DARKMOON_TOKEN, 1, true);
                    player->RemoveAurasByType(SPELL_AURA_MOUNTED);

                    player->AddAura(SPELL_RINGTOSS_ENABLE, player);
                    player->SetPower(POWER_ALTERNATE_POWER, 10);

                    return true;
                }
                else
                {
                    player->PlayerTalkClass->ClearMenus();
                    return OnGossipHello(player);
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->PlayerTalkClass->ClearMenus();
                return OnGossipHello(player);
                break;
            }
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_jessica_rogersAI(creature);
    }
};

// spell - 101695
class spell_ring_toss : public SpellScriptLoader
{
public:
    spell_ring_toss() : SpellScriptLoader("spell_ring_toss") {}

    class spell_ring_toss_SpellScript : public SpellScript
    {

        SpellCastResult CheckRequirement()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();

            WorldLocation* loc = GetHitDest();

            Creature* dubenko = caster->FindNearestCreature(54490, 100.0f, true);

            if (dubenko && dubenko->IsWithinDist2d(loc, 1.2f))
            {
                if (dubenko->HasAura(SPELL_RINGTOSS_TURTLE_CIRCLE_1))
                {
                    if (dubenko->HasAura(SPELL_RINGTOSS_TURTLE_CIRCLE_2))
                        dubenko->CastSpell(dubenko, SPELL_RINGTOSS_TURTLE_CIRCLE_3, true);
                    else
                        dubenko->CastSpell(dubenko, SPELL_RINGTOSS_TURTLE_CIRCLE_2, true);
                }
                else
                    dubenko->CastSpell(dubenko, SPELL_RINGTOSS_TURTLE_CIRCLE_1, true);

                caster->CastSpell(dubenko, SPELL_RINGTOSS_HIT, false);
            }          
        }
                        

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ring_toss_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_ring_toss_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ring_toss_SpellScript();
    }
};

// at_target_turtle - 7338
class at_target_turtle : public AreaTriggerScript
{
public:
    at_target_turtle() : AreaTriggerScript("at_target_turtle") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (!player->IsGameMaster())
            player->CastSpell(player, 109972, true);
        return true;
    }
};

void AddSC_darkmoon_ring_toss()
{
    new npc_jessica_rogers();
	new spell_ring_toss();
	new at_target_turtle();
};
