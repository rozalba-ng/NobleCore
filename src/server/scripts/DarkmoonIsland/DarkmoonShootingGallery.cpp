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
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "ScriptedCreature.h"
#include "DarkmoonIsland.h"
#include "Player.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptedEscortAI.h"
#include "WorldSession.h"
#include "Item.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "GameEventMgr.h"
#include "AchievementPackets.h"
#include "DB2HotfixGenerator.h"
#include "DB2Stores.h"
#include "CellImpl.h"
#include "ChatTextBuilder.h"
#include "Containers.h"
#include "DatabaseEnv.h"
#include "GameTime.h"
#include "GridNotifiersImpl.h"
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
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SharedDefines.h"
#include "ObjectAccessor.h"
#include "TemporarySummon.h"
#include <sstream>

enum HeShootsSpells
{
    SPELL_HESHOOTS_CRACKSHOT_ENABLE = 101871,
    SPELL_HESHOOTS_SHOOT = 101872,
    SPELL_HESHOOTS_TARGET_INDICATOR = 101010,
    SPELL_HESHOOTS_TARGET_INDICATOR_VISUAL = 43313,
    SPELL_HESHOOTS_KILL_CREDIT = 43300,
    SPELL_HESHOOTS_KILL_CREDIT_BONUS = 101012,
};

class npc_rinling_darkmoon : public CreatureScript
{
public:
    npc_rinling_darkmoon() : CreatureScript("npc_rinling_darkmoon") { }

    struct npc_rinling_darkmoonAI : public ScriptedAI
    {
        npc_rinling_darkmoonAI(Creature* creature) : ScriptedAI(creature)
        {
            Reset();
        }

        uint32 nextQuoteTimer;
        uint8 nextQuote;

        uint32 nextTargetChangeTimer;
        int8 targetIndex;
        ObjectGuid targetList[3];

        void Reset()
        {
            nextQuoteTimer = 40000 + urand(0, 15) * 10000;
            nextQuote = 0;
            nextTargetChangeTimer = 0;
            targetIndex = -1;
        }

        void UpdateAI(const uint32 diff)
        {
            if (nextTargetChangeTimer <= diff)
            {
                if (targetIndex < 0 || targetIndex >= 3)
                {
                    std::list<Creature*> crList;
                    GetCreatureListWithEntryInGrid(crList, me, 24171, 100.0f);
                    int i = 0;
                    for (std::list<Creature*>::const_iterator itr = crList.begin(); itr != crList.end(); ++itr)
                    {
                        targetList[i++] = (*itr)->GetGUID();
                        if (i >= 3)
                            break;
                    }
                }

                int8 chosen = -1;
                do
                {
                    // randomly choose one of targets
                    chosen = urand(0, 2);
                } while (chosen == targetIndex && urand(0, 1) == 0); // the same target could be chosen with only 50% chance (+-)

                targetIndex = chosen;

                Creature* creature_bunny = ObjectAccessor::GetCreature(*me, targetList[chosen]);
                if (creature_bunny)
                    creature_bunny->CastSpell(creature_bunny, SPELL_HESHOOTS_TARGET_INDICATOR, true);

                nextTargetChangeTimer = 4500 + urand(0, 1000);
            }
            else
                nextTargetChangeTimer -= diff;
        }

        bool OnGossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            AddGossipItemFor(player, 6225, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, 6225, 2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

            player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(me), me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*uiSender*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
                // Info
            case GOSSIP_ACTION_INFO_DEF + 1:
                AddGossipItemFor(player, 16972, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3); 
                    SendGossipMenuFor(player, 18353, me->GetGUID());
                break;
                // Ready to play
            case  GOSSIP_ACTION_INFO_DEF + 2:
                if (player->HasItemCount(ITEM_DARKMOON_TOKEN))
                {
                    CloseGossipMenuFor(player);

                    player->DestroyItemCount(ITEM_DARKMOON_TOKEN, 1, true);
                    player->CastSpell(player, SPELL_HESHOOTS_CRACKSHOT_ENABLE, TRIGGERED_FULL_MASK);

                    int16 progress = player->GetReqKillOrCastCurrentCount(QUEST_HE_SHOOTS_HE_SCORES, 54231);
                    if (progress > 0)
                        player->SetPower(POWER_ALTERNATE_POWER, progress);

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

            return false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rinling_darkmoonAI(creature);
    }
};

// spell - 101872
class spell_heshoots_shoot_hit : public SpellScriptLoader
{
public:
    spell_heshoots_shoot_hit() : SpellScriptLoader("spell_heshoots_shoot_hit") {}

    class spell_heshoots_shoot_hit_SpellScript : public SpellScript
    {
    private:
        void SetTargets(std::list<WorldObject*>& targets)
        {
            Unit* caster = GetCaster();
            if (!caster || !caster->ToPlayer())
                return;

            targets.clear();

            std::list<Creature*> potentialTargets;
            caster->GetCreatureListWithEntryInGrid(potentialTargets, 24171, 10.0f);

            for (Creature* creature : potentialTargets)
            {
                if (!creature->IsAlive() || !creature->HasAura(SPELL_HESHOOTS_TARGET_INDICATOR))
                    continue;

                if (!caster->HasInArc(static_cast<float>(M_PI / 12), creature))
                    continue;

                float startX = caster->GetPositionX();
                float startY = caster->GetPositionY();
                float startZ = caster->GetPositionZ() + caster->GetCollisionHeight() * 0.75f;

                float targetX = creature->GetPositionX();
                float targetY = creature->GetPositionY();
                float targetZ = creature->GetPositionZ() + creature->GetCollisionHeight() * 0.75f;

                float dx = targetX - startX;
                float dy = targetY - startY;
                float dz = targetZ - startZ;
                float distance = std::sqrt(dx * dx + dy * dy + dz * dz);

                if (distance > 10.0f)
                    continue;

                if (distance > 0)
                {
                    dx /= distance;
                    dy /= distance;
                    dz /= distance;
                }

                targets.push_back(creature);
            }
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            Player* player = caster->ToPlayer();
            if (!player)
                return;

            if (target->GetEntry() != 24171)
                return;

            if (Aura* shootAura = target->GetAura(SPELL_HESHOOTS_TARGET_INDICATOR))
            {
                target->CastSpell(player, SPELL_HESHOOTS_KILL_CREDIT, true);

                if (shootAura->GetMaxDuration() - shootAura->GetDuration() < 1200)
                {
                    target->CastSpell(player, SPELL_HESHOOTS_KILL_CREDIT_BONUS, true);
                    if (AchievementEntry const* achiev = sAchievementStore.LookupEntry(6022))
                        player->CompletedAchievement(achiev);
                }
            }
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_heshoots_shoot_hit_SpellScript::SetTargets, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_heshoots_shoot_hit_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_heshoots_shoot_hit_SpellScript();
    }
};

// spell - 101010
class spell_heshoots_indicator : public SpellScriptLoader
{
public:
    spell_heshoots_indicator() : SpellScriptLoader("spell_heshoots_indicator") { }

    class spell_heshoots_indicator_AuraScript : public AuraScript
    {

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Aura* aura = GetAura())
            {
                aura->SetDuration(3000);
                aura->SetMaxDuration(3000);

                TC_LOG_DEBUG("scripts", "Darkmoon Gallery: Set indicator aura duration to 3 seconds");
            }

            if (Unit* target = GetTarget())
            {
                target->CastSpell(target, SPELL_HESHOOTS_TARGET_INDICATOR_VISUAL, true);
            }
        }

        void EffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*modes*/)
        {
            if (!GetUnitOwner())
                return;

            GetUnitOwner()->RemoveAurasDueToSpell(SPELL_HESHOOTS_TARGET_INDICATOR_VISUAL);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_heshoots_indicator_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectApplyFn(spell_heshoots_indicator_AuraScript::EffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_heshoots_indicator_AuraScript();
    }
};

void AddSC_darkmoon_shooting_gallery()
{
    new npc_rinling_darkmoon();
    new spell_heshoots_shoot_hit();
    new spell_heshoots_indicator();
};
