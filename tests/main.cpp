#include <iostream>
#include "carry.h"
#include "follow.h"
#include "start.h"
#include "stop.h"
#include "vision.h"

int main(int argc, char** argv) {
    std::cout << "Initialized!" << std::endl;
    winddown(argc,argv);
    return 0;
}
