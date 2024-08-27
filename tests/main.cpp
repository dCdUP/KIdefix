#include <iostream>
#include "carry.h"
#include "follow.h"
#include "start.h"
#include "stop.h"
#include "vision.h"

enum States {
    Start,
    Carry,
    Follow,
    CarryEnd,
    Stop
};

int DetectState();

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "No networkInterface defined. Please define an interface" << std::endl;
        exit(-1);
    }

    const std::string Interface = argv[1];
    std::cout << "Initialized!" << std::endl;
    int State = start(Interface);
    int NextState;
    // todo: move state machine to seperate function
    // todo: unify the function naming Scheme
    // todo: switch to memory managed assignment of variables
    while(State != Stop) {
        if (State == Start) {
            NextState = DetectState();
            while (NextState != Carry || NextState != Follow || NextState != Stop) {
                NextState = DetectState();
            }
            switch (NextState) {
                case Carry:
                    State = carry(Interface);
                case Follow:
                    State = follow(Interface);
                case Stop:
                    State = stop(Interface);
                default:
                    break;
            }
        }else if (State == Carry) {
            NextState = DetectState();
            while (NextState != Follow || NextState != CarryEnd) {
                NextState = DetectState();
            }
            switch (NextState) {
                case Follow:
                    State = follow(Interface);
                case CarryEnd:
                    //todo: create CarryEnd() function
                default:
                    break;
            }
        }
        else if (State == Follow) {
            NextState = DetectState();
            while (NextState != Carry || NextState != CarryEnd || NextState != Stop) {
                NextState = DetectState();
            }
            switch (NextState) {
                case Carry:
                    State = carry(Interface);
                case CarryEnd:
                    //State = carryend(Interface);
                default:
                    break;
            }
        } else if (State == CarryEnd) {
            NextState = DetectState();
            while (NextState != Carry || NextState != Follow || NextState != Stop) {
                NextState = DetectState();
            }
            switch (NextState) {
                case Carry:
                    State = carry(Interface);
                case Follow:
                    State = follow(Interface);
                case Stop:
                    State = stop(Interface);
                default:
                    break;
            }
    }

    }
}

