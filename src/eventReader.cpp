//
// Created by dis3e on 18.05.24.
//

#include "../include/eventReader.h"
#include "../include/formatException.h"
#include <sstream>
#include <string>
#include <iomanip>

std::regex eventReader::numRegExp("[0-9]+");
std::regex eventReader::timeRegExp("[0-9]{2}:[0-9]{2} [0-9]{2}:[0-9]{2}");
std::regex eventReader::commandRegExp("[0-9]{2}:[0-9]{2} [0-9]{1,2} [a-z0-9_-]+( [0-9]+)?");

eventReader::eventReader(std::istream &istream) : in(istream), lastEvent(0, 0) {

}

bool eventReader::hasEvent() {
    return !in.eof();
}

std::shared_ptr<event> eventReader::getNextEvent(std::stringstream& out, std::string& buffer) {
    std::string timeString;
    int code;
    std::string clientName;


    std::getline(in, buffer);
    if (!eventReader::validateCommand(buffer)) throw formatException();
    std::stringstream ss(buffer);
    ss >> timeString >> code >> clientName;

    out << timeString << " " << code << " " << clientName;

    Time time = parseTime(timeString);
    if (time < lastEvent) {
        throw formatException();
    } else {
        lastEvent = time;
    }
    if (code == eventID::SIT) {
        unsigned int tableId;
        ss >> tableId;
        out << " " << tableId << "\n";
        return std::make_shared<userTableEvent>(time, eventID::SIT, clientName, tableId);
    } else {
        out << "\n";
        return std::make_shared<userEvent>(time, eventID(code), clientName);
    }
}

Time eventReader::parseTime(const std::string &time) {
    return {static_cast<unsigned int>(std::stoi(time)), static_cast<unsigned int>(std::stoi(time.c_str() + 3))};
}

bool eventReader::validateCommand(const std::string &command) {
    return std::regex_match(command, commandRegExp);
}

bool eventReader::validateNumber(const std::string &number) {
    return std::regex_match(number, numRegExp);
}

bool eventReader::validateTime(const std::string &time) {
    return std::regex_match(time, timeRegExp);
}
