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

/// \file       MeshRenderer.cpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"

#include "Runtime/Rendering/Renderer/MeshRenderer.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Default constructor
MeshRenderer::MeshRenderer()
{
    m_vao            = 0;
    m_indexesObject  = 0;
    m_verticesObject = 0;
    m_uvsObject      = 0;
    m_elementsCount  = 0;
    m_pShader        = nullptr;
}

/// \brief Destructor
MeshRenderer::~MeshRenderer() // NOLINT
{
    // TODO
}

/// \brief Initializes the mesh
/// \param indexes The indexes of the mesh
/// \param vertices The vertices of the mesh
/// \param colors The uvs of the mesh
void MeshRenderer::Initialize(
        std::vector<unsigned short> const& indexes,
        std::vector<glm::vec3>      const& vertices,
        std::vector<glm::vec2>      const& uvs)
{
    if(m_vao != 0)
    {
        glDeleteBuffers(1, &m_indexesObject);
        glDeleteBuffers(1, &m_verticesObject);
        glDeleteBuffers(1, &m_uvsObject);

        m_indexesObject  = 0;
        m_verticesObject = 0;
        m_uvsObject      = 0;
        m_elementsCount  = 0;
    }
    else if(m_vao == 0)
    {
        glGenVertexArrays(1, &m_vao);
    }

    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_indexesObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexesObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned short) ,&indexes[0], GL_STREAM_DRAW);

    glGenBuffers(1, &m_verticesObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_verticesObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STREAM_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glGenBuffers(1, &m_uvsObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvsObject);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STREAM_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    m_elementsCount = static_cast<GLsizei>(indexes.size());
}

/// \brief Updates the mesh
/// \param indexes The indexes of the mesh
/// \param vertices The vertices of the mesh
/// \param uvs The uvs of the mesh
void MeshRenderer::Update(
        std::vector<unsigned short> const &indexes,
        std::vector<glm::vec3>      const& vertices,
        std::vector<glm::vec2>      const& uvs)
{
	if(indexes.size() == 0)
	{
		return;
	}

    if(m_elementsCount < indexes.size())
    {
        // The buffer is too small, we need
        Initialize(indexes, vertices, uvs);
        return;
    }

    glBindVertexArray(m_vao);

    glBindBuffer   (GL_ELEMENT_ARRAY_BUFFER, m_indexesObject);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexes.size() * sizeof(unsigned short), &indexes[0]);


    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexesObject);
    auto *data = (unsigned short *) glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(data, &indexes[0], indexes.size() * sizeof(unsigned short));
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

    glBindBuffer   (GL_ARRAY_BUFFER, m_verticesObject);
    auto *fdata = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    size_t count = vertices.size();
    for(size_t i = 0; i < count; ++i)
    {
        fdata[i * 3 + 0] = vertices[i].x;
        fdata[i * 3 + 1] = vertices[i].y;
        fdata[i * 3 + 2] = vertices[i].z;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);


    glBindBuffer   (GL_ARRAY_BUFFER, m_uvsObject);
    auto *udata = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    count = uvs.size();
    for(size_t i = 0; i < count; ++i)
    {
        udata[i * 2 + 0] = uvs[i].x;
        udata[i * 2 + 1] = uvs[i].y;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);*/

    glBindBuffer   (GL_ARRAY_BUFFER, m_verticesObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices[0]);

    glBindBuffer   (GL_ARRAY_BUFFER, m_uvsObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, uvs.size() * sizeof(glm::vec2), &uvs[0]);

    m_elementsCount = static_cast<GLsizei>(indexes.size());

    glBindVertexArray(0);
}

/// \brief Sets the renderer shader
/// \param pShader The pointer on the shader
void MeshRenderer::SetShader(IShader * pShader)
{
    m_pShader = pShader;
}

/// \brief Translates the model
/// \param Translation The translation vector
void MeshRenderer::Translate(glm::vec3 const& Translation)
{
    m_model = glm::translate(m_model, Translation);
}

/// \brief Sets the position of the mesh renderer
/// \param position The new position
void MeshRenderer::SetPosition(const glm::vec3 &position)
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, position);
}

} // !namespace