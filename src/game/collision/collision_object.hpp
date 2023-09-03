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

#include "game/collision/collision_hit.hpp"
#include "math/rectf.hpp"

/** Abstract class, which represents an object, taking part in collision. */
class CollisionObject
{
public:
  CollisionObject();
  virtual ~CollisionObject();

  virtual void collision(CollisionObject* obj, const CollisionHit& hit) {}

  const RectF& get_bbox() const { return m_bbox; }

protected:
  RectF m_bbox;

private:
  CollisionObject(const CollisionObject&) = delete;
  CollisionObject& operator=(const CollisionObject&) = delete;
};
