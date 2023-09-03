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

#include "main/screen_manager.hpp"

#include <cassert>
#include <stdexcept>

#include <SDL2/SDL.h>

#include "main/constants.hpp"
#include "main/resources.hpp"
#include "main/screen.hpp"
#include "screens/game_session.hpp"
#include "video/renderer.hpp"
#include "video/sdl/sdl_error.hpp"
#include "video/sdl/sdl_video_system.hpp"

ScreenManager::ScreenManager() :
  m_video_system(),
  m_screen_stack(),
  m_new_screen_stack(),
  m_pop_screens(0)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw SDLError("SDL_Init", "Couldn't initialize SDL", SDL_GetError());

  m_video_system.reset(new SDLVideoSystem());
  Resources::initialize();

  // Set up and push the initial screen.
  auto init_screen = std::make_unique<GameSession>();
  init_screen->setup();
  m_screen_stack.push_back(std::move(init_screen));
}

ScreenManager::~ScreenManager()
{
  // Leave the current screen.
  m_screen_stack.back()->leave();

  Resources::destroy();
  m_video_system.reset();

  SDL_Quit();
}


int
ScreenManager::main_loop()
{
  Renderer& renderer = m_video_system->get_renderer();

  bool quit = false;
  SDL_Event ev;
  Uint32 refresh_time = SDL_GetTicks() + LOGICAL_FPS;
  Uint32 last_update_time = 0;

  while (!quit)
  {
    auto& screen = m_screen_stack.back();

    /** Event handling */
    while (SDL_PollEvent(&ev))
    {
      if (ev.type == SDL_QUIT)
      {
        quit = true;
        break;
      }

      // The screen should handle the event.
      screen->event(ev);
    }

    /** Updating */
    const Uint32 current_time = SDL_GetTicks();
    screen->update(static_cast<float>(current_time - last_update_time) / 1000.f);
    last_update_time = current_time;

    /** Rendering */
    screen->draw(renderer); // Render the screen.
    renderer.update();

    /** Update ScreenManager */
    handle_screen_switch();

    /** Achieve constant framerate */
    SDL_Delay(refresh_time - current_time);
    refresh_time += LOGICAL_FPS;
  }

  return 0;
}


void
ScreenManager::pop_screen()
{
  // Will be handled later in handle_screen_switch().
  m_pop_screens++;
}

void
ScreenManager::handle_screen_switch()
{
  if (m_pop_screens == 0 && m_new_screen_stack.empty())
    return; // No screens to switch between.

  // Leave the current screen.
  m_screen_stack.back()->leave();

  /** Pop screens */
  assert(m_pop_screens < m_screen_stack.size());
  while (m_pop_screens > 0)
  {
    m_screen_stack.pop_back();
    m_pop_screens--;
  }

  /** Push screens */
  if (!m_new_screen_stack.empty())
  {
    m_screen_stack.insert(m_screen_stack.end(),
                          std::make_move_iterator(m_new_screen_stack.begin()),
                          std::make_move_iterator(m_new_screen_stack.end()));
    m_new_screen_stack.clear();
  }

  // Set up the new screen.
  m_screen_stack.back()->setup();
}


Screen&
ScreenManager::get_current_screen() const
{
  return *m_screen_stack.back();
}
