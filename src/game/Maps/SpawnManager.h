/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOS_SPAWN_MANAGER_H
#define MANGOS_SPAWN_MANAGER_H

#include "Common.h"
#include "Entities/ObjectGuid.h"

#include <string>

class Map;

class SpawnInfo
{
    public:
        SpawnInfo(TimePoint when, uint32 dbguid, HighGuid high) : m_respawnTime(when), m_dbguid(dbguid), m_high(high) {}
        TimePoint const& GetRespawnTime() const { return m_respawnTime; }
        bool ConstructForMap(Map& map); // can fail due to linking, pooling not yet supported
        uint32 GetDbGuid() const { return m_dbguid; }
        HighGuid GetHighGuid() const { return m_high; }
    private:
        TimePoint m_respawnTime;
        uint32 m_dbguid;
        HighGuid m_high;
};

bool operator<(SpawnInfo const& lhs, SpawnInfo const& rhs);

class SpawnManager
{
    public:
        SpawnManager(Map& map) : m_map(map) {}
        void AddCreature(uint32 respawnDelay, uint32 dbguid);
        void AddGameObject(uint32 respawnDelay, uint32 dbguid);

        void RespawnCreature(uint32 dbguid);
        void RespawnGameObject(uint32 dbguid);

        void RespawnAll();

        void Update();

        std::string GetRespawnList();
    private:
        Map& m_map;

        std::vector<SpawnInfo> m_spawns;
};

#endif