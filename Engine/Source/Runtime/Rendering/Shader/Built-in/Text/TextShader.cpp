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

/// \file       TextShader.cpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Shader/Built-in
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"

#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/Text/TextShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
TextShader::TextShader()
{
    m_shaderID       = ShaderManager::GetShaderID("Text");
    m_texture        = m_texture = TextureManager::GetTextureID("SAORegular");
    m_textureSampler = glGetUniformLocation(m_shaderID, "textureSampler");
    m_textColor      = glGetUniformLocation(m_shaderID, "textColor");
}

/// \brief Sets up the pipeline for the shader
/// \param MVP The Projection-View-Model matrix to pass to the shader
void TextShader::Begin(glm::mat4 const& MVP, glm::mat4 const& P, glm::mat4 const& V, glm::mat4 const& M, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    glUseProgram      (m_shaderID);
    glActiveTexture   (GL_TEXTURE0);
    glBindTexture     (GL_TEXTURE_2D, m_texture);
    glUniform1i       (m_textureSampler, 0);
    SetFloat4         (m_textColor, m_color.x, m_color.y, m_color.z, m_color.a);

    glDisable(GL_CULL_FACE);
}

/// \brief Restore the pipeline state
void TextShader::End()
{
    glEnable(GL_CULL_FACE);
}

/// \brief Sets the color of the text
/// \param color The color
void TextShader::SetColor(glm::vec4 const& color)
{
    m_color = color;
}

} // !namespace

