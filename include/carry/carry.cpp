//
// Created by nakio on 11.08.24.
//
#include "carry.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

int carry(const std::string & Interface) {
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);

    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);//Timeout time
    sport_client.Init();
    sport_client.BalanceStand();

    bool RoutineBreak = false;
    while (!RoutineBreak) {
        //todo: place function here that detects if symbol is present, if so switch bool to true
    }

    int State;
    bool IsValidState = false;
    while (!IsValidState) {
        if (State == 2 || State == 3) {
            IsValidState = true;
        }

    }
    return State;
}
