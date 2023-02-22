//
// Created by jens on 22/02/23.
//

#ifndef MATRIXCALC_WEBSERVER_H
#define MATRIXCALC_WEBSERVER_H

#include "crow.h"
#include <fstream>

class WebServer {
    int port;
public:
    WebServer(int port = 18080);
    void start();
};


#endif //MATRIXCALC_WEBSERVER_H
