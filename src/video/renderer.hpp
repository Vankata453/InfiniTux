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

#include <memory>
#include <vector>

#include "video/render_request.hpp"
#include "video/texture_manager.hpp"

/** Abstract class, which represents a renderer.
    Processes rendering requests in organized layers. */
class Renderer
{
public:
  Renderer();

  TextureManager& get_texture_manager() const { return *m_texture_manager; }

  /** Functions */
  virtual SDL_Texture* create_texture(SDL_Surface* surface) const = 0;

  /** Requesting */
  void draw_line(const float& x1, const float& y1,
                 const float& x2, const float& y2,
                 const Color& color, const int& layer);
  void draw_line(const Vector& p1, const Vector& p2,
                 const Color& color, const int& layer);
  void draw_rect(const float& x, const float& y,
                 const float& w, const float& h,
                 const Color& color, const int& layer);
  void draw_rect(const RectF& rect, const Color& color,
                 const int& layer);
  void draw_fill_rect(const float& x, const float& y,
                      const float& w, const float& h,
                      const Color& color, const int& layer);
  void draw_fill_rect(const RectF& rect, const Color& color,
                      const int& layer);
  void draw_texture(const Texture& texture, const Vector& pos,
                    const int& layer);
  void draw_texture_mod(const Texture& texture, const Vector& pos,
                        const Color& color, const int& layer);
  void draw_texture_scaled(const Texture& texture, const RectF& dest_rect,
                           const int& layer);
  void draw_texture_scaled_mod(const Texture& texture, const RectF& dest_rect,
                               const Color& color, const int& layer);

  /** Updating (processing + rendering) */
  void update();

protected:
  /** Processing */
  virtual void process_draw_line(const LineRenderRequest& request) = 0;
  virtual void process_draw_rect(const RectRenderRequest& request) = 0;
  virtual void process_draw_fill_rect(const FillRectRenderRequest& request) = 0;
  virtual void process_draw_texture(const TextureRenderRequest& request) = 0;
  virtual void process_draw_texture_scaled(const TextureScaledRenderRequest& request) = 0;

  /** Rendering */
  virtual void clear() = 0;
  virtual void render() = 0;

protected:
  std::unique_ptr<TextureManager> m_texture_manager;

private:
  std::vector<std::unique_ptr<RenderRequest>> m_requests;

private:
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;
};
