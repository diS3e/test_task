//
// Created by dis3e on 19.05.24.
//

#include "../include/computerClub.h"

computerClub::computerClub(int numTables, Time start, Time end, int tableCost)
    : numTables(numTables), freeTables(numTables), start(start), end(end), clients(), queue() , tableCost(tableCost){
    tables = static_cast<table*>(operator new(numTables * sizeof(table)));
    for (int i = 0; i < numTables; ++i) {
        new (tables + i) table(i + 1);
    }
}

bool computerClub::inWorkingTime(Time time) {
    return start <= time && time < end;
}

std::vector<client>::iterator computerClub::findClientIteratorByName(const std::string &clientName) {
    return std::find_if(clients.begin(), clients.end(),
                        [&clientName](client& cl) { return cl.name == clientName; });

}

table *computerClub::findClientTableByName(const std::string &clientName) {
    return std::find_if(tables, tables + numTables,
                        [&clientName](table& cl) { return cl.userName == clientName; });
}

std::shared_ptr<event>
computerClub::clientLeave(const std::vector<client>::const_iterator &iterator, const std::shared_ptr<event> &inEvent) {
    client c = *iterator;
    if (c.state == clientState::IN_QUEUE) {
        auto p = std::find_if(queue.begin(), queue.end(), [&c](client& client){return c.name == client.name;});
        if (p != queue.end()) queue.erase(p, p + 1);
    }
    int i = -1;
    for (; i < numTables; ++i) {
        if (tables[i].isBusy() && tables[i].userName == c.name) {
            tables[i].endSession(inEvent->timePoint);
            freeTables++;
            break;
        }
    }

    clients.erase(iterator, iterator + 1);

    if (i != -1 && !queue.empty()) {
        freeTables--;
        client newUser = queue.front();
        queue.pop_front();
        tables[i].startSession(newUser.name, inEvent->timePoint);
        return std::make_shared<userTableEvent>(inEvent->timePoint, eventID::FREE_SIT, newUser.name, i + 1);
    }
    return inEvent;
}

std::shared_ptr<event>
computerClub::clientWait(std::vector<client>::iterator &iterator, const std::shared_ptr<event> &inEvent) {
    iterator->state = clientState::IN_QUEUE;
    client c = *iterator;

    if (queue.size() > numTables) {
        clients.erase(iterator, iterator + 1);
        return std::make_shared<userEvent>(inEvent->timePoint, eventID::FORCED_LEAVE, c.name);
    } else {
        queue.push_back(c);
        return inEvent;
    }
}

std::shared_ptr<event> computerClub::doEvent(const std::shared_ptr<event> &inEvent) {
    switch (inEvent->eventId) {
        case eventID::COME:{
            auto *pUserEvent = dynamic_cast<userEvent*>(inEvent.get());
            if (!inWorkingTime(pUserEvent->timePoint)) {
                return std::make_shared<errorEvent>(pUserEvent->timePoint, eventID::ERROR, "NotOpenYet");
            }
            if (findClientIteratorByName(pUserEvent->userName) != clients.end()) {
                return std::make_shared<errorEvent>(pUserEvent->timePoint, eventID::ERROR, "YouShallNotPass");
            }
            clients.emplace_back(pUserEvent->userName, clientState::IN_CLUB);
            return inEvent;
        }
        case eventID::LEAVE: {
            auto *pUserEvent = dynamic_cast<userEvent *>(inEvent.get());
            auto clientPlace = findClientIteratorByName(pUserEvent->userName);
            if (clientPlace == clients.end()) {
                return std::make_shared<errorEvent>(pUserEvent->timePoint, eventID::ERROR, "ClientUnknown");
            }
            return clientLeave(clientPlace, inEvent);
        }
        case eventID::WAIT: {
            auto *pUserEvent = dynamic_cast<userEvent *>(inEvent.get());
            auto clientPlace = findClientIteratorByName(pUserEvent->userName);
            if (clientPlace == clients.end()) {
                return std::make_shared<errorEvent>(pUserEvent->timePoint, eventID::ERROR, "ClientUnknown");
            }
            if (freeTables != 0) {
                return std::make_shared<errorEvent>(pUserEvent->timePoint, eventID::ERROR, "ICanWaitNoLonger!");
            }
            return clientWait(clientPlace, inEvent);
        }
        case eventID::SIT: {
            auto *pUserTableEvent = dynamic_cast<userTableEvent *>(inEvent.get());
            auto clientPlace = findClientIteratorByName(pUserTableEvent->userName);
            auto pClientTable = findClientTableByName(pUserTableEvent->userName);
            if (clientPlace == clients.end()) {
                return std::make_shared<errorEvent>(pUserTableEvent->timePoint, eventID::ERROR, "ClientUnknown");
            }

            unsigned int table = pUserTableEvent->tableID - 1;
            if (tables[table].isBusy()) {
                return std::make_shared<errorEvent>(pUserTableEvent->timePoint, eventID::ERROR, "PlaceIsBusy");
            }
            tables[table].startSession(pUserTableEvent->userName, pUserTableEvent->timePoint);
            freeTables--;
            clientPlace->state = clientState::AT_TABLE;
            if (pClientTable != (tables + numTables)) {
                pClientTable->endSession(pUserTableEvent->timePoint);
                freeTables++;
            }
            return inEvent;
        }
        default: {
            throw std::runtime_error("Incorrect input event!");
        }
    }
}

void computerClub::finishDay(std::ostream &out) {
    std::vector<std::string> names;
    for (int i = 0; i < numTables; ++i) {
        if (tables[i].isBusy()) {
            names.push_back(tables[i].userName);
            tables[i].endSession(end);
        }
    }
    freeTables = numTables;

    std::sort(clients.begin(), clients.end(), [](client& a, client& b) { return a.name < b.name;} );
    for (auto &t : clients) {
        out << end << " " << eventID::FORCED_LEAVE <<  " " << t.name << "\n";
    }
}

void computerClub::countTablesIncome(std::ostream &out) {
    for (int i = 0; i < numTables; ++i) {
        unsigned int workingTime = tables[i].workingTime;
        unsigned int payHours = tables[i].payTime;
        out << i + 1 << " " << payHours * tableCost << " " << Time(workingTime) << "\n";
    }
}

computerClub::~computerClub() {
    delete tables;
}
