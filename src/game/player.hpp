#pragma once

#include "game/sprited_object.hpp"

class Player final : public SpritedObject
{
public:
  Player();

  void update(const float& elapsed_sec) override;

  /** Process a keyboard event.
      TODO: Process a custom control, derived by the pressed key. */
  void process_control(const SDL_KeyboardEvent& key);

  void collision(CollisionObject* obj, const CollisionHit& hit) override;

private:
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
};
