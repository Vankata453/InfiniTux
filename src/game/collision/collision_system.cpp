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

#include "game/collision/collision_system.hpp"

#include <algorithm>

#include "game/collision/collision_object.hpp"
#include "video/renderer.hpp"

CollisionSystem::CollisionSystem() :
  m_objects()
{
}


void
CollisionSystem::draw(Renderer& renderer)
{
  // TODO: Toggle this via an option

  /** Draw collision rectangles for every object. */
  for (CollisionObject* obj : m_objects)
  {
    renderer.draw_fill_rect(obj->get_bbox(), Color(255, 0, 0, 125), LAYER_OBJECTS + 10);
  }
}

void
CollisionSystem::update()
{
  CollisionHit hit;

  /** Determine whether any two objects intersect. */
  for (CollisionObject* obj1 : m_objects)
  {
    for (CollisionObject* obj2 : m_objects)
    {
      if (obj1 == obj2) continue; // Make sure we're checking against a different object.

      const RectF& bbox1 = obj1->get_bbox();
      const RectF& bbox2 = obj2->get_bbox();

      /** Check if the first object collides with the second.
          A check the other way around will be performed eventually. */

      if (!bbox1.overlaps(bbox2)) continue; // Make sure the two bounding boxes overlap.

      hit.left = (bbox1.get_right() > bbox2.get_left() && bbox1.get_right() < bbox2.get_right());
      hit.right = (bbox1.get_left() > bbox2.get_left() && bbox1.get_left() < bbox2.get_right());
      hit.top = (bbox1.get_bottom() > bbox2.get_top() && bbox1.get_bottom() < bbox2.get_bottom());
      hit.bottom = (bbox1.get_top() > bbox2.get_top() && bbox1.get_top() < bbox2.get_bottom());

      obj2->collision(obj1, hit);

      hit.reset();
    }
  }
}


void
CollisionSystem::add_object(CollisionObject* obj)
{
  m_objects.push_back(obj);
}

void
CollisionSystem::remove_object(CollisionObject* obj)
{
  m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
                                 [obj](CollisionObject* current_obj)
                                 {
                                   return obj == current_obj;
                                 }), m_objects.end());
}
