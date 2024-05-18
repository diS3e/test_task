//
// Created by dis3e on 18.05.24.
//

#ifndef TEST_TASK_EVENTREADER_H
#define TEST_TASK_EVENTREADER_H

#include <memory>
#include "fstream"
#include "events/event.h"
#include "events/userEvent.h"
#include "events/userTableEvent.h"
#include "events/errorEvent.h"

class eventReader {

private:
    std::ifstream& in;
public:
    explicit eventReader(std::ifstream & istream);
    bool hasEvent();
    std::shared_ptr<event> getNextEvent();

    static Time parseTime(const std::string& time) {
        std::tm tm = {};
        strptime(time.c_str(), "%H:%M", &tm);
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }

};
#endif //TEST_TASK_EVENTREADER_H
