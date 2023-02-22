//
// Created by jens on 22/02/23.
//

#include "WebServer.h"

WebServer::WebServer(int port): port(port) {

}

void WebServer::start() {
    crow::SimpleApp app;
    crow::mustache::set_base(".");

    CROW_ROUTE(app, "/")([]() {
        crow::mustache::context ctx;
        std::ifstream t("website/index1.html");
        std::string indexPage((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        return indexPage;
    });
    app.port(this->port).multithreaded().run();
}