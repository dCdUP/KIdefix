//
// Created by nakio on 11.08.24.
//

#include <unitree/robot/channel/channel_subscriber.hpp>
#include <unitree/robot/go2/sport/sport_client.hpp>
#include <unitree/idl/ros2/PointStamped_.hpp>
#include "follow.h"

#include <cmath>

#include "stop.h"
#include "carry.h"
#include <unitree/robot/go2/sport/sport_client.hpp>

#include "vision.h"

#define TOPIC_RANGE_INFO "rt/utlidar/range_info"

using namespace unitree::robot;
using namespace unitree::common;


/*
 * Unitree Lidar has a way of returning distance to the datachannel
 * The return value is a float value ranging from -inf bis inf
 * the measureable distane is different mostly fluctuaing between 0.5 and 2.25
 *
 */

double pointsInfront;

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
    pointsInfront = range_msg->point().x();
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
        cm = firstIntervalinCm + (dist-Intervallsplit) / moreSplitDevisor;
    }

    return cm;
}

// converts the moveX Value to be always between -1 and 1 using a sigmoid function
float convertMovetoInterval(float moveX) {
    return 2*(1/(1+pow(2.71828,-moveX))) -1;
}


int follow(const std::string& Interface) {
    // setup for the LIDAR interface
    ChannelFactory::Instance()->Init(0, Interface);
    ChannelSubscriber<geometry_msgs::msg::dds_::PointStamped_> subscriber(TOPIC_RANGE_INFO);
    subscriber.InitChannel(Handler);

    sleep(3); //this allows the robot to set up the Lidar data flow. If this is not done the robot sometimes freezes.

    go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);
    sport_client.Init();


    while (true)
    {
        float moveX;
        float centimeterInfrontconstant = convertDisttoCm(pointsInfront);
        float centimeterInfront = centimeterInfrontconstant;
        const float optimalDistance = 80;
        if (centimeterInfront ==  std::numeric_limits<float>::infinity()) // the LIDAR system can return inf as values which causes the follwing calculation to stop working
            {
            centimeterInfront =70.0;
            }
            else if (centimeterInfront == -std::numeric_limits<float>::infinity())
            {
                centimeterInfront = 0;
            }
        if(centimeterInfront < optimalDistance) {
            const float lessDistanceSplit = 40.0;

            if (centimeterInfront < lessDistanceSplit)
            {
                const float lessSplitDevisor = -0.025;
                moveX = centimeterInfront*lessSplitDevisor;
            }
            else
            {
                const float moreSplitDevisor = -0.05;
                moveX = -1 + (centimeterInfront-lessDistanceSplit)*moreSplitDevisor;
            }
        }
        else if (centimeterInfront >= optimalDistance) {
            float lessSplit = 133.75;
            if (centimeterInfront < lessSplit )
            {
                const float lessMultiplyer = 0.0186;
                moveX = (centimeterInfront-optimalDistance)*lessMultiplyer;
            }
            else
            {
                const float moreMultiplyer = 0.06153;
                const float moreSplit = 53.75;
                moveX = 1 + (centimeterInfront-optimalDistance-moreSplit)*moreMultiplyer;
            }
        }
        sleep(1);
        const float maxMoveValue = 2.0;
        if (moveX > maxMoveValue)
            {
                moveX = maxMoveValue;
            }
        else if (moveX < -maxMoveValue)
            {
                moveX = -maxMoveValue;
            }
        // todo: break function if a new symbol is discovered
        const int followEnd = 38;
        if (detectState(Interface) == followEnd) {
            return 34;
        }

        moveX = convertMovetoInterval(moveX);
        sport_client.Move(moveX,0.0,0.0);
    }
}