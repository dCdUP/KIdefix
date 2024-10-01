//
// Created by KIdefix on 11.08.24.
//

#include "start.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

int start(const std::string & Interface) {
    std::cout << "startup routine" << std::endl;
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);
    //argv[1] is network interface of the robot

    //Create a sports client object
    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);//Timeout time
    sport_client.Init();

    sleep(3);
    sport_client.Hello();
    sleep(4);
    return 24;
}
