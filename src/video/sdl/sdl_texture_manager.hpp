/*
* InfiniTux - An infinite jumping game, featuring Tux.
* Copyright (C) 2023 Vankata453
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "video/texture_manager.hpp"

class SDL_Renderer;

/** Represents a texture manager, which creates textures using an SDL renderer. */
class SDLTextureManager final : public TextureManager
{
public:
  SDLTextureManager(SDL_Renderer* renderer);

protected:
  SDL_Texture* create_texture(const char* file) override;

private:
  SDL_Renderer* m_renderer;

private:
  SDLTextureManager(const SDLTextureManager&) = delete;
  SDLTextureManager& operator=(const SDLTextureManager&) = delete;
};
