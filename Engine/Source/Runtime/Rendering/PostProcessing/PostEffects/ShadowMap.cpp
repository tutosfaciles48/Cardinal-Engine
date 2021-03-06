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

/// \file       ShadowMap.cpp
/// \date       08/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/ShadowMap.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
ShadowMap::ShadowMap() : PostEffect(PostEffect::EType::ShadowMap, "Shadow map")
{
    // Getting shader ...
    m_shaderID = (uint)ShaderManager::GetShaderID("DepthBufferPostProcess");

    // Getting uniforms
    m_depthTextureID = glGetUniformLocation(m_shaderID, "depthTexture");
}

/// \brief Destructor
ShadowMap::~ShadowMap() // NOLINT
{
    // None
}

/// \brief Applies the effect from the given textures
/// \param colorTexture The color texture
/// \param depthTexture The depth buffer texture
/// \param lightScatteringTexture The result of the light scattering pass
void ShadowMap::ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture, uint shadowMapTexture)
{
    glUseProgram   (m_shaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, shadowMapTexture);
    glUniform1i    (m_depthTextureID, 0);
}

/// \brief Called to draw the GUI
void ShadowMap::OnGUI()
{
    ImGui::Checkbox("Enabled###Enabled_ShadowMap", &m_bIsActive);
}

} // !namespace