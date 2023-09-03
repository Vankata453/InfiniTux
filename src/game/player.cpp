#include "game/player.hpp"

#include <iostream>

Player::Player() :
  SpritedObject("../data/images/creatures/tux/tux.png")
{
  // Set the default position.
  m_bbox.set_pos(Vector(100.f, 240.f));
}



void
Player::update(const float& elapsed_sec)
{
}

void
Player::process_control(const SDL_KeyboardEvent& key)
{
  // TEMPORARY: Player movement for testing
  Vector pos = m_bbox.get_pos();
  switch (key.keysym.sym)
  {
    case SDLK_LEFT:
      pos.x -= 10.f;
      break;
    case SDLK_RIGHT:
      pos.x += 10.f;
      break;
    case SDLK_UP:
      pos.y -= 10.f;
      break;
    case SDLK_DOWN:
      pos.y += 10.f;
      break;
  }
  m_bbox.set_pos(pos);
}


void
Player::collision(CollisionObject* obj, const CollisionHit& hit)
{
  std::cout << hit.left << " " << hit.right << " " << hit.top <<" " << hit.bottom << std::endl;
}
