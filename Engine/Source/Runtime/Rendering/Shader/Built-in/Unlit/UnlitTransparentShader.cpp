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

/// \file       UnlitColorShader.cpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Shader/Built-in
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"

#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/Unlit/UnlitTransparentShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
UnlitTransparentShader::UnlitTransparentShader()
{
    m_shaderID  = ShaderManager::GetShaderID("UnlitTransparent");
    m_matrixID  = glGetUniformLocation((uint)m_shaderID, "MVP");
    m_textureID = glGetUniformLocation((uint)m_shaderID, "colorTexture");
}

/// \brief Sets up the pipeline for the shader
/// \param MVP The Projection-View-Model matrix to pass to the shader
void UnlitTransparentShader::Begin(glm::mat4 const& MVP, glm::mat4 const& P, glm::mat4 const& V, glm::mat4 const& M, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    // Pre-condition
    glUseProgram      ((uint)m_shaderID);
    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);

    glDisable      (GL_CULL_FACE);
    glDisable      (GL_MULTISAMPLE);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, (uint)m_texture);
    glUniform1i    (m_textureID, 0);
}

/// \brief Restore the pipeline state
void UnlitTransparentShader::End()
{
    glEnable  (GL_CULL_FACE);
}

/// \brief Sets the texture
void UnlitTransparentShader::SetTexture(int texture)
{
    m_texture = texture;
}

} // !namespace



