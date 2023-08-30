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
  m_default_color(default_color)
{
  SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

SDLRenderer::~SDLRenderer()
{
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
    throw SDLError("SDL_RenderFillRectF", "Error drawing rectangle", SDL_GetError());
}


void
SDLRenderer::set_draw_color(const Color& color)
{
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g,
                                     color.b, color.a);
}
