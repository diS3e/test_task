//
// Created by dis3e on 19.05.24.
//

#ifndef TEST_TASK_TABLE_H
#define TEST_TASK_TABLE_H


#include <iostream>
#include "Time.h"

class table {
private:
    bool _isBusy = false;
    Time startTime;
public:
    unsigned workingTime = 0;
    unsigned payTime = 0;
    std::string userName;
    const unsigned int id;

    explicit table(unsigned  int tableId);

    bool isBusy() const;

    void startSession(const std::string& name, Time start);

    void endSession(Time end);
};


#endif //TEST_TASK_TABLE_H
