cmake_minimum_required(VERSION 3.26)
project(test_task)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_Populate(googletest)

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
        include/events/errorEvent.h
        src/client.cpp
        include/client.h
        src/computerClub.cpp
        include/computerClub.h
        src/table.cpp
        include/table.h
        include/clientState.h
        src/Time.cpp
        include/Time.h
        src/formatException.cpp
        include/formatException.h
        src/Runner.cpp
        include/Runner.h
)

add_executable(testing
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
        include/events/errorEvent.h
        src/client.cpp
        include/client.h
        src/computerClub.cpp
        include/computerClub.h
        src/table.cpp
        include/table.h
        include/clientState.h
        src/Time.cpp
        include/Time.h
        tests/testInputValidation.cpp
        tests/testCorrectness.cpp
        src/Runner.cpp
        include/Runner.h
        tests/test.cpp

)
target_link_libraries(testing gtest_main)

add_subdirectory(${CMAKE_BINARY_DIR}/_deps/googletest-src
        ${CMAKE_BINARY_DIR}/_deps/googletest-build)
