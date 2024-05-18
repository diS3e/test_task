cmake_minimum_required(VERSION 3.26)
project(test_task)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_task src/main.cpp
        src/eventReader.cpp
        include/eventReader.h
        src/events/event.cpp
        include/events/event.h
        include/events/eventID.h
        src/events/userEvent.cpp
        include/events/userEvent.h
        src/events/userTableEvent.cpp
        include/events/userTableEvent.h
        src/events/errorEvent.cpp
        include/events/errorEvent.h)
