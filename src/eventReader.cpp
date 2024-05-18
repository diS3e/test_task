//
// Created by dis3e on 18.05.24.
//

#include "../include/eventReader.h"
#include <sstream>
#include <string>
#include <iomanip>

eventReader::eventReader(std::ifstream &istream) : in(istream) {

}

bool eventReader::hasEvent() {
    return !in.eof();
}

std::shared_ptr<event> eventReader::getNextEvent() {
    std::string line;
    std::getline(in, line);
    std::istringstream iss(line);

    std::string timeString;
    int code;
    std::string clientName;

    iss >> timeString >> code >> clientName;

    Time time = parseTime(timeString);

    if (code == eventID::SIT) {
        unsigned int tableId;
        iss >> tableId;
//        auto* a = new userTableEvent();
        return std::make_shared<userTableEvent>(time, eventID::SIT, clientName, tableId);
    } else {
        return std::make_shared<userEvent>(time, eventID(code), clientName);
    }
}
