//
// Created by dis3e on 18.05.24.
//

#ifndef TEST_TASK_ERROREVENT_H
#define TEST_TASK_ERROREVENT_H
#include "event.h"

class errorEvent : public event {
public:
    const char* errorMessage;

    explicit errorEvent(Time timePoint, eventID eventId, const char *message);
};


#endif //TEST_TASK_ERROREVENT_H
