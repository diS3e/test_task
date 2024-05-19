//
// Created by dis3e on 18.05.24.
//

#ifndef TEST_TASK_EVENTREADER_H
#define TEST_TASK_EVENTREADER_H

#include <memory>
#include <regex>
#include "fstream"
#include "events/event.h"
#include "events/userEvent.h"
#include "events/userTableEvent.h"
#include "events/errorEvent.h"

class eventReader {

private:
    std::istream& in;
    Time lastEvent;
    static std::regex numRegExp;
    static std::regex timeRegExp;
    static std::regex commandRegExp;
public:
    explicit eventReader(std::istream & istream);
    bool hasEvent();
    std::shared_ptr<event> getNextEvent(std::stringstream & out, std::string& buffer);

    static Time parseTime(const std::string& time);

    static bool validateCommand(const std::string& command);

    static bool validateNumber(const std::string& number);

    static bool validateTime(const std::string& time);
};
#endif //TEST_TASK_EVENTREADER_H
