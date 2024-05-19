//
// Created by dis3e on 18.05.24.
//

#ifndef TEST_TASK_EVENT_H
#define TEST_TASK_EVENT_H

#include <chrono>
#include <ostream>
#include "eventID.h"
#include "../Time.h"
#include <memory>

class event {
public:
    Time timePoint;
    eventID eventId;
    event() = delete;
    event(Time timePoint, eventID eventId);


    virtual ~event() = default;
};


#endif //TEST_TASK_EVENT_H
