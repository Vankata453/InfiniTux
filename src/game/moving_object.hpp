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

#include "game/collision/collision_object.hpp"
#include "game/game_object.hpp"

/** Abstract class, which represents a game object, containing a bounding box.
    Takes part in collision. */
class MovingObject : public GameObject,
                     public CollisionObject
{
public:
  MovingObject() {}

  void set_pos(const Vector& pos) { m_bbox.set_pos(pos); }
  void set_size(const SizeF& size) { m_bbox.set_size(size); }

private:
  MovingObject(const MovingObject&) = delete;
  MovingObject& operator=(const MovingObject&) = delete;
};
