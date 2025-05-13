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
#include "ScriptedCreature.h"
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
#include "TemporarySummon.h"
#include "Vehicle.h"
#include <sstream>
#include <G3D/Quat.h>

enum TonkSpells
{
    SPELL_TONK_ENABLE                   = 102178,
    SPELL_TONK_SHOOT                    = 24933, //27766
    SPELL_TONK_NITRO_BOOST              = 102297,
    SPELL_TONK_KILL_CREDIT              = 110162,
    SPELL_TONK_STAY_OUT                 = 109976,

    SPELL_ENEMY_TONK_MARKED             = 102341,
    SPELL_ENEMY_TONK_CANNON_BLAST       = 102227,
};

enum TonkNPCs
{
    NPC_PLAYER_TONK                     = 54588,
    NPC_ENEMY_TONK                      = 54642,
    NPC_ENEMY_MINIZEP                   = 54643,
    NPC_TONK_TARGET                     = 33081,
};

#define TONK_TARGET_POSITION_COUNT 33

const Position tonkTargetPositions[TONK_TARGET_POSITION_COUNT] = {
    {-4145.988770f, 6290.719727f, 13.116899f, 0.499545f},
    {-4137.421387f, 6289.625977f, 13.116899f, 1.210661f},
    {-4133.106934f, 6296.116699f, 13.116899f, 2.729411f},
    {-4139.067383f, 6300.952148f, 13.116899f, 0.894536f},
    {-4139.654297f, 6305.813477f, 13.116899f, 0.671786f},
    {-4143.446777f, 6308.530762f, 13.116899f, 2.021786f},
    {-4148.482910f, 6308.563965f, 13.116899f, 0.614411f},
    {-4147.683105f, 6300.739258f, 13.116899f, 0.972161f},
    {-4145.276855f, 6304.266602f, 13.116899f, 0.972161f},
    {-4142.250000f, 6312.737793f, 13.116899f, 0.297161f},
    {-4137.417480f, 6316.265137f, 13.116899f, 6.023472f},
    {-4133.054688f, 6318.007813f, 13.116899f, 5.348472f},
    {-4127.991211f, 6313.178223f, 13.116899f, 2.551661f},
    {-4125.186035f, 6313.233398f, 13.116899f, 3.395411f},
    {-4122.878418f, 6307.192383f, 13.116899f, 3.395411f},
    {-4126.788574f, 6306.019043f, 13.116899f, 2.274911f},
    {-4124.875977f, 6300.727051f, 13.116899f, 3.176036f},
    {-4123.939941f, 6299.044434f, 13.116899f, 2.328911f},
    {-4126.655762f, 6294.246094f, 13.116899f, 2.328911f},
    {-4129.494141f, 6294.895020f, 13.116899f, 1.205036f},
    {-4131.038086f, 6292.043457f, 13.116899f, 2.575286f},
    {-4135.638184f, 6288.404785f, 13.116899f, 1.750661f},
    {-4137.863770f, 6292.131836f, 13.116899f, 1.075661f},
    {-4137.863770f, 6297.746094f, 13.116899f, 1.755162f},
    {-4135.811523f, 6302.905762f, 13.116517f, 1.755162f},
    {-4133.516113f, 6307.136719f, 13.116517f, 1.755162f},
    {-4143.302246f, 6310.689941f, 13.116517f, 0.573911f},
    {-4148.054688f, 6297.366211f, 13.116712f, 5.652222f},
    {-4139.401855f, 6294.312500f, 13.116712f, 0.047411f},
    {-4119.912109f, 6299.708496f, 13.116712f, 4.221162f},
    {-4120.738281f, 6306.735352f, 13.116712f, 3.097287f},
    {-4125.261719f, 6317.238281f, 13.116712f, 3.154662f},
    {-4135.285645f, 6321.727539f, 13.116712f, 4.992911f}
};

const Position playerSpawnPosition = { -4130.196777f, 6320.329102f, 13.116393f, 4.368710f };
const Position playerKickPosition = { -4125.278809f, 6332.548828f, 12.219045f, 4.313733f };
const Position circleCenterPosition = { -4135.632813f, 6302.201172f, 13.116685f, 1.336366f };
const float circleBattleRadius = 17.0f;

#define FINLAY_QUOTE_1 "Hey, hey! Command a tonk in glorious battle!"
#define FINLAY_QUOTE_2 "Step right up and try a tonk!"
#define FINLAY_QUOTE_3 "Tonks! We got tonks here!"
#define FINLAY_QUOTE_4 "We're under attack! Step up and do your part!"

#define FINLAY_QUOTES_TOTAL 4
const char* finlayQuotes[FINLAY_QUOTES_TOTAL] = {
    FINLAY_QUOTE_1, FINLAY_QUOTE_2, FINLAY_QUOTE_3, FINLAY_QUOTE_4
};

struct TargetSpawn
{
    ObjectGuid guid;
    uint8 pos;
    uint32 nextSpawnTime;
    uint32 nextCheckTime;
};

#define TONK_TARGETS_MAX 8

class npc_finlay_darkmoon : public CreatureScript
{
public:
    npc_finlay_darkmoon() : CreatureScript("npc_finlay_darkmoon") { }

    struct npc_finlay_darkmoonAI : public ScriptedAI
    {
        npc_finlay_darkmoonAI(Creature* c) : ScriptedAI(c)
        {
            spawnedTonks = false;
            Reset();
        }

        uint32 nextQuoteTimer;
        uint32 nextCheckTimer;
        uint8 nextQuote;
        TargetSpawn targetSpawns[TONK_TARGETS_MAX];
        bool spawnedTonks;

        void Reset()
        {
            nextQuoteTimer = urand(1, 60) * 1000;
            nextCheckTimer = 1000;
            nextQuote = 0;

            memset(&targetSpawns, 0, sizeof(targetSpawns));

            if (!spawnedTonks)
            {
                uint8 point;
                for (uint32 i = 0; i < 3; i++)
                {
                    point = urand(0, TONK_TARGET_POSITION_COUNT);
                    me->SummonCreature(NPC_ENEMY_TONK, tonkTargetPositions[point], TEMPSUMMON_MANUAL_DESPAWN);
                }
                spawnedTonks = true;
            }
        }

        bool IsSpawnAtPos(uint8 pos)
        {
            for (uint32 i = 0; i < TONK_TARGETS_MAX; i++)
            {
                if (pos == targetSpawns[i].pos)
                    return true;
            }
            return false;
        }

        void UpdateAI(const uint32 diff)
        {
            if (nextQuoteTimer <= diff)
            {
                nextQuoteTimer = 30000 + urand(0, 15) * 10000; // 30 - 180s (step by 10s, not so big importance)
                me->Say(54605, me);

                nextQuote++;
                if (nextQuote >= FINLAY_QUOTES_TOTAL)
                    nextQuote = 0;
            }
            else
                nextQuoteTimer -= diff;

            if (nextCheckTimer <= diff)
            {
                Map::PlayerList const& plList = me->GetMap()->GetPlayers();
                Player* tmp;
                for (Map::PlayerList::const_iterator itr = plList.begin(); itr != plList.end(); ++itr)
                {
                    tmp = itr->GetSource();
                    if (!tmp)
                        continue;

                    // is further - dont care
                    if (!tmp->IsWithinDist2d(&circleCenterPosition, circleBattleRadius))
                        continue;

                    // has enable aura - dont care
                    if (tmp->HasAura(SPELL_TONK_ENABLE))
                        continue;

                    tmp->CastSpell(tmp, SPELL_TONK_STAY_OUT, true);
                }

                nextCheckTimer = 500;
            }
            else
                nextCheckTimer -= diff;

            for (uint32 i = 0; i < TONK_TARGETS_MAX; i++)
            {
                if (targetSpawns[i].nextCheckTime <= diff)
                {
                    Creature* cr = ObjectAccessor::GetCreature(*me, targetSpawns[i].guid);
                    if (!cr || cr->isDead())
                    {
                        targetSpawns[i].nextSpawnTime = 2000;
                        targetSpawns[i].nextCheckTime = 5000;
                    }
                    else
                    {
                        targetSpawns[i].nextCheckTime = 2000;
                    }
                }
                else
                    targetSpawns[i].nextCheckTime -= diff;

                if (targetSpawns[i].nextSpawnTime <= diff)
                {
                    targetSpawns[i].nextSpawnTime = urand(20000, 40000);
                    if (Creature* cr = ObjectAccessor::GetCreature(*me, targetSpawns[i].guid))
                    {
                        cr->DespawnOrUnsummon(1s);
                    }

                    uint8 chosen = 0;
                    do
                    {
                        chosen = urand(0, TONK_TARGET_POSITION_COUNT);
                    } while (IsSpawnAtPos(chosen));

                    targetSpawns[i].pos = chosen;

                    Creature* cr = me->SummonCreature(NPC_TONK_TARGET, tonkTargetPositions[chosen], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000ms);
                    if (cr)
                        targetSpawns[i].guid = cr->GetGUID();
                }
                else
                    targetSpawns[i].nextSpawnTime -= diff;
            }
        }

        bool OnGossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            AddGossipItemFor(player, 13019, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            AddGossipItemFor(player, 13019, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

            player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(me), me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            switch (action)
            {
                // Info
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->PlayerTalkClass->ClearMenus();
                AddGossipItemFor(player, 16972, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                SendGossipMenuFor(player, 18352, me->GetGUID());
                return true;
                // Play
            case  GOSSIP_ACTION_INFO_DEF + 2:
                if (player->HasItemCount(ITEM_DARKMOON_TOKEN, 1))
                {
                    player->DestroyItemCount(ITEM_DARKMOON_TOKEN, 1, true);
                    player->RemoveAurasByType(SPELL_AURA_MOUNTED);
                    player->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

                    Creature* summon = player->SummonCreature(NPC_PLAYER_TONK, playerSpawnPosition, TEMPSUMMON_MANUAL_DESPAWN, 0s);
                    if (summon)
                    {
                        summon->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                        summon->SetUnitFlag(UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                        summon->SetImmuneToAll(true);
                        player->EnterVehicle(summon, 0);
                        player->CastSpell(player, SPELL_TONK_ENABLE, true);
                        summon->SetImmuneToAll(true);

                        int16 progress = player->GetReqKillOrCastCurrentCount(QUEST_TONK_COMMANDER, 33081);
                        if (progress > 0)
                            player->SetPower(POWER_ALTERNATE_POWER, progress);
                    }
                }
                else
                {
                    player->PlayerTalkClass->ClearMenus();
                    return OnGossipHello(player);
                }
                return true;
                // "I understand"
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->PlayerTalkClass->ClearMenus();
                return OnGossipHello(player);
            }

            return false;
        }
    };

    CreatureAI* GetAI(Creature* c) const
    {
        return new npc_finlay_darkmoonAI(c);
    }
};

class spell_tonk_enable : public SpellScriptLoader
{
public:
    spell_tonk_enable() : SpellScriptLoader("spell_tonk_enable") { }

    class spell_tonk_enable_AuraScript : public AuraScript
    {
        bool Load()
        {
            return true;
        }

        void EffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*modes*/)
        {
            if (!GetUnitOwner() || GetUnitOwner()->GetTypeId() != TYPEID_PLAYER)
                return;
        }

        void EffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*modes*/)
        {
            if (!GetUnitOwner() || GetUnitOwner()->GetTypeId() != TYPEID_PLAYER)
                return;

            Unit* owner = GetUnitOwner();
            if (Creature* vb = owner->ToPlayer()->GetVehicleCreatureBase())
            {
                vb->Kill(owner, vb);
                vb->DespawnOrUnsummon();
            }


            owner->NearTeleportTo(playerKickPosition.GetPositionX(), playerKickPosition.GetPositionY(), playerKickPosition.GetPositionZ(), playerKickPosition.GetOrientation(), false);
            owner->SetImmuneToAll(false);
            owner->CastSpell(owner, 109976, true);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_tonk_enable_AuraScript::EffectApply, EFFECT_0, SPELL_AURA_ENABLE_POWER_BAR_TIMER, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectApplyFn(spell_tonk_enable_AuraScript::EffectRemove, EFFECT_0, SPELL_AURA_ENABLE_POWER_BAR_TIMER, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_tonk_enable_AuraScript();
    }
};

class npc_darkmoon_tonk_target : public CreatureScript
{
public:
    npc_darkmoon_tonk_target() : CreatureScript("npc_darkmoon_tonk_target") { }

    struct npc_darkmoon_tonk_targetAI : public ScriptedAI
    {
        npc_darkmoon_tonk_targetAI(Creature* c) : ScriptedAI(c)
        {
            Reset();
        }

        void SpellHit(WorldObject* caster, SpellInfo const* spellInfo) override
        {
            Unit* unitCaster = caster->ToUnit();
            if (!unitCaster)
                return;

            if (spellInfo->Id == SPELL_TONK_SHOOT)
            {
                Vehicle* veh = unitCaster->GetVehicleKit();
                if (veh)
                {
                    for (uint32 i = 0; i < MAX_VEHICLE_SEATS; i++)
                    {
                        if (Unit* passenger = veh->GetPassenger(i))
                            passenger->CastSpell(passenger, SPELL_TONK_KILL_CREDIT, true);
                    }
                }
                me->CastSpell(me, 100626, true);
                me->DespawnOrUnsummon(600ms);
            }
        }
    };

    CreatureAI* GetAI(Creature* c) const
    {
        return new npc_darkmoon_tonk_targetAI(c);
    }
};

class vehicle_darkmoon_steam_tonk : public VehicleScript
{
public:
    vehicle_darkmoon_steam_tonk() : VehicleScript("vehicle_darkmoon_steam_tonk") { }

    void OnRemovePassenger(Vehicle* veh, Unit* passenger)
    {
        if (passenger)
        {
            passenger->RemoveAurasDueToSpell(SPELL_TONK_ENABLE);
        }

        if (Unit* base = veh->GetBase())
            if (base->ToCreature())
                base->ToCreature()->DespawnOrUnsummon(0s);
    }
};

class npc_darkmoon_enemy_tonk : public CreatureScript
{
public:
    npc_darkmoon_enemy_tonk() : CreatureScript("npc_darkmoon_enemy_tonk") { }

    struct npc_darkmoon_enemy_tonkAI : public ScriptedAI
    {
        npc_darkmoon_enemy_tonkAI(Creature* c) : ScriptedAI(c)
        {
            Reset();
        }

        ObjectGuid target;
        bool changePath;
        uint32 pathCheckTimer;
        uint32 targetCheckTimer;

        void Reset()
        {
            target.Clear();
            changePath = true;
            pathCheckTimer = 0;
            targetCheckTimer = 1000;
        }

        void MovementInform(uint32 /*type*/, uint32 id)
        {
            if (id == 0)
                changePath = true;
        }

        void UpdateAI(const uint32 diff)
        {
            if (pathCheckTimer != 0)
            {
                if (pathCheckTimer <= diff)
                {
                    target.Clear();
                    changePath = true;
                    pathCheckTimer = 0;
                }
                else
                    pathCheckTimer -= diff;
            }

            if (changePath)
            {
                if (me && me->IsAlive() && me->IsInWorld())
                {
                    uint8 point = urand(0, TONK_TARGET_POSITION_COUNT - 1);
                    me->GetMotionMaster()->MovePoint(0, tonkTargetPositions[point]);
                    changePath = false;
                }
            }

            if (targetCheckTimer <= diff)
            {
                if (!target.IsEmpty())
                {
                    std::list<Creature*> crList;
                    GetCreatureListWithEntryInGrid(crList, me, NPC_PLAYER_TONK, 4.5f);
                    for (std::list<Creature*>::iterator itr = crList.begin(); itr != crList.end(); ++itr)
                    {
                        if ((*itr)->isInFront(me, 7.0f) && !(*itr)->HasAura(SPELL_ENEMY_TONK_MARKED))
                        {
                            target = (*itr)->GetGUID();
                            me->StopMoving();
                            changePath = false;
                            me->SetFacingToObject(*itr);
                            me->AddAura(SPELL_ENEMY_TONK_MARKED, (*itr));
                            me->CastSpell((*itr), SPELL_ENEMY_TONK_CANNON_BLAST, false);
                            pathCheckTimer = 3000; // 2s spellcast + 1s delay
                            break;
                        }
                    }

                    if (!target.IsEmpty())
                        targetCheckTimer = 1000;
                    else
                        targetCheckTimer = 2500;
                }
                else
                {
                    Unit* targetUnit = ObjectAccessor::GetUnit(*me, target);
                    if (targetUnit && targetUnit->IsWithinDist(me, 7.0f, true) && targetUnit->isInFront(me, 7.0f))
                    {
                        targetUnit->CastSpell(targetUnit, 100626, true);
                        me->DealDamage(me, targetUnit, (targetUnit->GetMaxHealth() / 2) + 1);
                    }
                    targetCheckTimer = 2000;
                }
            }
            else
                targetCheckTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* c) const
    {
        return new npc_darkmoon_enemy_tonkAI(c);
    }
};

class spell_tonk_cannon : public SpellScript
{
    static constexpr uint32 ALLOWED_ENTRIES[] = { 54642, 33081 };
    static constexpr float MAX_DISTANCE = 7.0f;

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        Player* player = caster->GetCharmerOrOwnerPlayerOrPlayerItself();

        if (Vehicle* vehicle = caster->GetVehicleKit())
            if (Unit* passenger = vehicle->GetPassenger(0))
                if (passenger->GetTypeId() == TYPEID_PLAYER)
                    player = passenger->ToPlayer();

        if (!player)
            return;

        targets.remove_if([player](WorldObject* target)
        {
            if (target->GetTypeId() != TYPEID_UNIT)
                return true;

            Creature* creature = target->ToCreature();
            if (!creature)
                return true;

            bool entryValid = false;
            for (auto entry : ALLOWED_ENTRIES)
                if (creature->GetEntry() == entry)
                    entryValid = true;

            if (!entryValid)
                return true;

            return !player->IsWithinDistInMap(target, MAX_DISTANCE) ||
                !player->HasInLine(target, 2.0f, player->GetObjectScale());
        });
    }

    void HandleDamage(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            if (target->GetEntry() == 54588 ||
                target->GetTypeId() == TYPEID_PLAYER)
            {
                PreventHitDamage();
                TC_LOG_ERROR("spells", "TonkCannon: Blocked damage to invalid target %s",
                    target->GetName().c_str());
            }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_tonk_cannon::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
        OnEffectHitTarget += SpellEffectFn(spell_tonk_cannon::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// areatrigger - 7340
class at_tonks_zone : public AreaTriggerScript
{
public:
    at_tonks_zone() : AreaTriggerScript("at_tonks_zone") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        if (!player->IsGameMaster() && !player->HasAura(102178))
            player->CastSpell(player, 109976, true);
        return true;
    }
};

void AddSC_darkmoon_tonk()
{
    new npc_finlay_darkmoon();
    new spell_tonk_enable();
    new npc_darkmoon_tonk_target();
    new vehicle_darkmoon_steam_tonk();
    new npc_darkmoon_enemy_tonk();
    new spell_tonk_cannon();
    //areatrigger
    new at_tonks_zone();
};
