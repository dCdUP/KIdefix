//
// Created by nakio on 11.08.24.
//
#include "stop.h"
#include "carry.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

int winddown(std::string &Interface, const bool iscarrying) {

    if (iscarrying) {
        transfer(Interface);
    }

    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);
    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);
    sport_client.Init();


    sleep(5);
    sport_client.Heart();
    sleep(3);
    sport_client.StandDown();
    sleep(5);
    sport_client.StandUp();

    return 0;
}
