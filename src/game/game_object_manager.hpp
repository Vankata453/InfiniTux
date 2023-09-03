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

#include <memory>
#include <vector>

#include "game/game_object.hpp"

/** Represents a manager of an array of GameObjects. */
class GameObjectManager
{
public:
  GameObjectManager();

  /** Perform collision checks (called each frame). */
  virtual void draw(Renderer& renderer);
  virtual void update(const float& elapsed_sec);

  template<typename T, typename... Args>
  T& add(Args&&... args)
  {
    auto obj = std::make_unique<T>(std::forward<Args>(args)...);
    T& obj_ref = *obj;

    // Will be handled later in flush_game_objects().
    m_new_objects.push_back(std::move(obj));

    return obj_ref;
  }

protected:
  void flush_game_objects();

protected:
  std::vector<std::unique_ptr<GameObject>> m_objects;

private:
  std::vector<std::unique_ptr<GameObject>> m_new_objects;

private:
  GameObjectManager(const GameObjectManager&) = delete;
  GameObjectManager& operator=(const GameObjectManager&) = delete;
};
