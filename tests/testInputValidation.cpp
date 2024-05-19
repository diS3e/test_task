//
// Created by dis3e on 19.05.24.
//

#include <gtest/gtest.h>
#include "../include/Runner.h"

void testValidation(const std::string& testAnswer) {
    std::istringstream in(testAnswer);
    std::stringstream out;
    Runner runner(in, out);
    int exit_code = runner.runTask();
    ASSERT_EQ(exit_code, 1);
}

TEST(InputValidation, Number) {
    testValidation(R"(-123
00:00 19:00
2)");
    testValidation(R"(12a3
00:00 19:00
2)");
    testValidation(R"(123
00:00 19:00
-2)");
    testValidation(R"(0
00:00 19:00
abvg)");
    testValidation(R"(3
00:00 19:00
+2)");
    testValidation(R"(123
00:00 19:00
)");

}


TEST(InputValidation, Time) {
    testValidation(R"(123
00:00 19:0
12)");
    testValidation(R"(123
00:0 19:00
12)");
    testValidation(R"(123
123:00 19:00
12)");
    testValidation(R"(123
0-0:00 19:00
12)");
    testValidation(R"(123
00.00 19:00
12)");
    testValidation(R"(123
00.00 19:00
12)");
    testValidation(R"(123
09.00 19:00
12
08:1 1 a)");
}

TEST(InputValidation, Spaces) {
    testValidation(R"(123
00:00 19: 00
12)");
    testValidation(R"(123
00:00   19:00
12)");
    testValidation(R"(  123
00:00 19:00
12)");
    testValidation(R"(123
  00:00 19:00
12)");
    testValidation(R"(123
00:00 19:00
12
08:10   1 a)");
    testValidation(R"(123
00:00 19:00
12
08:11 1 a

08:12 1 a)");

    testValidation(R"(123
00:00 19:00
12
08:11 1 a
08:12 1 a

)");
}

TEST(InputValidation, Names) {
    testValidation(R"(123
00:00 19:00
12
08:11 1 a
08:12 1 aABc)");
    testValidation(R"(123
00:00 19:00
12
08:11 1 a
08:12 1 aA~!@#c)");
    testValidation(R"(123
00:00 19:00
12
08:11 1 a
08:12 1 a./c)");
    testValidation(R"(123
00:00 19:00
12
08:11 1 a
08:12 1 )");
    testValidation(R"(123
00:00 19:00
12
08:11 1 a
08:12 1 ~$&*#@(*&#$_!@#__*%a)");
}