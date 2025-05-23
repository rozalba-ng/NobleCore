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

#ifndef TRINITYCORE_COMMON_H
#define TRINITYCORE_COMMON_H

#include "Define.h"
#include <array>
#include <string>
#include <cstdlib>
#include <boost/any.hpp>
#include <mutex>
#include <unordered_map>
#include <map>
#include <regex>
#include <list>
#include "Errors.h"
#include "LockedQueue.h"
#include "StringFormat.h"

using namespace std::string_literals;
using namespace std::string_view_literals;

#define STRINGIZE(a) #a

enum TimeConstants
{
    MINUTE          = 60,
    HOUR            = MINUTE*60,
    DAY             = HOUR*24,
    WEEK            = DAY*7,
    MONTH           = DAY*30,
    YEAR            = MONTH*12,
    IN_MILLISECONDS = 1000
};

enum AccountTypes
{
    SEC_PLAYER         = 0,
    SEC_MODERATOR      = 1,
    SEC_GAMEMASTER     = 2,
    SEC_ADMINISTRATOR  = 3,
    SEC_CONSOLE        = 4                                  // must be always last in list, accounts must have less security level always also
};

enum LocaleConstant : uint8
{
    LOCALE_enUS = 0,
    LOCALE_koKR = 1,
    LOCALE_frFR = 2,
    LOCALE_deDE = 3,
    LOCALE_zhCN = 4,
    LOCALE_zhTW = 5,
    LOCALE_esES = 6,
    LOCALE_esMX = 7,
    LOCALE_ruRU = 8,
    LOCALE_none = 9,
    LOCALE_ptBR = 10,
    LOCALE_itIT = 11,

    TOTAL_LOCALES
};

const uint8 OLD_TOTAL_LOCALES = 9; /// @todo convert in simple system
#define DEFAULT_LOCALE LOCALE_enUS

enum class CascLocaleBit : uint8
{
    None        = 0,
    enUS        = 1,
    koKR        = 2,
    Reserved    = 3,
    frFR        = 4,
    deDE        = 5,
    zhCN        = 6,
    esES        = 7,
    zhTW        = 8,
    enGB        = 9,
    enCN        = 10,
    enTW        = 11,
    esMX        = 12,
    ruRU        = 13,
    ptBR        = 14,
    itIT        = 15,
    ptPT        = 16
};

TC_COMMON_API extern char const* localeNames[TOTAL_LOCALES];

TC_COMMON_API LocaleConstant GetLocaleByName(std::string_view name);

TC_COMMON_API extern CascLocaleBit WowLocaleToCascLocaleBit[TOTAL_LOCALES];

constexpr inline bool IsValidLocale(LocaleConstant locale)
{
    return locale < TOTAL_LOCALES && locale != LOCALE_none;
}

#pragma pack(push, 1)

struct LocalizedString
{
    constexpr char const* operator[](LocaleConstant locale) const
    {
        return Str[locale];
    }

    std::array<char const*, TOTAL_LOCALES> Str;
};

#pragma pack(pop)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_4
#define M_PI_4 0.785398163397448309616
#endif

#define MAX_QUERY_LEN 32*1024

namespace ThisCore
{
    class TC_GAME_API AnyData
    {
    public:
        template<typename T>
        void Set(std::string const& key, T value)
        {
            dataMap[key] = value;
        }

        template<typename T>
        T GetValue(std::string const& key, T defaultValue = T()) const
        {
            auto itr = dataMap.find(key);
            if (itr != dataMap.end())
                return boost::any_cast<T>(itr->second);
            return defaultValue;
        }

        bool Exist(std::string const& key) const
        {
            return dataMap.find(key) != dataMap.end();
        }

        void Remove(std::string const& key)
        {
            dataMap.erase(key);
        }

        uint32 Increment(std::string const& key, uint32 increment = 1)
        {
            uint32 currentValue = GetValue<uint32>(key, uint32(0));
            Set(key, currentValue += increment);
            return currentValue;
        }

        bool IncrementOrProcCounter(std::string const& key, uint32 maxVal, uint32 increment = 1)
        {
            uint32 newValue = Increment(key, increment);
            if (newValue < maxVal)
                return false;

            Remove(key);
            return true;
        }

    private:
        std::unordered_map<std::string, boost::any> dataMap;
    };
}

#endif
