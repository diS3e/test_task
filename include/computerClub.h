//
// Created by dis3e on 19.05.24.
//

#ifndef TEST_TASK_COMPUTERCLUB_H
#define TEST_TASK_COMPUTERCLUB_H


#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include "table.h"
#include "client.h"
#include "events/event.h"
#include "events/errorEvent.h"
#include "events/userEvent.h"
#include "events/userTableEvent.h"

class computerClub {
private:
    int numTables;
    int freeTables;
    Time start, end;
    std::vector<client> clients;
    std::deque<client> queue;
    unsigned int tableCost;
    table* tables;

    bool inWorkingTime (Time time);

    std::vector<client>::iterator findClientIteratorByName(const std::string& clientName);

    table* findClientTableByName(const std::string& clientName);

    std::shared_ptr<event> clientLeave(const std::vector<client>::const_iterator& iterator, std::shared_ptr<event> const & inEvent);

    std::shared_ptr<event> clientWait(std::vector<client>::iterator& iterator, std::shared_ptr<event> const & inEvent);

public:
    computerClub(int numTables, Time start, Time end, int tableCost);

    ~computerClub();

    std::shared_ptr<event> doEvent(std::shared_ptr<event> const & inEvent);

    void finishDay(std::ostream& out);

    void countTablesIncome(std::ostream& out);
};


#endif //TEST_TASK_COMPUTERCLUB_H
