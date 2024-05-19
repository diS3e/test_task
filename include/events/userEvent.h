//
// Created by dis3e on 18.05.24.
//

#ifndef TEST_TASK_USEREVENT_H
#define TEST_TASK_USEREVENT_H

#include <string>
#include "event.h"

class userEvent : public event{
public:
    std::string userName;

    explicit userEvent(Time timePoint, eventID eventId, std::string userName);

    ~userEvent() override = default;

};


#endif //TEST_TASK_USEREVENT_H
