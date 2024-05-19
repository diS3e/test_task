//
// Created by dis3e on 19.05.24.
//

#ifndef TEST_TASK_RUNNER_H
#define TEST_TASK_RUNNER_H


#include <ostream>

class Runner {
private:
    std::istream& in;
    std::ostream& cout;

    int readNumber(std::string& line);
public:
    Runner(std::istream& in, std::ostream& out);

    int runTask();
};


#endif //TEST_TASK_RUNNER_H
