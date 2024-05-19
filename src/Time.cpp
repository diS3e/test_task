//
// Created by dis3e on 19.05.24.
//

#include "../include/Time.h"
#include "exception"
#include <sstream>

Time::Time(unsigned int hour, unsigned int minute) {
    if (0 <= hour && hour < 24 && 0 <= minute && minute < 60) {
        this->hour = hour;
        this->minute = minute;
    } else {
        throw std::exception();
    }
}

int operator-(const Time &a, const Time &b) {
    return a.toInt() - b.toInt();
}

int Time::toInt() const {
    return hour * 60 + minute;
}

std::string to_string(const Time &a) {
    auto hours = ((a.hour < 10) ? "0" : "") + std::to_string(a.hour);
    auto minutes = ((a.minute < 10) ? "0" : "") + std::to_string(a.minute);
    return hours + ":" + minutes;
}

bool operator==(const Time &a, const Time &b) {
    return a.hour == b.hour && a.minute == b.minute;
}

bool operator!=(const Time &a, const Time &b) {
    return !(a == b);
}

bool operator<(const Time &a, const Time &b) {
    return a.hour < b.hour || (a. hour == b.hour && a.minute < b.minute);
}

bool operator>(const Time &a, const Time &b) {
    return !(a <= b);
}

bool operator<=(const Time &a, const Time &b) {
    return (a < b) || a == b;
}

bool operator>=(const Time &a, const Time &b) {
    return !(a < b);
}

std::ostream& operator<<(std::ostream& s, Time const& a) {
    return s << to_string(a);
}