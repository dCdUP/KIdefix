#include <iostream>
#include "carry.h"
#include "follow.h"
#include "start.h"
#include "stop.h"
#include "vision.h"

const enum States {
    Start,
    Carry,
    Follow,
    Stop
};

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "No networkInterface defined. Please define an interface" << std::endl;
        exit(-1);
    }
    const std::string Interface = argv[1];
    std::cout << "Initialized!" << std::endl;
    int LastState = startup(Interface);
    // todo: implement state machine
    if (LastState != 0) {
        while(LastState != 3) {
            switch(LastState) {
                case Start:
                    std::cout << "Starting..." << std::endl;
                case Carry:
                    std::cout << "Carrying..." << std::endl;
                case Follow:
                    std::cout << "Following..." << std::endl;
                case Stop:
                    return 0;
                default:
                    return -1;
            }
        }
    }else {
        return -1;
    }

}
