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

#include "main/screen.hpp"

class Texture;

/** Screen to test rendering and event handling. */
class TestScreen final : public Screen
{
public:
  TestScreen();

  void setup() override;
  void leave() override;

  void draw(Renderer& renderer) override;
  void event(const SDL_Event& ev) override;

private:
  Texture get_text_texture() const;

private:
  const Texture& m_texture;
  Texture m_text_texture;

private:
  TestScreen(const TestScreen&) = delete;
  TestScreen& operator=(const TestScreen&) = delete;
};
