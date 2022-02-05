#pragma once

#include "common.hh"
#include "crow/json.h"
#include "game.hh"

// deserializing crow json objects to game objects
Turn deserialize_turn(const crow::json::rvalue &turn_json);
Game deserialize_game(const crow::json::rvalue &game_json);
Board deserialize_board(const crow::json::rvalue &board_json);
Snake deserialize_snake(const crow::json::rvalue &snake_json);
Point deserialize_point(const crow::json::rvalue &point_json);
Ruleset deserialize_ruleset(const crow::json::rvalue &ruleset_json);
Settings deserialize_settings(const crow::json::rvalue &settings_json);
Customizations deserialize_customizations(const crow::json::rvalue &customizations_json);

// serialize game objects to crow json objects
crow::json::wvalue serialize_move(const Move &move);
crow::json::wvalue serialize_customizations(const Customizations &customizations);
