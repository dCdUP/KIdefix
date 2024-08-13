#include <iostream>
#include "carry.h"
#include "follow.h"
#include "start.h"
#include "stop.h"
#include "vision.h"

int main(int argc, char **argv) {
    std::cout << "Initialized!" << std::endl;
    winddown(argc,argv);
    //int returner = accompany("enp0s31f6");
    return 0; // returner;
}
