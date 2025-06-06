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

#include "InspectPackets.h"
#include "AzeriteItem.h"
#include "Item.h"
#include "PacketOperators.h"
#include "Player.h"

namespace WorldPackets::Inspect
{
void Inspect::Read()
{
    _worldPacket >> Target;
}

ByteBuffer& operator<<(ByteBuffer& data, InspectEnchantData const& enchantData)
{
    data << uint32(enchantData.Id);
    data << uint8(enchantData.Index);

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, AzeriteEssenceData const& azeriteEssenceData)
{
    data << uint32(azeriteEssenceData.Index);
    data << uint32(azeriteEssenceData.AzeriteEssenceID);
    data << uint32(azeriteEssenceData.Rank);
    data << Bits<1>(azeriteEssenceData.SlotUnlocked);
    data.FlushBits();

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, InspectItemData const& itemData)
{
    data << itemData.CreatorGUID;
    data << uint8(itemData.Index);
    data << Size<uint32>(itemData.AzeritePowers);
    data << Size<uint32>(itemData.AzeriteEssences);

    if (!itemData.AzeritePowers.empty())
        data.append(itemData.AzeritePowers.data(), itemData.AzeritePowers.size());

    data << itemData.Item;
    data << Bits<1>(itemData.Usable);
    data << BitsSize<4>(itemData.Enchants);
    data << BitsSize<2>(itemData.Gems);
    data.FlushBits();

    for (AzeriteEssenceData const& azeriteEssenceData : itemData.AzeriteEssences)
        data << azeriteEssenceData;

    for (InspectEnchantData const& enchantData : itemData.Enchants)
        data << enchantData;

    for (Item::ItemGemData const& gem : itemData.Gems)
        data << gem;

    return data;
}

void PlayerModelDisplayInfo::Initialize(Player const* player)
{
    GUID = player->GetGUID();
    SpecializationID = AsUnderlyingType(player->GetPrimarySpecialization());
    Name = player->GetName();
    GenderID = player->GetNativeGender();
    Race = player->GetRace();
    ClassID = player->GetClass();

    for (UF::ChrCustomizationChoice const& customization : player->m_playerData->Customizations)
        Customizations.push_back(customization);

    for (uint8 i = 0; i < EQUIPMENT_SLOT_END; ++i)
        if (::Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            Items.emplace_back(item, i);
}

ByteBuffer& operator<<(ByteBuffer& data, PlayerModelDisplayInfo const& displayInfo)
{
    data << displayInfo.GUID;
    data << int32(displayInfo.SpecializationID);
    data << Size<uint32>(displayInfo.Items);
    data << SizedString::BitsSize<6>(displayInfo.Name);
    data << uint8(displayInfo.GenderID);
    data << uint8(displayInfo.Race);
    data << uint8(displayInfo.ClassID);
    data << Size<uint32>(displayInfo.Customizations);
    data << SizedString::Data(displayInfo.Name);

    for (Character::ChrCustomizationChoice const& customization : displayInfo.Customizations)
        data << customization;

    for (InspectItemData const& item : displayInfo.Items)
        data << item;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, InspectGuildData const& guildData)
{
    data << guildData.GuildGUID;
    data << int32(guildData.NumGuildMembers);
    data << int32(guildData.AchievementPoints);

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, PVPBracketData const& bracket)
{
    data << uint8(bracket.Bracket);
    data << int32(bracket.RatingID);
    data << int32(bracket.Rating);
    data << int32(bracket.Rank);
    data << int32(bracket.WeeklyPlayed);
    data << int32(bracket.WeeklyWon);
    data << int32(bracket.SeasonPlayed);
    data << int32(bracket.SeasonWon);
    data << int32(bracket.WeeklyBestRating);
    data << int32(bracket.LastWeeksBestRating);
    data << int32(bracket.Tier);
    data << int32(bracket.WeeklyBestTier);
    data << int32(bracket.SeasonBestRating);
    data << uint8(bracket.SeasonBestTierEnum);
    data << int32(bracket.RoundsSeasonPlayed);
    data << int32(bracket.RoundsSeasonWon);
    data << int32(bracket.RoundsWeeklyPlayed);
    data << int32(bracket.RoundsWeeklyWon);
    data << Bits<1>(bracket.Disqualified);
    data.FlushBits();

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, TraitInspectInfo const& traits)
{
    data << int32(traits.Level);
    data << int32(traits.ChrSpecializationID);
    data << traits.Config;

    return data;
}

InspectItemData::InspectItemData(::Item const* item, uint8 index)
{
    CreatorGUID = item->GetCreator();

    Item.Initialize(item);
    Index = index;
    Usable = true; /// @todo

    for (uint8 i = 0; i < MAX_ENCHANTMENT_SLOT; ++i)
        if (uint32 enchId = item->GetEnchantmentId(EnchantmentSlot(i)))
            Enchants.emplace_back(enchId, i);

    uint8 i = 0;
    for (UF::SocketedGem const& gemData : item->m_itemData->Gems)
    {
        if (gemData.ItemID)
        {
            Gems.emplace_back();

            Item::ItemGemData& gem = Gems.back();
            gem.Slot = i;
            gem.Item.Initialize(&gemData);
        }
        ++i;
    }

    if (AzeriteItem const* azeriteItem = item->ToAzeriteItem())
    {
        if (UF::SelectedAzeriteEssences const* essences = azeriteItem->GetSelectedAzeriteEssences())
        {
            for (uint8 slot = 0; slot < essences->AzeriteEssenceID.size(); ++slot)
            {
                AzeriteEssences.emplace_back();

                AzeriteEssenceData& essence = AzeriteEssences.back();
                essence.Index = slot;
                essence.AzeriteEssenceID = essences->AzeriteEssenceID[slot];
                if (essence.AzeriteEssenceID)
                {
                    essence.Rank = azeriteItem->GetEssenceRank(essence.AzeriteEssenceID);
                    essence.SlotUnlocked = true;
                }
                else
                    essence.SlotUnlocked = azeriteItem->HasUnlockedEssenceSlot(slot);
            }
        }
    }
}

WorldPacket const* InspectResult::Write()
{
    _worldPacket << DisplayInfo;
    _worldPacket << Size<uint32>(Glyphs);
    _worldPacket << Size<uint32>(Talents);
    _worldPacket << Size<uint32>(PvpTalents);
    _worldPacket << int32(ItemLevel);
    _worldPacket << uint8(LifetimeMaxRank);
    _worldPacket << uint16(TodayHK);
    _worldPacket << uint16(YesterdayHK);
    _worldPacket << uint32(LifetimeHK);
    _worldPacket << uint32(HonorLevel);
    if (!Glyphs.empty())
        _worldPacket.append(Glyphs.data(), Glyphs.size());
    if (!Talents.empty())
        _worldPacket.append(Talents.data(), Talents.size());
    if (!PvpTalents.empty())
        _worldPacket.append(PvpTalents.data(), PvpTalents.size());

    _worldPacket << OptionalInit(GuildData);
    _worldPacket << OptionalInit(AzeriteLevel);
    _worldPacket.FlushBits();

    for (PVPBracketData const& bracket : Bracket)
        _worldPacket << bracket;

    if (GuildData)
        _worldPacket << *GuildData;

    if (AzeriteLevel)
        _worldPacket << int32(*AzeriteLevel);

    _worldPacket << TalentTraits;

    return &_worldPacket;
}

void QueryInspectAchievements::Read()
{
    _worldPacket >> Guid;
}
}
