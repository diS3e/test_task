#include <iostream>
#include <fstream>
#include "../include/Runner.h"

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "No file!";
        return 1;
    }
    const char *fileName = argv[1];

    std::ifstream in(fileName);
    if (!in.is_open()) {
        std::cerr << "File not open!";
        return 1;
    }
    Runner runner(in, std::cout);
    int exitCode = runner.runTask();
    in.close();
    return exitCode;

}
