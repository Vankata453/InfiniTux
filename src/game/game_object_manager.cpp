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

#include "game/game_object_manager.hpp"

#include <algorithm>

GameObjectManager::GameObjectManager() :
  m_objects(),
  m_new_objects()
{
}


void
GameObjectManager::draw(Renderer& renderer)
{
  /** Draw objects. */
  for (auto& object : m_objects)
    object->draw(renderer);
}

void
GameObjectManager::update(const float& elapsed_sec)
{
  /** Update objects. */
  for (auto& object : m_objects)
    object->update(elapsed_sec);

  /** Flush objects. */
  flush_game_objects();
}


void
GameObjectManager::flush_game_objects()
{
  /** Remove objects. */
  m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
                                 [](const auto& obj)
                                 {
                                   return obj->m_scheduled_for_removal;
                                 }), m_objects.end());

  /** Add objects. */
  if (!m_new_objects.empty())
  {
    m_objects.insert(m_objects.end(),
                     std::make_move_iterator(m_new_objects.begin()),
                     std::make_move_iterator(m_new_objects.end()));
    m_new_objects.clear();
  }
}
