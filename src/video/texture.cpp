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

#include "video/texture.hpp"

Texture::Texture(SDL_Texture* texture) :
  m_texture(texture),
  m_size(0.f, 0.f)
{
  /** Size */
  int w, h;
  SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
  m_size = SizeF(w, h); // Convert integer size to float for convenience.
}

Texture::~Texture()
{
  SDL_DestroyTexture(m_texture);
}
