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

/// \file       VBOIndexer.hpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Optimization
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_VBO_INDEXER_HPP__
#define CARDINAL_ENGINE_VBO_INDEXER_HPP__

#include <map>
#include <vector>
#include <cstring>

#include "Glm/glm/glm.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class Indexer
/// \brief Optimizes rendering by indexing vertices who
///        share same properties (uvs, colors, normals)
class VBOIndexer
{
public :

    // TODO : Update docs
    /// \brief Indexes vertices who shares same properties
    /// \param inVertices  The input vertices vector
    /// \param inUVs       The input uvs vector
    /// \param outIndexes  The output indexes vector
    /// \param outVertices The output vertices vector
    /// \param outUVs      The output uvs vector
    static void Index(
            std::vector<glm::vec3> const& inVertices,
            std::vector<glm::vec2> const& inUVs,
            std::vector<unsigned short> & outIndexes,
            std::vector<glm::vec3>      & outVertices,
            std::vector<glm::vec2>      & outUVs);

    // TODO : Update docs
    /// \brief Indexes vertices who shares same properties
    /// \param inVertices  The input vertices vector
    /// \param inUVs       The input uvs vector
    /// \param outIndexes  The output indexes vector
    /// \param outVertices The output vertices vector
    /// \param outUVs      The output uvs vector
    static void Index(
            std::vector<glm::vec3> const& inVertices,
            std::vector<glm::vec3> const& inNormals,
            std::vector<glm::vec2> const& inUVs,
            std::vector<unsigned short> & outIndexes,
            std::vector<glm::vec3>      & outVertices,
            std::vector<glm::vec3>      & outNormals,
            std::vector<glm::vec2>      & outUVs);

private:

    /// \struct sPackedVertex
    struct sPackedVertex
    {
        glm::vec3 position; ///< Stores the position of a vertex
        glm::vec2 uv;        ///< Stores the color of a vertex

        /// \brief Compare helper method
        bool operator<(const sPackedVertex other) const
        {
            return memcmp((void*)this, (void*)&other, sizeof(sPackedVertex)) > 0;
        };
    };

    /// \struct sPackedVertexBeta
    struct sPackedVertexBeta
    {
        glm::vec3 position;
        glm::vec3 normals;
        glm::vec2 uv;

        /// \brief Compare helper method
        bool operator<(const sPackedVertexBeta other) const
        {
            return memcmp((void*)this, (void*)&other, sizeof(sPackedVertexBeta)) > 0;
        };
    };

    /// \brief  Tells if there already is a similar vertex
    /// \param  pack The current pack to check
    /// \param  output The output map
    /// \param  result The result
    /// \return True or false
    inline static bool GetSimilarVertexIndex(sPackedVertex const& pack,
            std::map<sPackedVertex,unsigned short> const& output,
            unsigned short & result);

    /// \brief  Tells if there already is a similar vertex
    /// \param  pack The current pack to check
    /// \param  output The output map
    /// \param  result The result
    /// \return True or false
    inline static bool GetSimilarVertexIndex(sPackedVertexBeta const& pack,
            std::map<sPackedVertexBeta,unsigned short> const& output,
            unsigned short & result);
};

} // !namespace

#include "Impl/VBOIndexer.inl"

#endif // !CARDINAL_ENGINE_VBO_INDEXER_HPP__