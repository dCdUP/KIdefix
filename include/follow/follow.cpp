//
// Created by nakio on 11.08.24.
//

#include <unitree/robot/channel/channel_subscriber.hpp>
#include <unitree/robot/go2/sport/sport_client.hpp>
#include <unitree/idl/ros2/PointStamped_.hpp>
#include "follow.h"
#include "stop.h"
#include "carry.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

#define TOPIC_RANGE_INFO "rt/utlidar/range_info"

using namespace unitree::robot;
using namespace unitree::common;


/*
 * Unitree Lidar has a way of returning distance to the datachannel
 * The return value is a float value ranging from -inf bis inf
 * the measureable distane is different mostly fluctuaing between 0.5 and 2.25
 *
 */

double distanceInfront;

void Handler(const void *message)
{
    // print msg info
    const geometry_msgs::msg::dds_::PointStamped_ *range_msg = (const geometry_msgs::msg::dds_::PointStamped_ *)message;
    std::cout << "Received a range info message here!"
            //<< "\n\tstamp = " << range_msg->header().stamp().sec() << "." << range_msg->header().stamp().nanosec()
            //<< "\n\tframe = " << range_msg->header().frame_id()
            << "\n\trange front = " << range_msg->point().x()
            //<< "\n\trange left = " << range_msg->point().y()
            //<< "\n\trange right = " << range_msg->point().z()
            << std::endl << std::endl;
    distanceInfront = range_msg->point().x();
}

float convertDisttoCm(float dist) {
    float cm;
    constexpr float Intervallsplit = 0.75;

    if (dist <= Intervallsplit) {
        const float lessIntervalDevisor = 0.015;
        cm = dist  / lessIntervalDevisor;
    }
    else {
        const float firstIntervalinCm = 50;
        const float moreSplitDevisor = 0.01;
        cm = firstIntervalinCm + (dist-Intervallsplit) * moreSplitDevisor;
    }

    return cm;
}


int accompany(const std::string networkInterface) {
    ChannelFactory::Instance()->Init(0, networkInterface);
    ChannelSubscriber<geometry_msgs::msg::dds_::PointStamped_> subscriber(TOPIC_RANGE_INFO);

    go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);
    sport_client.Init();

    const float firstInterval = 0.6;
    const float firstIntervalMultiplyer = 5/3;
    float secondInterval;
    const float secondIntervalMultiplyer = 10/3;
    float distancetoMove = 0;


    while (true)
    {

        sport_client.Move(distancetoMove,0.0,0.0);

    }
}

