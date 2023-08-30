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

struct Color
{
public:
  Color(const Uint8& r_, const Uint8& g_,
        const Uint8& b_, const Uint8& a_) :
  r(r_), g(g_), b(b_), a(a_) {}

  friend std::ostream& operator<<(std::ostream& os, const Color& color);

public:
  Uint8 r, g, b, a;
};
