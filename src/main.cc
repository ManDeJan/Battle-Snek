#include <fmt/core.h>
#include "crow.h"
#include "crow/logging.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]{
        return crow::json::wvalue{{{"apiversion", "1"},
                                   {"author", "ManDeJan"},
                                   {"color", "#ff2169"},
                                   {"head", "default"},
                                   {"tail", "default"}}};
    });

    CROW_ROUTE(app, "/start")
        .methods("POST"_method)
    ([](const crow::request& req){
        auto data = crow::json::load(req.body);
        if (!data) return crow::response(crow::status::BAD_REQUEST);
        CROW_LOG_INFO << fmt::format("Start game: {}", data["game"]["id"].i());
        return crow::response("ok");
    });

    CROW_ROUTE(app, "/end")
        .methods("POST"_method)
    ([](const crow::request& req){
        auto data = crow::json::load(req.body);
        if (!data) return crow::response(crow::status::BAD_REQUEST);

        CROW_LOG_INFO << fmt::format("End game: {}", data["game"]["id"].i());
        return crow::response("ok");
    });

    CROW_ROUTE(app, "/move")
        .methods("POST"_method)
    ([](const crow::request& req){
        auto data = crow::json::load(req.body);
        if (!data) return crow::response(crow::status::BAD_REQUEST);

        CROW_LOG_INFO << fmt::format("Move: {}", data["game"]["id"].i());
        return crow::response(crow::json::wvalue{{{"move", "up"},
                                                  {"shout", "omae wa mou shindeiru"}}});
    });

    CROW_LOG_INFO << fmt::format("Battle Snek ready for action!\n\n");
    app.port(31337).run();
}
