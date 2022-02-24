#include <fmt/core.h>
#include "serialization.hh"
#include "crow/json.h"
#include "game.hh"

Turn deserialize_turn(const crow::json::rvalue& turn_json) {
    Turn turn;
    turn.game = deserialize_game(turn_json["game"]);
    turn.turn = turn_json["turn"].u();
    turn.board = deserialize_board(turn_json["board"]);
    turn.you = deserialize_snake(turn_json["you"]);
    return turn;
}

Game deserialize_game(const crow::json::rvalue& game_json) {
    Game game;
    game.id = game_json["id"].s();
    game.ruleset = deserialize_ruleset(game_json["ruleset"]);
    game.timeout = game_json["timeout"].i();
    game.source = game_json["source"].s();
    return game;
}

Board deserialize_board(const crow::json::rvalue& board_json) {
    Board board;
    board.width = board_json["width"].i();
    board.height = board_json["height"].i();
    for (const auto& food_json : board_json["food"]) {
        board.food.push_back(deserialize_point(food_json));
    }
    for (const auto& snake_json : board_json["snakes"]) {
        board.snakes.push_back(deserialize_snake(snake_json));
    }
    for (const auto& hazard_json : board_json["hazards"]) {
        board.hazards.push_back(deserialize_point(hazard_json));
    }
    return board;
}

Snake deserialize_snake(const crow::json::rvalue& snake_json) {
    Snake snake;

    snake.id = snake_json["id"].s();
    snake.name = snake_json["name"].s();
    snake.latency = snake_json["latency"].s();
    snake.health = snake_json["health"].i();
    for (const auto& body_json : snake_json["body"]) {
        snake.body.push_back(deserialize_point(body_json));
    }
    snake.head = deserialize_point(snake_json["head"]);
    snake.length = snake_json["length"].u();
    snake.shout = snake_json["shout"].s();
    snake.squad = snake_json["squad"].s();
    snake.customizations = deserialize_customizations(snake_json["customizations"]);
    return snake;
}

Point deserialize_point(const crow::json::rvalue& point_json) {
    Point point;
    point.x = point_json["x"].i();
    point.y = point_json["y"].i();
    return point;
}

Ruleset deserialize_ruleset(const crow::json::rvalue& ruleset_json) {
    Ruleset ruleset;
    ruleset.name = ruleset_json["name"].s();
    ruleset.version = ruleset_json["version"].s();
    ruleset.settings = deserialize_settings(ruleset_json["settings"]);
    return ruleset;
}

Settings deserialize_settings(const crow::json::rvalue &settings_json) {
    Settings settings;
    settings.foodSpawnChance = settings_json["foodSpawnChance"].i();
    settings.minimumFood = settings_json["minimumFood"].i();
    settings.hazardDamagePerTurn = settings_json["hazardDamagePerTurn"].i();
    // FIXME: MAP parameter is not send by battlesnake server
    settings.royale = SettingsRoyale{settings_json["royale"]["shrinkEveryNTurns"].u()};
    settings.squad = SettingsSquad{
        settings_json["squad"]["allowBodyCollisions"].b(),
        settings_json["squad"]["sharedElimination"].b(),
        settings_json["squad"]["sharedHealth"].b(),
        settings_json["squad"]["sharedLength"].b()
    };
    return settings;
}

Customizations deserialize_customizations(const crow::json::rvalue& customizations_json) {
    Customizations customizations;
    // Note lines commented out are not send by battlesnake server
    // customizations.apiversion = customizations_json["apiversion"].s();
    // customizations.author = customizations_json["author"].s();
    customizations.color = customizations_json["color"].s();
    customizations.head = customizations_json["head"].s();
    customizations.tail = customizations_json["tail"].s();
    // customizations.version = customizations_json["version"].s();
    return customizations;
}

crow::json::wvalue serialize_move(const Move &move) {
    crow::json::wvalue move_json;
    move_json["move"] = array{"up", "right", "down", "left"}[static_cast<u8>(move.direction)];
    move_json["shout"] = move.shout;
    return move_json;
}

crow::json::wvalue serialize_customizations(const Customizations &customizations) {
    crow::json::wvalue customizations_json;
    customizations_json["apiversion"] = customizations.apiversion;
    customizations_json["author"] = customizations.author;
    customizations_json["color"] = customizations.color;
    customizations_json["head"] = customizations.head;
    customizations_json["tail"] = customizations.tail;
    customizations_json["version"] = customizations.version;
    return customizations_json;
}
