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

#include "video/sdl/sdl_texture_manager.hpp"

#include <SDL2/SDL_image.h>

#include "video/sdl/sdl_error.hpp"

SDLTextureManager::SDLTextureManager(SDL_Renderer* renderer) :
  m_renderer(renderer)
{
  if (IMG_Init(IMG_INIT_PNG) < 0)
    throw SDLError("IMG_Init", "Error initializing SDL2_image with PNG support", IMG_GetError());
  if (IMG_Init(IMG_INIT_JPG) < 0)
    throw SDLError("IMG_Init", "Error initializing SDL2_image with JPG support", IMG_GetError());
} 


SDL_Texture*
SDLTextureManager::create_texture(const char* file) const
{
  SDL_Texture* texture = IMG_LoadTexture(m_renderer, file);
  if (!texture)
    throw SDLError("IMG_LoadTexture", "Error loading texture from file", IMG_GetError());

  return texture;
}

SDL_Texture*
SDLTextureManager::create_texture(SDL_Surface* surface)const
{
  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  if (!texture)
    throw SDLError("SDL_CreateTextureFromSurface", "Error creating texture from surface", SDL_GetError());

  return texture;
}
