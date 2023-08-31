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

#include "video/texture_manager.hpp"

#include <SDL2/SDL_image.h>

#include "video/renderer.hpp"
#include "video/sdl/sdl_error.hpp"

TextureManager::TextureManager(const Renderer& renderer) :
  m_renderer(renderer),
  m_texture_map()
{
  /** Initialize SDL2_image */
  if (IMG_Init(IMG_INIT_PNG) < 0)
    throw SDLError("IMG_Init", "Error initializing SDL2_image with PNG support", IMG_GetError());
  if (IMG_Init(IMG_INIT_JPG) < 0)
    throw SDLError("IMG_Init", "Error initializing SDL2_image with JPG support", IMG_GetError());

  /** Initialize SDL2_ttf */
  if (TTF_Init() < 0)
    throw SDLError("TTF_Init", "Error initializing SDL2_ttf", TTF_GetError());
}


const Texture&
TextureManager::load(const char* file)
{
  auto it = m_texture_map.find(file);
  if (it == m_texture_map.end())
    return create(file);

  return *it->second;
}

const Texture&
TextureManager::create(const char* file)
{
  SDL_Surface* surface = IMG_Load(file);
  if (!surface)
    throw SDLError("IMG_Load", "Error loading image to surface", TTF_GetError());

  auto texture = std::make_unique<Texture>(m_renderer.create_texture(surface));
  Texture& texture_ref = *texture;

  m_texture_map.insert({ file, std::move(texture) });

  return texture_ref;
}


Texture
TextureManager::create_text(TTF_Font* font, const std::string& text,
                            const Color& color)
{
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color.to_sdl());
  if (!surface)
    throw SDLError("TTF_RenderText_Solid", "Error rendering text to surface", TTF_GetError());

  SDL_Texture* texture = m_renderer.create_texture(surface);
  SDL_FreeSurface(surface);

  return Texture(texture);
}
