//
// Created by dis3e on 19.05.24.
//

#include <gtest/gtest.h>
#include "../include/Runner.h"

void testCorrectness(const std::pair<std::string, std::string>& testAnswer) {
    std::istringstream in(testAnswer.first);
    std::stringstream out;
    Runner runner(in, out);
    int exitCode = runner.runTask();
    ASSERT_EQ(exitCode, 0);
    ASSERT_EQ(out.str(), testAnswer.second);
}

TEST(Correctness, EmptyDay) {
    testCorrectness({
                            R"(1
09:00 20:00
239239)",
                            R"(09:00
20:00
1 0 00:00
)"
                    });
}

TEST(Correctness, GeneratedEvents) {
    testCorrectness({
R"(2
09:00 20:00
2
08:48 1 a
09:10 1 a
09:11 1 a
09:12 2 a 1
09:13 2 a 1
09:13 2 a 2
09:13 2 b 1
09:14 1 b
09:15 3 b
09:30 4 c)",
R"(09:00
08:48 1 a
08:48 13 NotOpenYet
09:10 1 a
09:11 1 a
09:11 13 YouShallNotPass
09:12 2 a 1
09:13 2 a 1
09:13 13 PlaceIsBusy
09:13 2 a 2
09:13 2 b 1
09:13 13 ClientUnknown
09:14 1 b
09:15 3 b
09:15 13 ICanWaitNoLonger!
09:30 4 c
09:30 13 ClientUnknown
20:00 11 a
20:00 11 b
20:00
1 2 00:01
2 22 10:47
)"
                    });
}

TEST(Correctness, GoOutFromQueue) {
    testCorrectness({
        R"(1
09:00 20:00
2
09:10 1 a
09:12 2 a 1
09:14 1 b
09:20 3 b
09:25 4 b
09:30 4 a)",R"(09:00
09:10 1 a
09:12 2 a 1
09:14 1 b
09:20 3 b
09:25 4 b
09:30 4 a
20:00
1 2 00:18
)"});
}


TEST(Correctness, Example) {
    testCorrectness({
R"(3
09:00 19:00
10
08:48 1 client1
09:41 1 client1
09:48 1 client2
09:52 3 client1
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:45 3 client4
12:33 4 client1
12:43 4 client2
15:52 4 client4)",
R"(09:00
08:48 1 client1
08:48 13 NotOpenYet
09:41 1 client1
09:48 1 client2
09:52 3 client1
09:52 13 ICanWaitNoLonger!
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:35 13 PlaceIsBusy
11:45 3 client4
12:33 4 client1
12:33 12 client4 1
12:43 4 client2
15:52 4 client4
19:00 11 client3
19:00
1 70 05:58
2 30 02:18
3 90 08:01
)"});
}