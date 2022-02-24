#include <fmt/core.h>

#include "crow.h"
#include "crow/logging.h"

#include "game.hh"
#include "serialization.hh"
#include "snake_ai.hh"

int main(int argc, char *argv[]) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]{
        // check https://docs.battlesnake.com/references/personalization for more info
        return serialize_customizations({
            .apiversion = "1",
            .author = "ManDeJan",
            .color = "#ff2169",
            .head = "caffeine",
            .tail = "freckled",
            .version = "0.0.1 Snek"
        });
    });

    CROW_ROUTE(app, "/start")
        .methods("POST"_method)
    ([](const crow::request &req){
        try {
            auto turn = deserialize_turn(crow::json::load(req.body));
            snake_ai::start_game(turn);
            return crow::status::OK;
        } catch (const std::exception& e) {
            CROW_LOG_ERROR << fmt::format("Exception during deserialization:\n{}\nBody:\n{}\n", e.what(), req.body);
            return crow::status::BAD_REQUEST;
        }
    });

    CROW_ROUTE(app, "/end")
        .methods("POST"_method)
    ([](const crow::request &req){
        try {
            auto turn = deserialize_turn(crow::json::load(req.body));
            snake_ai::end_game(turn);
            return crow::status::OK;
        } catch (const std::exception &e) {
            CROW_LOG_ERROR << fmt::format("Exception during deserialization:\n{}\nBody:{}\n", e.what(), req.body);
            return crow::status::BAD_REQUEST;
        }
    });

    CROW_ROUTE(app, "/move")
        .methods("POST"_method)
    ([](const crow::request& req){
        try {
            CROW_LOG_INFO << fmt::format("Game ID: {}", crow::json::load(req.body)["game"]["id"].s());
            auto turn = deserialize_turn(crow::json::load(req.body));
            const auto move_json = serialize_move(snake_ai::move(turn));
            // CROW_LOG_INFO << fmt::format("Request body: {}", move_json.dump());
            return crow::response(move_json.dump());
        } catch (const std::exception &e) {
            CROW_LOG_ERROR << fmt::format("Exception during deserialization:\n{}\nBody:{}\n", e.what(), req.body);
            return crow::response(crow::status::BAD_REQUEST);
        }
    });

    CROW_LOG_INFO << fmt::format("Battle Snek ready for action!\n\n");
    u16 port = 3000;
    // if port in argv use that
    if (argc > 1) {
        port = std::stoi(argv[1]);
    }
    app.bindaddr("127.0.0.1").port(port).run();
}
