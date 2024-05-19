//
// Created by dis3e on 19.05.24.
//

#include "../include/Runner.h"
#include "../include/formatException.h"
#include "../include/eventReader.h"
#include "../include/computerClub.h"

int Runner::readNumber(std::string& line) {
    std::getline(in, line);
    if (!eventReader::validateNumber(line)) throw formatException();
    return std::stoi(line);
}

int Runner::runTask() {
    std::stringstream out;
    std::string line;
    unsigned int lineNumber = 1;
    try {
        int tableNum, cost;
        Time start, end;


        tableNum = readNumber(line);

        std::string startString, endString;
        lineNumber++;
        std::getline(in, line);
        if (!eventReader::validateTime(line)) throw formatException();
        std::stringstream iss(line);
        iss >> startString >> endString;
        start = eventReader::parseTime(startString), end = eventReader::parseTime(endString);

        lineNumber++;
        cost = readNumber(line);

        out << start << "\n";
        eventReader e(in);

        computerClub club(tableNum, start, end, cost);

        while (e.hasEvent()) {
            lineNumber++;
            auto event = e.getNextEvent(out, line);
            auto answer = club.doEvent(event);
            if (answer != event) {
                out << answer->timePoint << " " << answer->eventId << " ";
                switch (answer->eventId) {
                    case eventID::FORCED_LEAVE: {
                        auto *c = dynamic_cast<userEvent*>(answer.get());
                        out << c->userName << "\n";
                        break;
                    }
                    case eventID::FREE_SIT: {
                        auto *c = dynamic_cast<userTableEvent*>(answer.get());
                        out << c->userName << " " << c->tableID << "\n";
                        break;
                    }
                    case eventID::ERROR: {
                        auto *c = dynamic_cast<errorEvent*>(answer.get());
                        out << c->errorMessage << "\n";
                        break;
                    }
                    default: {
                        throw std::runtime_error("Unexpected generated event id");
                    }
                }
            }
        }

        cout << out.str();
        club.finishDay(cout);
        cout << end << "\n";
        club.countTablesIncome(cout);
    } catch (const formatException &a) {
        std::cerr << "Incorrect format in line " << lineNumber << ":\n\t\"" << line << "\"\n";
        return 1;
    }
    return 0;
}

Runner::Runner(std::istream &in, std::ostream &out)
    : in(in), cout(out) {

}
