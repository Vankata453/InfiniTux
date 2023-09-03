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

#include "util/current_object.hpp"

#include <vector>

class CollisionObject;
class Renderer;

/** Collision system. On update, determines whether any two objects intersect. */
class CollisionSystem final : public CurrentObject<CollisionSystem>
{
public:
  CollisionSystem();

  /** Render collision rectangles, if enabled. */
  void draw(Renderer& renderer);

  /** Perform collision checks (called each frame). */
  void update();

  void add_object(CollisionObject* obj);
  void remove_object(CollisionObject* obj);

private:
  std::vector<CollisionObject*> m_objects;

private:
  CollisionSystem(const CollisionSystem&) = delete;
  CollisionSystem& operator=(const CollisionSystem&) = delete;
};
