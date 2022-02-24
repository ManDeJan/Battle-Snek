#include "snake_ai.hh"
#include "fmt/core.h"
#include "game.hh"
#include <array>

namespace snake_ai {


Direction turn_right(Direction dir) {
    switch (dir) {
        case Direction::Up:    return Direction::Right;
        case Direction::Right: return Direction::Down;
        case Direction::Down:  return Direction::Left;
        case Direction::Left:  return Direction::Up;
    }
}

Direction turn_back(Direction dir) {
    return turn_right(turn_right(dir));
}

Direction turn_left(Direction dir) {
    return turn_right(turn_back(dir));
}

Direction get_current_direction(Snake snake) {
    if (snake.head.y == snake.body[1].y) {
        if (snake.head.x < snake.body[1].x) {
            return Direction::Left;
        } else {
            return Direction::Right;
        }
    } else {
        if (snake.head.y < snake.body[1].y) {
            return Direction::Down;
        } else {
            return Direction::Up;
        }
    }
}

void start_game(const Turn& turn) {
    fmt::print("Start game: {}\n", turn.game.id);
}

void end_game(const Turn& turn) {
    fmt::print("End game: {}\n", turn.game.id);
}

Move move(const Turn& turn) {
    fmt::print("Move: {}\n", turn.game.id);
    const auto current_direction = get_current_direction(turn.you);
    const auto directions = array{current_direction, turn_right(current_direction), turn_left(current_direction)};
    const auto random_direction = directions[rand() % directions.size()];

    return Move{.direction = random_direction,
                .shout = "omae wa mou shindeiru"};
}

} // namespace snake_ai
