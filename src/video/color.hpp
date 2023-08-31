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

class Color final
{
public:
  Color() :
    r(255), g(255), b(255), a(255) {}
  Color(const Uint8& r_, const Uint8& g_,
        const Uint8& b_, const Uint8& a_) :
    r(r_), g(g_), b(b_), a(a_) {}

  SDL_Color to_sdl() const
  {
    return { r, g, b, a };
  }

  friend std::ostream& operator<<(std::ostream& os, const Color& color);

public:
  Uint8 r, g, b, a;
};
