//
// Created by dis3e on 19.05.24.
//

#ifndef TEST_TASK_TIME_H
#define TEST_TASK_TIME_H


#include <ostream>

class Time {
public:
    unsigned int hour = 0;
    unsigned int minute = 0;

    Time() : hour(0), minute(0) {}
    Time(Time const& other)  = default;
    Time& operator=(Time const& other) = default;
    Time(unsigned int hour, unsigned int minute);
    explicit Time(unsigned int minutes) : Time(minutes / 60, minutes % 60){

    }
    ~Time() = default;
    int toInt() const;
    friend std::string to_string(Time const& a);
    friend int operator-(Time const& a, Time const& b);

    friend bool operator==(Time const& a, Time const& b);
    friend bool operator!=(Time const& a, Time const& b);
    friend bool operator< (Time const& a, Time const& b);
    friend bool operator> (Time const& a, Time const& b);
    friend bool operator<=(Time const& a, Time const& b);
    friend bool operator>=(Time const& a, Time const& b);
};
std::ostream& operator<<(std::ostream& s, Time const& a);

#endif //TEST_TASK_TIME_H
