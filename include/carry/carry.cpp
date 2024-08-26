//
// Created by nakio on 11.08.24.
//
#include "carry.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

int transfer(const std::string & Interface) {
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);

    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);//Timeout time
    sport_client.Init();

    //wait for next symbol
    while (true) {
        sport_client.BalanceStand();
        sleep(3);
        //todo: place function here that detects if symbol is present
        return 0;
    }
}
