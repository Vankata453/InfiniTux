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

#include "video/sdl/sdl_renderer.hpp"

#include <SDL2/SDL.h>

#include "video/sdl/sdl_error.hpp"

SDLRenderer::SDLRenderer(SDL_Window* window, const Color& default_color) :
  m_renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)),
  m_size(0.f, 0.f),
  m_default_color(default_color)
{
  SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

  // Get size.
  int w, h;
  SDL_GetRendererOutputSize(m_renderer, &w, &h);
  m_size = SizeF(w, h); // Convert integer size to float for convenience.
}

SDLRenderer::~SDLRenderer()
{
  m_texture_manager.reset();

  SDL_DestroyRenderer(m_renderer);
}


void
SDLRenderer::clear()
{
  set_draw_color(m_default_color);
  SDL_RenderClear(m_renderer);
}

void
SDLRenderer::render()
{
  SDL_RenderPresent(m_renderer);
}


void
SDLRenderer::process_draw_line(const LineRenderRequest& request)
{
  set_draw_color(request.color);

  if (SDL_RenderDrawLineF(m_renderer, request.p1.x, request.p1.y,
                                      request.p2.x, request.p2.y) < 0)
    throw SDLError("SDL_RenderDrawLineF", "Error drawing line", SDL_GetError());
}

void
SDLRenderer::process_draw_rect(const RectRenderRequest& request)
{
  set_draw_color(request.color);

  SDL_FRect rect = request.rect.to_sdl();
  if (SDL_RenderDrawRectF(m_renderer, &rect) < 0)
    throw SDLError("SDL_RenderDrawRectF", "Error drawing rectangle", SDL_GetError());
}

void
SDLRenderer::process_draw_fill_rect(const FillRectRenderRequest& request)
{
  set_draw_color(request.color);

  SDL_FRect rect = request.rect.to_sdl();
  if (SDL_RenderFillRectF(m_renderer, &rect) < 0)
    throw SDLError("SDL_RenderFillRectF", "Error drawing filled rectangle", SDL_GetError());
}

void
SDLRenderer::process_draw_texture(const TextureRenderRequest& request)
{
  SDL_SetTextureColorMod(request.texture.get_sdl(), request.color.r, request.color.g,
                                                    request.color.b);
  SDL_SetTextureAlphaMod(request.texture.get_sdl(), request.color.a);

  SDL_FRect dest_rect = { request.pos.x, request.pos.y,
                          request.texture.get_width(), request.texture.get_height() };
  if (SDL_RenderCopyF(m_renderer, request.texture.get_sdl(), NULL, &dest_rect) < 0)
    throw SDLError("SDL_RenderCopyF", "Error drawing texture", SDL_GetError());
}

void
SDLRenderer::process_draw_texture_scaled(const TextureScaledRenderRequest& request)
{
  SDL_SetTextureColorMod(request.texture.get_sdl(), request.color.r, request.color.g,
                                                    request.color.b);
  SDL_SetTextureAlphaMod(request.texture.get_sdl(), request.color.a);

  SDL_FRect dest_rect = { request.pos.x, request.pos.y,
                          request.size.w, request.size.h };
  if (SDL_RenderCopyF(m_renderer, request.texture.get_sdl(), NULL, &dest_rect) < 0)
    throw SDLError("SDL_RenderCopyF", "Error drawing scaled texture", SDL_GetError());
}


SDL_Texture*
SDLRenderer::create_texture(SDL_Surface* surface) const
{
  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  if (!texture)
    throw SDLError("SDL_CreateTextureFromSurface", "Error creating texture from surface", SDL_GetError());

  return texture;
}


void
SDLRenderer::set_draw_color(const Color& color)
{
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g,
                                     color.b, color.a);
}
