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

#include "video/renderer.hpp"

#include <algorithm>

Renderer::Renderer() :
  m_texture_manager(new TextureManager(*this)),
  m_requests()
{
}


void
Renderer::draw_line(const float& x1, const float& y1,
                    const float& x2, const float& y2,
                    const Color& color, const int& layer)
{
  draw_line(Vector(x1, y1), Vector(x2, y2), color, layer);
}

void
Renderer::draw_line(const Vector& p1, const Vector& p2,
                    const Color& color, const int& layer)
{
  m_requests.push_back(std::make_unique<LineRenderRequest>(layer, p1, p2, color));
}

void
Renderer::draw_rect(const float& x, const float& y,
                    const float& w, const float& h,
                    const Color& color, const int& layer)
{
  draw_rect(RectF(x, y, w, h), color, layer);
}

void
Renderer::draw_rect(const RectF& rect, const Color& color,
                    const int& layer)
{
  m_requests.push_back(std::make_unique<RectRenderRequest>(layer, rect, color));
}

void
Renderer::draw_fill_rect(const float& x, const float& y,
                         const float& w, const float& h,
                         const Color& color, const int& layer)
{
  draw_fill_rect(RectF(x, y, w, h), color, layer);
}

void
Renderer::draw_fill_rect(const RectF& rect, const Color& color,
                         const int& layer)
{
  m_requests.push_back(std::make_unique<FillRectRenderRequest>(layer, rect, color));
}

void
Renderer::draw_texture(const Texture& texture, const Vector& pos,
                       const int& layer)
{
  draw_texture_mod(texture, pos, Color(), layer);
}

void
Renderer::draw_texture_mod(const Texture& texture, const Vector& pos,
                           const Color& color, const int& layer)
{
  m_requests.push_back(std::make_unique<TextureRenderRequest>(layer, texture, pos, color));
}

void
Renderer::draw_texture_scaled(const Texture& texture, const RectF& dest_rect,
                              const int& layer)
{
  draw_texture_scaled_mod(texture, dest_rect, Color(), layer);
}

void
Renderer::draw_texture_scaled_mod(const Texture& texture, const RectF& dest_rect,
                                  const Color& color, const int& layer)
{
  m_requests.push_back(std::make_unique<TextureScaledRenderRequest>(layer, texture, dest_rect, color));
}


void
Renderer::update()
{
  // Clear everything on screen.
  clear();

  // Sort all render requests by layer.
  std::stable_sort(m_requests.begin(), m_requests.end(),
                   [](const auto& lhs, const auto& rhs)
                   {
                     return lhs->layer < rhs->layer;
                   });

  // Process each request, according to its type.
  for (const auto& request : m_requests)
  {
    switch (request->get_type())
    {
      case RenderRequest::LINE:
        process_draw_line(static_cast<LineRenderRequest&>(*request));
        break;
      case RenderRequest::RECT:
        process_draw_rect(static_cast<RectRenderRequest&>(*request));
        break;
      case RenderRequest::FILL_RECT:
        process_draw_fill_rect(static_cast<FillRectRenderRequest&>(*request));
        break;
      case RenderRequest::TEXTURE:
        process_draw_texture(static_cast<TextureRenderRequest&>(*request));
        break;
      case RenderRequest::TEXTURE_SCALED:
        process_draw_texture_scaled(static_cast<TextureScaledRenderRequest&>(*request));
        break;
    }
  }

  // Render everything.
  render();

  // Clear all requests.
  m_requests.clear();
}
