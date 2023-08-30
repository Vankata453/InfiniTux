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
  m_requests()
{
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
      case RenderRequest::RECT:
        process_draw_rect(static_cast<RectRenderRequest&>(*request));
        break;
      case RenderRequest::FILL_RECT:
        process_draw_fill_rect(static_cast<FillRectRenderRequest&>(*request));
        break;
    }
  }

  // Render everything.
  render();

  // Clear all requests.
  m_requests.clear();
}
