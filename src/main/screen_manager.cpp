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

#include <stdexcept>

#include <SDL2/SDL.h>

#include "video/color.hpp"
#include "video/renderer.hpp"
#include "video/sdl/sdl_error.hpp"
#include "video/sdl/sdl_video_system.hpp"

ScreenManager::ScreenManager() :
  m_video_system()
  //m_screen_stack()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw SDLError("SDL_Init", "Couldn't initialize SDL", SDL_GetError());

  m_video_system.reset(new SDLVideoSystem());
}

ScreenManager::~ScreenManager()
{
  m_video_system.reset();

  SDL_Quit();
}

int
ScreenManager::main_loop()
{
  bool quit = false;
  SDL_Event ev;

  while (!quit)
  {
    while (SDL_PollEvent(&ev))
    {
      if (ev.type == SDL_QUIT)
        quit = true;
    }

    // TEMPORARY: Draw test rectangles and lines
    m_video_system->get_renderer().draw_rect(0.f, 10.f, 20.f, 20.f, Color(0, 188, 255, 255), 1);
    m_video_system->get_renderer().draw_fill_rect(0.f, 60.f, 20.f, 20.f, Color(0, 255, 188, 255), 1);
    m_video_system->get_renderer().draw_line(40.f, 50.f, 80.f, 92.f, Color(255, 30, 92, 255), 5);

    m_video_system->get_renderer().update();
  }

  return 0;
}
