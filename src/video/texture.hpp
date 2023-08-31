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

#include <SDL2/SDL.h>

#include "math/sizef.hpp"

/** Wrapper to SDL_Texture, containing information about the texture. */
class Texture final
{
public:
  Texture(SDL_Texture* texture);
  ~Texture();

  SDL_Texture* get_sdl() const { return m_texture; }

  const float& get_width() const { return m_size.w; }
  const float& get_height() const { return m_size.h; }
  const SizeF& get_size() const { return m_size; }

private:
  SDL_Texture* m_texture;

  SizeF m_size;

private:
  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;
};
