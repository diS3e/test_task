//
// Created by dis3e on 18.05.24.
//

#ifndef TEST_TASK_USERTABLEEVENT_H
#define TEST_TASK_USERTABLEEVENT_H


#include <string>
#include "event.h"

class userTableEvent : public event {
public:
    const std::string userName;
    unsigned int tableID;
    explicit userTableEvent(Time timePoint, eventID eventId, std::string  userName, unsigned int tableId);
};


#endif //TEST_TASK_USERTABLEEVENT_H
