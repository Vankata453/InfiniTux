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

/** Abstract class, which represents a renderer.
    Processes rendering requests in organized layers.  */
class Renderer
{
public:
  Renderer();

  /** Requesting */
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

  /** Updating (processing + rendering) */
  void update();

protected:
  /** Processing */
  virtual void process_draw_rect(const RectRenderRequest& request) = 0;
  virtual void process_draw_fill_rect(const FillRectRenderRequest& request) = 0;

  /** Rendering */
  virtual void clear() = 0;
  virtual void render() = 0;

private:
  std::vector<std::unique_ptr<RenderRequest>> m_requests;

private:
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;
};
