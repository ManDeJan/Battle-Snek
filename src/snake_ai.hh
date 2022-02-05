#pragma once
#include "common.hh"
#include "game.hh"

namespace snake_ai {

void start_game(const Turn& turn);
void end_game(const Turn& turn);
Move move(const Turn& turn);

} // namespace snake_ai
