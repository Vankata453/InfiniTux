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

#include <ostream>

#include "math/sizef.hpp"
#include "math/vector.hpp"

class RectF final
{
public:
  RectF(const float& x, const float& y,
        const float& w, const float& h) :
    m_pos(x, y),
    m_size(w, h)
  {}
  RectF(const Vector& pos,
        const float& w, const float& h) :
    m_pos(pos),
    m_size(w, h)
  {}
  RectF(const float& x, const float& y,
        const SizeF& size) :
    m_pos(x, y),
    m_size(size)
  {}
  RectF(const Vector& pos, const SizeF& size) :
    m_pos(pos),
    m_size(size)
  {}

  const float& get_left() const { return m_pos.x; }
  const float& get_top() const { return m_pos.y; }
  const float& get_width() const { return m_size.w; }
  const float& get_height() const { return m_size.h; }

  const Vector& get_pos() const { return m_pos; }
  const SizeF& get_size() const { return m_size; }

  SDL_FRect to_sdl() const
  {
    return { get_left(), get_top(),
             get_width(), get_height() };
  }
  SDL_Rect to_sdl_rect() const
  {
    return { static_cast<int>(get_left()), static_cast<int>(get_top()),
             static_cast<int>(get_width()), static_cast<int>(get_height()) };
  }

  friend std::ostream& operator<<(std::ostream& os, const RectF& rect);

private:
  Vector m_pos;
  SizeF m_size;
};
