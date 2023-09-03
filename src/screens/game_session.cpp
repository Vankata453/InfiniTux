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

#include "screens/game_session.hpp"

#include "game/player.hpp"
#include "main/resources.hpp"
#include "video/texture_manager.hpp"

GameSession::GameSession() :
  m_collision_system(),
  m_player(add<Player>()),
  m_state(State::START_GAME),
  m_start_text(TextureManager::current()->create_text(Resources::Fonts::default_font, "Jump to start!", Color(255, 255, 255, 255)))
{
  Player& player2 = add<Player>();
  player2.set_pos(Vector(150.f, 240.f));

  flush_game_objects();
}


void
GameSession::draw(Renderer& renderer)
{
  /** Draw collision rectangles. */
  m_collision_system.draw(renderer);

  /** Draw objects. */
  GameObjectManager::draw(renderer);

  switch (m_state)
  {
    case State::START_GAME:
    {
      // Draw "Jump to start!" text.
      renderer.draw_texture(m_start_text,
                            Vector(renderer.get_width() / 2 - m_start_text.get_width() / 2,
                                   renderer.get_height() / 3), 0);
      break;
    }
  }
}

void
GameSession::update(const float& elapsed_sec)
{
  //if (m_state != State::ACTIVE)
   // return; // Update objects, only if active.

  /** Perform collision checks. */
  m_collision_system.update();

  /** Update objects. */
  GameObjectManager::update(elapsed_sec);
}

void
GameSession::event(const SDL_Event& ev)
{
  if (ev.type == SDL_KEYDOWN)
  {
    // Process the event by the player.
    // TODO: Process a custom control, derived by the pressed key.
    m_player.process_control(ev.key);
  }
}
