#include "snake_ai.hh"
#include "fmt/core.h"
#include "game.hh"

namespace snake_ai {

void start_game(const Turn& turn) {
    fmt::print("Start game: {}\n", turn.game.id);
}

void end_game(const Turn& turn) {
    fmt::print("End game: {}\n", turn.game.id);
}

Move move(const Turn& turn) {
    fmt::print("Move: {}\n", turn.game.id);
    return Move{.direction = Direction::Up,
                .shout = "omae wa mou shindeiru"};
}

} // namespace snake_ai
