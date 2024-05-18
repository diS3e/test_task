//
// Created by dis3e on 18.05.24.
//

#include <utility>

#include "../../include/events/userTableEvent.h"

userTableEvent::userTableEvent(Time timePoint, eventID eventId, std::string  userName, unsigned int tableId) :
        event(timePoint, eventId), userName(std::move(userName)), tableID(tableId){

}
