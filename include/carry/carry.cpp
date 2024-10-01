//
// Created by KIdefix on 11.08.24.
//
#include "carry.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

int carry(const std::string& Interface,bool& isCarrying) {
    constexpr int State = 22;
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);

    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);//Timeout time
    sport_client.Init();
    sport_client.BalanceStand();
    std::cout << "Starting carry mode" << std::endl;
    sleep(15);
    isCarrying = true;
    return State;
}

int stopcarry(const std::string &Interface, bool& isCarrying) {
    constexpr int State = 0;
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);

    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);
    sport_client.Init();

    sport_client.StopMove();
    sport_client.BalanceStand();
    std::cout << "Stopping Carry Mode" << std::endl;
    sleep(15);
    isCarrying = false;
    return State;
}