//
// Created by nakio on 11.08.24.
//
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "vision.h"
#include <string>
#include <unitree/robot/go2/video/video_client.hpp>
#include <iostream>
#include <fstream>
#include <ctime>


int detectState(const std::string& Interface)
{
    int currentState = 1;
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);
    unitree::robot::go2::VideoClient video_client;
    video_client.SetTimeout(1.0f);
    video_client.Init();

    std::vector<uint8_t> image_sample;
    int ret;
    std::string inputPath = "./module";
    PyObject* pSysPath = PySys_GetObject("path");
    PyList_Append(pSysPath, PyUnicode_FromString(inputPath.c_str()));
    PyObject* pName = PyUnicode_DecodeFSDefault("vision");
    PyObject* pModule = PyImport_Import(pName);

    while (currentState != 40 && currentState != 24 && currentState != 22 && currentState != 38 && currentState != 0  && currentState != 34 )
    {
        ret = video_client.GetImageSample(image_sample);
        std::string imageName = "./picture/capture.png";
        if (ret == 0) {
            std::ofstream image_file(imageName, std::ios::binary);
            if (image_file.is_open()) {
                image_file.write(reinterpret_cast<const char*>(image_sample.data()), image_sample.size());
                image_file.close();
                std::cout << "Image saved successfully as " << imageName << std::endl;
            }
        }


        PyObject* pFunc = PyObject_GetAttrString(pModule, "detectState");

        PyObject* pArgs = PyTuple_New(1);
        PyObject* pArgValue = PyUnicode_FromString(imageName.c_str());
        PyTuple_SetItem(pArgs, 0, pArgValue);

        PyObject* pValue = PyObject_CallObject(pFunc, pArgs);

        currentState = static_cast<int>(PyLong_AsLong(pValue));
        sleep(3);

    }
    return currentState;
}

int moveAngle(const std::string &Interface) {
    return 0;
}