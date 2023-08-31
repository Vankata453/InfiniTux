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

#include "video/renderer.hpp"

/** Represents a renderer, powered by SDL. */
class SDLRenderer final : public Renderer
{
public:
  SDLRenderer(SDL_Window* window, const Color& default_color);
  ~SDLRenderer();

  void set_default_color(const Color& color) { m_default_color = color; }

  /** Functions */
  SDL_Texture* create_texture(SDL_Surface* surface) const override;

protected:
  /** Processing */
  void process_draw_line(const LineRenderRequest& request) override;
  void process_draw_rect(const RectRenderRequest& request) override;
  void process_draw_fill_rect(const FillRectRenderRequest& request) override;
  void process_draw_texture(const TextureRenderRequest& request) override;
  void process_draw_texture_scaled(const TextureScaledRenderRequest& request) override;

  /** Rendering */
  void clear() override;
  void render() override;

private:
  void set_draw_color(const Color& color);

private:
  SDL_Renderer* m_renderer;

  Color m_default_color;

private:
  SDLRenderer(const SDLRenderer&) = delete;
  SDLRenderer& operator=(const SDLRenderer&) = delete;
};
