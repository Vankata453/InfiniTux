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

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <memory>
#include <string>

#include "video/color.hpp"
#include "video/texture.hpp"

/** Abstract class, which represents a texture manager.
    Creates textures, binds textures to file paths. */
class TextureManager
{
public:
  TextureManager();

  const Texture& load(const char* file);

  Texture create_text(TTF_Font* font, const std::string& text,
                      const Color& color);

private:
  const Texture& create(const char* file);

protected:
  virtual SDL_Texture* create_texture(SDL_Surface* surface) const = 0;

private:
  std::map<const char*, std::unique_ptr<Texture>> m_texture_map;

private:
  TextureManager(const TextureManager&) = delete;
  TextureManager& operator=(const TextureManager&) = delete;
};
