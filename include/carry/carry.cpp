//
// Created by nakio on 11.08.24.
//
#include "carry.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

int carry(const std::string& Interface,bool& isCarrying) {
    int State = 1;
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);

    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);//Timeout time
    sport_client.Init();
    sport_client.BalanceStand();
    isCarrying = true;
    return State;
}

int stopcarry(const std::string &Interface, bool& isCarrying) {
    int State = 3;
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);

    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);
    sport_client.Init();

    sport_client.StopMove();

    sleep(5);

    sport_client.BalanceStand();
    isCarrying = false;
    return State;
}