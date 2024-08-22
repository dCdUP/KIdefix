//
// Created by nakio on 11.08.24.
//
#include "vision.h"
#include <string>
#include <unitree/robot/go2/video/video_client.hpp>
#include <iostream>
#include <fstream>
#include <ctime>


int watch(const std::string& Interface)
{

    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);
    unitree::robot::go2::VideoClient video_client;
    video_client.SetTimeout(1.0f);
    video_client.Init();

    std::vector<uint8_t> image_sample;
    int ret;

    while (true)
    {
        ret = video_client.GetImageSample(image_sample);

        if (ret == 0) {
            time_t rawtime;
            tm *timeinfo;
            char buffer[80];

            time(&rawtime);
            timeinfo = localtime(&rawtime);

            strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S.jpg", timeinfo);
            std::string image_name(buffer);

            std::ofstream image_file(image_name, std::ios::binary);
            if (image_file.is_open()) {
                image_file.write(reinterpret_cast<const char*>(image_sample.data()), image_sample.size());
                image_file.close();
                std::cout << "Image saved successfully as " << image_name << std::endl;
            } else {
                std::cerr << "Error: Failed to save image." << std::endl;
            }
        }

        sleep(3);
    }
}