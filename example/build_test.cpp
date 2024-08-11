#include <unitree/robot/go2/sport/sport_client.hpp>
#include <unistd.h>
#include "image_save.cpp"

int main(const int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " networkInterface" << std::endl;
        exit(-1);
    }
    unitree::robot::ChannelFactory::Instance()->Init(0, argv[1]);
    //argv[1] is network interface of the robot



    //Create a sports client object
    unitree::robot::go2::SportClient sport_client;
    sport_client.SetTimeout(10.0f);//Timeout time
    sport_client.Init();

    sport_client.Sit(); //Special action, robot dog sitting down
    sleep(3);//delay 3s
    sport_client.RiseSit(); //Restore
    sleep(3);

    return 0;
}