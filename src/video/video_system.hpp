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

#include <memory>
#include <vector>

class Renderer;
class SDL_Window;

/** Abstract class, which represents a video system. */
class VideoSystem : public CurrentObject<VideoSystem>
{
public:
  VideoSystem();
  virtual ~VideoSystem();

  SDL_Window* get_window() const { return m_window; }
  Renderer& get_renderer() const { return *m_renderer; }

protected:
  SDL_Window* m_window;
  std::unique_ptr<Renderer> m_renderer;

private:
  VideoSystem(const VideoSystem&) = delete;
  VideoSystem& operator=(const VideoSystem&) = delete;
};
