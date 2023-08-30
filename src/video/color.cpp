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

#include "video/color.hpp"

std::ostream& operator<<(std::ostream& os, const Color& color)
{
  os << "COLOR["
     << static_cast<int>(color.r) << ", "
     << static_cast<int>(color.g) << ", "
     << static_cast<int>(color.b) << ", "
     << static_cast<int>(color.a) << "]";
  return os;
}
