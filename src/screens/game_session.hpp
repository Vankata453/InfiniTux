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

#include "game/game_object_manager.hpp"
#include "main/screen.hpp"

#include <memory>
#include <vector>

#include "game/collision/collision_system.hpp"
#include "game/player.hpp"

class Texture;

/** Screen, which handles gameplay, objects and level randomization. */
class GameSession final : public Screen,
                          public GameObjectManager
{
public:
  GameSession();

  void draw(Renderer& renderer) override;
  void update(const float& elapsed_sec) override;
  void event(const SDL_Event& ev) override;

private:
  enum class State
  {
    START_GAME, /** Waiting for input to start game. */
    ACTIVE, /** Active. */
    GAME_OVER /** Stopped, the player has lost. */
  };

private:
  CollisionSystem m_collision_system;

  Player& m_player;
  State m_state;

  const Texture m_start_text;

private:
  GameSession(const GameSession&) = delete;
  GameSession& operator=(const GameSession&) = delete;
};
