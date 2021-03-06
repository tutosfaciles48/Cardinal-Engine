/// Copyright (C) 2018-2019, Cardinal Engine
/// Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

/// \file       ProceduralBuilding.hpp
/// \date       07/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_PROCEDURAL_BUILDING_HPP
#define CARDINAL_ENGINE_PROCEDURAL_BUILDING_HPP

#include "World/Cube/ByteCube.hpp"
#include "World/Cube/UVManager.hpp"
#include "ProceduralBuildingRenderer.hpp"

#define BUILDING_MAX_SIZE   32
#define BUILDING_MAX_HEIGHT 32

/// \class ProceduralBuilding
/// \brief Procedural building system using sockets
class ProceduralBuilding
{
public:

    /// \brief Constructor
    ProceduralBuilding();

    /// \brief Initializes the building before generation
    void Initialize();

    /// \brief Generates the building
    void Generate();

    /// \brief Batch geometry
    void Batch();

    /// \brief Updates the geometry of the building
    /// \param dt The elapsed time
    void Update(float dt);

private:

    ProceduralBuildingRenderer m_renderer;
    ByteCube m_building[BUILDING_MAX_SIZE][BUILDING_MAX_SIZE][BUILDING_MAX_HEIGHT];

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_uvs;

    float m_offset;
    float m_elapsed;
};

#endif // !CARDINAL_ENGINE_PROCEDURAL_BUILDING_HPP