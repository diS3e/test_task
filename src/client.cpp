//
// Created by dis3e on 19.05.24.
//

#include <utility>

#include "../include/client.h"

client::client(std::string name, clientState clientState) :
    name(std::move(name)), state(clientState){
}
