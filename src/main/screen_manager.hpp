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

class Screen;
class VideoSystem;

class ScreenManager final : public CurrentObject<ScreenManager>
{
public:
  ScreenManager();
  ~ScreenManager() override;

  int main_loop();

  /** Screen management */
  template<typename T, typename... Args>
  void push_screen(Args&&... args)
  {
    // Will be handled later in handle_screen_switch().
    m_new_screen_stack.push_back(std::make_unique<T>(std::forward<Args>(args)...));
  }
  void pop_screen();

  Screen& get_current_screen() const;

private:
  void handle_screen_switch();

private:
  std::unique_ptr<VideoSystem> m_video_system;

  std::vector<std::unique_ptr<Screen>> m_screen_stack;
  std::vector<std::unique_ptr<Screen>> m_new_screen_stack;
  size_t m_pop_screens;

private:
  ScreenManager(const ScreenManager&) = delete;
  ScreenManager& operator=(const ScreenManager&) = delete;
};
