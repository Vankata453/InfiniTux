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

#include "math/rectf.hpp"

bool
RectF::overlaps(const RectF& other) const
{
  // Ensure there is horizontal overlap.
  if (get_left() >= other.get_right() || other.get_left() >= get_right())
    return false;
  // Ensure there is vertical overlap.
  if (get_top() >= other.get_bottom() || other.get_top() >= get_bottom())
    return false;

  return true;
}


std::ostream& operator<<(std::ostream& os, const RectF& rect)
{
  os << "RECT["
     << rect.get_left() << ", "
     << rect.get_top() << ", "
     << rect.get_width() << ", "
     << rect.get_height() << "]";
  return os;
}
