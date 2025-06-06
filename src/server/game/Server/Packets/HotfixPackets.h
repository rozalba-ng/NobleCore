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

#ifndef TRINITYCORE_HOTFIX_PACKETS_H
#define TRINITYCORE_HOTFIX_PACKETS_H

#include "Common.h"
#include "DB2Stores.h"
#include "Packet.h"

namespace WorldPackets
{
    namespace Hotfix
    {
        class DBQueryBulk final : public ClientPacket
        {
        public:
            struct DBQueryRecord
            {
                uint32 RecordID = 0;
            };

            explicit DBQueryBulk(WorldPacket&& packet) : ClientPacket(CMSG_DB_QUERY_BULK, std::move(packet)) { }

            void Read() override;

            uint32 TableHash = 0;
            std::vector<DBQueryRecord> Queries;
        };

        class DBReply final : public ServerPacket
        {
        public:
            explicit DBReply() : ServerPacket(SMSG_DB_REPLY, 4 + 4 + 4 + 1 + 4) { }

            WorldPacket const* Write() override;

            uint32 TableHash = 0;
            uint32 Timestamp = 0;
            uint32 RecordID = 0;
            DB2Manager::HotfixRecord::Status Status = DB2Manager::HotfixRecord::Status::Invalid;
            ByteBuffer Data;
        };

        class TC_GAME_API AvailableHotfixes final : public ServerPacket
        {
        public:
            explicit AvailableHotfixes() : ServerPacket(SMSG_AVAILABLE_HOTFIXES, 0) { }

            WorldPacket const* Write() override;

            int32 VirtualRealmAddress = 0;
            std::set<DB2Manager::HotfixId> Hotfixes;
        };

        class HotfixRequest final : public ClientPacket
        {
        public:
            explicit HotfixRequest(WorldPacket&& packet) : ClientPacket(CMSG_HOTFIX_REQUEST, std::move(packet)) { }

            void Read() override;

            uint32 ClientBuild = 0;
            uint32 DataBuild = 0;
            std::vector<int32> Hotfixes;
        };

        class HotfixConnect final : public ServerPacket
        {
        public:
            struct HotfixData
            {
                DB2Manager::HotfixRecord Record;
                uint32 Size = 0;
            };

            explicit HotfixConnect() : ServerPacket(SMSG_HOTFIX_CONNECT) { }

            WorldPacket const* Write() override;

            std::vector<HotfixData> Hotfixes;
            ByteBuffer HotfixContent;
        };
    }
}

#endif // TRINITYCORE_HOTFIX_PACKETS_H
