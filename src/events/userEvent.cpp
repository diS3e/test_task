//
// Created by dis3e on 18.05.24.
//

#include <utility>

#include "../../include/events/userEvent.h"

userEvent::userEvent(Time timePoint, eventID eventId, std::string   userName) :
        event(timePoint, eventId), userName(std::move(userName)) {
}
