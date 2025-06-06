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

#ifndef TRINITYCORE_CHAT_PACKETS_H
#define TRINITYCORE_CHAT_PACKETS_H

#include "Packet.h"
#include "Common.h"
#include "ObjectGuid.h"
#include "Optional.h"
#include "PacketUtilities.h"
#include "SharedDefines.h"

class WorldObject;
enum class ChatWhisperTargetStatus : uint8;

namespace WorldPackets
{
    namespace Chat
    {
        // CMSG_CHAT_MESSAGE_GUILD
        // CMSG_CHAT_MESSAGE_OFFICER
        // CMSG_CHAT_MESSAGE_YELL
        // CMSG_CHAT_MESSAGE_SAY
        // CMSG_CHAT_MESSAGE_PARTY
        // CMSG_CHAT_MESSAGE_RAID
        // CMSG_CHAT_MESSAGE_RAID_WARNING
        // CMSG_CHAT_MESSAGE_INSTANCE_CHAT
        class ChatMessage final : public ClientPacket
        {
        public:
            explicit ChatMessage(WorldPacket&& packet) : ClientPacket(std::move(packet)) { }

            void Read() override;

            std::string Text;
            int32 Language = LANG_UNIVERSAL;
            bool IsSecure = true;
        };

        // CMSG_CHAT_MESSAGE_WHISPER
        class ChatMessageWhisper final : public ClientPacket
        {
        public:
            explicit ChatMessageWhisper(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_MESSAGE_WHISPER, std::move(packet)) { }

            void Read() override;

            int32 Language = LANG_UNIVERSAL;
            ObjectGuid TargetGUID;
            uint32 TargetVirtualRealmAddress = 0;
            std::string Target;
            std::string Text;
        };

        // CMSG_CHAT_MESSAGE_CHANNEL
        class ChatMessageChannel final : public ClientPacket
        {
        public:
            explicit ChatMessageChannel(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_MESSAGE_CHANNEL, std::move(packet)) { }

            void Read() override;

            int32 Language = LANG_UNIVERSAL;
            ObjectGuid ChannelGUID;
            std::string Text;
            std::string Target;
            Optional<bool> IsSecure;
        };

        struct ChatAddonMessageParams
        {
            std::string Prefix;
            std::string Text;
            ChatMsg Type = CHAT_MSG_PARTY;
            bool IsLogged = false;
        };

        // CMSG_CHAT_ADDON_MESSAGE
        class ChatAddonMessage final : public ClientPacket
        {
        public:
            explicit ChatAddonMessage(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_ADDON_MESSAGE, std::move(packet)) { }

            void Read() override;

            ChatAddonMessageParams Params;
        };

        // CMSG_COMMENTATOR_ENABLE
        class CommentatorModeEnable final : public ClientPacket
        {
        public:
            CommentatorModeEnable(WorldPacket&& packet) : ClientPacket(CMSG_COMMENTATOR_ENABLE, std::move(packet)) { }

            void Read() override;

            uint32 Action = 0;
        };

        // CMSG_CHAT_ADDON_MESSAGE_CHANNEL
        class ChatAddonMessageTargeted final : public ClientPacket
        {
        public:
            explicit ChatAddonMessageTargeted(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_ADDON_MESSAGE_TARGETED, std::move(packet)) { }

            void Read() override;

            ChatAddonMessageParams Params;
            std::string PlayerName;
            ObjectGuid PlayerGUID;
            uint32 PlayerVirtualRealmAddress = 0;
            std::string ChannelName;
            ObjectGuid ChannelGUID;
        };

        class ChatMessageDND final : public ClientPacket
        {
        public:
            explicit ChatMessageDND(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_MESSAGE_DND, std::move(packet)) { }

            void Read() override;

            std::string Text;
        };

        class ChatMessageAFK final : public ClientPacket
        {
        public:
            explicit ChatMessageAFK(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_MESSAGE_AFK, std::move(packet)) { }

            void Read() override;

            std::string Text;
        };

        class ChatMessageEmote final : public ClientPacket
        {
        public:
            explicit ChatMessageEmote(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_MESSAGE_EMOTE, std::move(packet)) { }

            void Read() override;

            std::string Text;
        };

        // SMSG_CHAT
        class TC_GAME_API Chat final : public ServerPacket
        {
        public:
            explicit Chat() : ServerPacket(SMSG_CHAT, 100) { }
            Chat(Chat const& chat);

            void Initialize(ChatMsg chatType, Language language, WorldObject const* sender, WorldObject const* receiver, std::string_view message, uint32 achievementId = 0,
                std::string_view channelName = "", LocaleConstant locale = DEFAULT_LOCALE, std::string_view addonPrefix = "");
            void SetSender(WorldObject const* sender, LocaleConstant locale);
            void SetReceiver(WorldObject const* receiver, LocaleConstant locale);

            WorldPacket const* Write() override;

            uint8 SlashCmd = 0;     ///< @see enum ChatMsg
            uint32 _Language = LANG_UNIVERSAL;
            ObjectGuid SenderGUID;
            ObjectGuid SenderGuildGUID;
            ObjectGuid SenderWowAccount;
            ObjectGuid TargetGUID;
            uint32 SenderVirtualAddress = 0;
            uint32 TargetVirtualAddress = 0;
            std::string SenderName;
            std::string TargetName;
            std::string Prefix;     ///< Addon Prefix
            std::string _Channel;   ///< Channel Name
            std::string ChatText;
            uint32 AchievementID = 0;
            uint16 _ChatFlags = 0;   ///< @see enum ChatFlags
            float DisplayTime = 0.0f;
            int32 SpellID = 0;
            Optional<uint32> BroadcastTextID;
            bool HideChatLog = false;
            bool FakeSenderName = false;
            Optional<ObjectGuid> ChannelGUID;
        };

        class Emote final : public ServerPacket
        {
        public:
            explicit Emote() : ServerPacket(SMSG_EMOTE, 18 + 4) { }

            WorldPacket const* Write() override;

            ObjectGuid Guid;
            uint32 EmoteID = 0;
            std::vector<int32> SpellVisualKitIDs;
            int32 SequenceVariation = 0;
        };

        class CTextEmote final : public ClientPacket
        {
        public:
            explicit CTextEmote(WorldPacket&& packet) : ClientPacket(CMSG_SEND_TEXT_EMOTE, std::move(packet)) { }

            void Read() override;

            ObjectGuid Target;
            int32 EmoteID = 0;
            int32 SoundIndex = -1;
            Array<int32, 2> SpellVisualKitIDs;
            int32 SequenceVariation = 0;
        };

        class STextEmote final : public ServerPacket
        {
        public:
            explicit STextEmote() : ServerPacket(SMSG_TEXT_EMOTE, 3 * 18 + 2 * 4) { }

            WorldPacket const* Write() override;

            ObjectGuid SourceGUID;
            ObjectGuid SourceAccountGUID;
            ObjectGuid TargetGUID;
            int32 SoundIndex = -1;
            int32 EmoteID = 0;
        };

        class ClearBossEmotes final : public ServerPacket
        {
        public:
            explicit ClearBossEmotes() : ServerPacket(SMSG_CLEAR_BOSS_EMOTES, 0) { }

            WorldPacket const* Write() override { return &_worldPacket; }
        };

        class TC_GAME_API PrintNotification final : public ServerPacket
        {
        public:
            explicit PrintNotification(std::string const& notifyText) : ServerPacket(SMSG_PRINT_NOTIFICATION, 2 + notifyText.size()), NotifyText(notifyText) { }

            WorldPacket const* Write() override;

            std::string NotifyText;
        };

        class EmoteClient final : public ClientPacket
        {
        public:
            explicit EmoteClient(WorldPacket&& packet) : ClientPacket(CMSG_EMOTE, std::move(packet)) { }

            void Read() override { }
        };

        class ChatPlayerNotfound final : public ServerPacket
        {
        public:
            explicit ChatPlayerNotfound(std::string const& name) : ServerPacket(SMSG_CHAT_PLAYER_NOTFOUND, 2 + name.size()), Name(name) { }

            WorldPacket const* Write() override;

            std::string Name;
        };

        class ChatServerMessage final : public ServerPacket
        {
        public:
            explicit ChatServerMessage() : ServerPacket(SMSG_CHAT_SERVER_MESSAGE, 4 + 2) { }

            WorldPacket const* Write() override;

            int32 MessageID = 0;
            std::string_view StringParam;
        };

        class ChatRegisterAddonPrefixes final : public ClientPacket
        {
        public:
            enum
            {
                MAX_PREFIXES = 64
            };

            explicit ChatRegisterAddonPrefixes(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_REGISTER_ADDON_PREFIXES, std::move(packet)) { }

            void Read() override;

            Array<std::string, MAX_PREFIXES> Prefixes;
        };

        class ChatUnregisterAllAddonPrefixes final : public ClientPacket
        {
        public:
            explicit ChatUnregisterAllAddonPrefixes(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_UNREGISTER_ALL_ADDON_PREFIXES, std::move(packet)) { }

            void Read() override { }
        };

        class DefenseMessage final : public ServerPacket
        {
        public:
            explicit DefenseMessage() : ServerPacket(SMSG_DEFENSE_MESSAGE) { }

            WorldPacket const* Write() override;

            int32 ZoneID = 0;
            std::string MessageText;
        };

        class ChatReportIgnored final : public ClientPacket
        {
        public:
            explicit ChatReportIgnored(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_REPORT_IGNORED, std::move(packet)) { }

            void Read() override;

            ObjectGuid IgnoredGUID;
            uint8 Reason = 0;
        };

        class ChatPlayerAmbiguous final : public ServerPacket
        {
        public:
            explicit ChatPlayerAmbiguous(std::string const& name) : ServerPacket(SMSG_CHAT_PLAYER_AMBIGUOUS, 2 + name.length()), Name(name) { }

            WorldPacket const* Write() override;

            std::string Name;
        };

        class ChatRestricted final : public ServerPacket
        {
        public:
            explicit ChatRestricted() : ServerPacket(SMSG_CHAT_RESTRICTED, 4) { }

            WorldPacket const* Write() override;

            int32 Reason = 0;
        };

        class CanLocalWhisperTargetRequest final : public ClientPacket
        {
        public:
            explicit CanLocalWhisperTargetRequest(WorldPacket&& packet) : ClientPacket(CMSG_CHAT_CAN_LOCAL_WHISPER_TARGET_REQUEST, std::move(packet)) { }

            void Read() override;

            ObjectGuid WhisperTarget;
        };

        class CanLocalWhisperTargetResponse final : public ServerPacket
        {
        public:
            explicit CanLocalWhisperTargetResponse() : ServerPacket(SMSG_CHAT_CAN_LOCAL_WHISPER_TARGET_RESPONSE, 16 + 1) { }

            WorldPacket const* Write() override;

            ObjectGuid WhisperTarget;
            ChatWhisperTargetStatus Status = {};
        };

        class UpdateAADCStatus final : public ClientPacket
        {
        public:
            explicit UpdateAADCStatus(WorldPacket&& packet) : ClientPacket(CMSG_UPDATE_AADC_STATUS, std::move(packet)) { }

            void Read() override;

            bool ChatDisabled = false;
        };

        class UpdateAADCStatusResponse final : public ServerPacket
        {
        public:
            explicit UpdateAADCStatusResponse() : ServerPacket(SMSG_UPDATE_AADC_STATUS_RESPONSE, 1) { }

            WorldPacket const* Write() override;

            bool Success = false;
            bool ChatDisabled = false;
        };
    }
}

#endif // TRINITYCORE_CHAT_PACKETS_H
