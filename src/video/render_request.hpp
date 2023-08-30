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

#include "math/rectf.hpp"
#include "video/color.hpp"

class RectF;

/** Represents a request for the renderer to process. */
class RenderRequest
{
public:
  /** REQUEST TYPE LIST */
  enum Type
  {
    LINE,
    RECT,
    FILL_RECT
  };

public:
  RenderRequest(const int& layer_) :
    layer(layer_)
  {}

  virtual Type get_type() const = 0;

public:
  const int layer;
};


/** REQUEST TYPE DECLARATIONS */


class LineRenderRequest final : public RenderRequest
{
public:
  LineRenderRequest(const int& layer_, const Vector& p1_,
                    const Vector& p2_, const Color& color_) :
    RenderRequest(layer_),
    p1(p1_),
    p2(p2_),
    color(color_)
  {}

  virtual RenderRequest::Type get_type() const override { return RenderRequest::LINE; }

public:
  const Vector p1;
  const Vector p2;
  const Color color;
};

class RectRenderRequest : public RenderRequest
{
public:
  RectRenderRequest(const int& layer_, const RectF& rect_,
                    const Color& color_) :
    RenderRequest(layer_),
    rect(rect_),
    color(color_)
  {}

  virtual RenderRequest::Type get_type() const override { return RenderRequest::RECT; }

public:
  const RectF rect;
  const Color color;
};

class FillRectRenderRequest final : public RectRenderRequest
{
public:
  using RectRenderRequest::RectRenderRequest;

  RenderRequest::Type get_type() const override { return RenderRequest::FILL_RECT; }
};
