//
// Created by jens on 22/02/23.
//

#include "WebServer.h"

int main(int argc, char *argv[]) {
    WebServer ws = WebServer();
    ws.start();
    return 0;
}