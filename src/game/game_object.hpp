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

/** Abstract class, which represents a game object.
    Serves as a component of a game. Able to be drawn on screen and updated. */
class GameObject
{
  friend class GameObjectManager;

public:
  GameObject() :
    m_scheduled_for_removal(false)
  {}

  /** Draw the object on screen every frame. */
  virtual void draw(Renderer& renderer) = 0;

  /** Update object logic. */
  virtual void update(const float& elapsed_sec) = 0;

  bool is_valid() const { return !m_scheduled_for_removal; }

private:
  bool m_scheduled_for_removal;

private:
  GameObject(const GameObject&) = delete;
  GameObject& operator=(const GameObject&) = delete;
};
