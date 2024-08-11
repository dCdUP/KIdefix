//
// Created by nakio on 11.08.24.
//

#include "start.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

int startup(int argc, char **argv) {
    std::cout << "startup routine" << std::endl;
    if (argc < 2) {
        std::cout << "No networkInterface defined. Please define an interface" << std::endl;
        exit(-1);
    }
    unitree::robot::ChannelFactory::Instance()->Init(0, argv[1]);
    //argv[1] is network interface of the robot

    //Create a sports client object
    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);//Timeout time
    sport_client.Init();

    sport_client.Dance1();
    sleep(3);

    sport_client.WiggleHips();
    sleep(3);

    sport_client.Hello();



    return 0;
}
