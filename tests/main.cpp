#include <iostream>
#include "carry.h"
#include "follow.h"
#include "start.h"
#include "stop.h"
#include "vision.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "No networkInterface defined. Please define an interface" << std::endl;
        exit(-1);
    }
    const std::string Interface = argv[1];
    std::cout << "Initialized!" << std::endl;
    watch(Interface);
    //winddown(Interface);
    //accompany(Interface);
    return 0; // returner;
}
