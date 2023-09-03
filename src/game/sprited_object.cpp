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

#include "game/sprited_object.hpp"

#include "video/texture_manager.hpp"

SpritedObject::SpritedObject(const std::string& sprite_file) :
  m_sprite(TextureManager::current()->load(sprite_file.c_str()))
{
  // Set bounding box size to sprite size.
  m_bbox.set_size(m_sprite.get_size());
}


void
SpritedObject::draw(Renderer& renderer)
{
  /** TODO: Support for sprites, containing multiple textures. */
  renderer.draw_texture(m_sprite, m_bbox.get_pos(), LAYER_OBJECTS);
}
