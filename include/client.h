//
// Created by dis3e on 19.05.24.
//

#ifndef TEST_TASK_CLIENT_H
#define TEST_TASK_CLIENT_H


#include "clientState.h"
#include <string>

class client {

public:
    clientState state;
    std::string name;

    client(std::string name, clientState clientState);
};


#endif //TEST_TASK_CLIENT_H
