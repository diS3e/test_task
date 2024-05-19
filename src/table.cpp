//
// Created by dis3e on 19.05.24.
//

#include "../include/table.h"

table::table(unsigned int tableId)
    : id(tableId), startTime(0, 0){

}

bool table::isBusy() const {
    return _isBusy;
}

void table::startSession(const std::string &name, Time start) {
    _isBusy = true;
    userName = name;
    startTime = start;
}

void table::endSession(Time end) {
    _isBusy = false;
    int delta = end - startTime;
    payTime += (delta / 60) + (delta % 60 == 0 ? 0 : 1);
    workingTime += delta;
}

