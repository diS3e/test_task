#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/eventReader.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "No file!";
        return 1;
    }
    const char* fileName = argv[1];

    std::ifstream in(fileName);
    if (!in.is_open()) {
        return 1;
    }

    eventReader e(in);
    int tableNum, cost;
    Time start, end;
    std::string startEndTime;

    in >> tableNum;
    std::getline(in, startEndTime);

    std::getline(in, startEndTime);
    std::istringstream iss(startEndTime);
    std::string startString, endString;
    iss >> startString >> endString;
    start = eventReader::parseTime(startString), end = eventReader::parseTime(endString);



    in >> cost;
    std::getline(in, startEndTime);
    std::cout << "Tables: " << tableNum << "\n";
    std::cout << "Cost: " << cost << "\n";
    while (e.hasEvent()) {
        std::shared_ptr<event> t = e.getNextEvent();
        switch (t->eventId) {
            case eventID::COME:
            case eventID::CLOSE_LEAVE:
            case eventID::LEAVE:
            case eventID::WAIT: {
                auto *c = dynamic_cast<userEvent*>(t.get());
                std::cout << "Come: " << c->userName << "\n";
                break;
            }
            case eventID::FREE_SIT:
            case eventID::SIT: {
                auto *c = dynamic_cast<userTableEvent *>(t.get());
                std::cout << "Visitor " << c->userName << " sit down at table " << c->tableID << ".\n";
                break;
            }
            case eventID::ERROR: {
                auto *c = dynamic_cast<errorEvent *>(t.get());
                std::cout << "Error: " << c->errorMessage << "\n";
                break;
            }
        }
    }
    in.close();
    return 0;
}
