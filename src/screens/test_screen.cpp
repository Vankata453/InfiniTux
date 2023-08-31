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

#include "screens/test_screen.hpp"

#include <sstream>
#include <iostream>

#include "main/resources.hpp"
#include "main/screen_manager.hpp"
#include "video/texture_manager.hpp"

TestScreen::TestScreen() :
  m_texture(TextureManager::current()->load("../data/images/creatures/tux/tux.png")),
  m_text_texture(get_text_texture())
{
}


void
TestScreen::setup()
{
std::cout << "setting up" << std::endl;
}

void
TestScreen::leave()
{
std::cout << "leaving" << std::endl;
}


void
TestScreen::draw(Renderer& renderer)
{
  // TEMPORARY: Draw test rectangles, lines and textures
  renderer.draw_rect(0.f, 10.f, 20.f, 20.f, Color(0, 188, 255, 255), 1);
  renderer.draw_fill_rect(0.f, 60.f, 20.f, 20.f, Color(0, 255, 188, 255), 1);
  renderer.draw_line(40.f, 50.f, 80.f, 92.f, Color(255, 30, 92, 255), 5);
  renderer.draw_texture(m_texture, Vector(100.f, 100.f), 102);
  renderer.draw_texture_mod(m_texture, Vector(200.f, 100.f), Color(255, 30, 92, 255), 102);
  renderer.draw_texture_scaled(m_texture,
      RectF(300.f, 100.f, m_texture.get_width() * 2, m_texture.get_height() * 2), 102);
  renderer.draw_texture_scaled_mod(m_texture,
      RectF(400.f, 100.f, m_texture.get_width() * 2, m_texture.get_height() * 2), Color(255, 30, 92, 255), 102);
  renderer.draw_texture(m_text_texture, Vector(400.f, 200.f), 102);
}

void
TestScreen::event(const SDL_Event& ev)
{
  if (ev.type == SDL_KEYDOWN)
  {
    if (ev.key.keysym.sym == SDLK_ESCAPE)
    {
      ScreenManager::current()->pop_screen();
    }
    else
    {
      ScreenManager::current()->push_screen<TestScreen>();
      ScreenManager::current()->push_screen<TestScreen>();
    }
  }
}


Texture
TestScreen::get_text_texture() const
{
  std::ostringstream out;
  out << this;
  return TextureManager::current()->create_text(Resources::Fonts::default_font, out.str(), Color(0, 255, 188, 255));
}
