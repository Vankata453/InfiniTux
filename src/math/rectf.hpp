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

class RectF final
{
public:
  RectF(const float& x_, const float& y_,
        const float& w_, const float& h_) :
    x(x_),
    y(y_),
    w(w_),
    h(h_)
  {}

  const float& get_left() const { return x; }
  const float& get_top() const { return y; }
  const float& get_width() const { return w; }
  const float& get_height() const { return h; }

  SDL_FRect to_sdl() const
  {
    return { x, y, w, h };
  }

  friend std::ostream& operator<<(std::ostream& os, const RectF& rect);

private:
  float x, y, w, h;
};
