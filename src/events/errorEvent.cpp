//
// Created by dis3e on 18.05.24.
//

#include "../../include/events/errorEvent.h"

errorEvent::errorEvent(Time timePoint, eventID eventId, const char *message)
        : event(timePoint, eventId), errorMessage(message) {

}
