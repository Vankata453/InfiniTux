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

#include "video/renderer.hpp"

/** Abstract class, which represents a screen.
    Determines what is drawn on screen, and processes any occuring events. */
class Screen
{
public:
  Screen() {}

  /** Perform actions on screen setup and leave. */
  virtual void setup() {}
  virtual void leave() {}

  /** Draw items on screen every frame. */
  virtual void draw(Renderer& renderer) = 0;

  /** Process any occuring events. */
  virtual void event(const SDL_Event& ev) = 0;

private:
  Screen(const Screen&) = delete;
  Screen& operator=(const Screen&) = delete;
};
