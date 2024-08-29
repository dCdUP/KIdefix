//
// Created by nakio on 27.08.24.
//
#include "statemachine.h"

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

int DetectState() {
    int state;
    std::cin >> state;
    return state;
}

int statemachine(const std::string& Interface) {
    int State = DetectState();//start(Interface);
    int NextState;
    bool isCarrying;
    // todo: switch to memory managed assignment of variables
    while(State != Stop) {
        if (State == Start) {
            NextState = DetectState();
            while (NextState != Carry && NextState != Follow && NextState != Stop) {
                NextState = DetectState();
            }
            switch (NextState) {
                case Carry:
                    State = carry(Interface,isCarrying);
                    break;
                case Follow:
                    State = follow(Interface);
                    break;
                case Stop:
                    State = stop(Interface);
                    break;
                default:
                    break;
            }
        }else if (State == Carry) {
            NextState = DetectState();
            while (NextState != Follow && NextState != CarryEnd) {
                NextState = DetectState();
            }
            switch (NextState) {
                case Follow:
                    State = follow(Interface);
                    break;
                case CarryEnd:
                    if(isCarrying) {
                        State = stopcarry(Interface,isCarrying);
                    }
                    break;
                default:
                    break;
            }
        }
        else if (State == Follow) {
            NextState = DetectState();
            while (NextState != Carry && NextState != CarryEnd && NextState != Stop) {
                NextState = DetectState();
            }
            switch (NextState) {
                case Carry:
                    State = carry(Interface,isCarrying);
                    break;
                case CarryEnd:
                    if(isCarrying) {
                        State = stopcarry(Interface,isCarrying);
                    }
                default:
                    break;
            }
        } else if (State == CarryEnd) {
            NextState = DetectState();
            while (NextState != Carry && NextState != Follow && NextState != Stop) {
                NextState = DetectState();
            }
            switch (NextState) {
                case Carry:
                    State = carry(Interface,isCarrying);
                    break;
                case Follow:
                    State = follow(Interface);
                    break;
                case Stop:
                    State = stop(Interface);
                    break;
                default:
                    break;
            }
    }
    }
    return 0;
}
