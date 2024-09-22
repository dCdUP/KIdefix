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
    int currentState;
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);
    unitree::robot::go2::VideoClient video_client;
    video_client.SetTimeout(1.0f);
    video_client.Init();

    std::vector<uint8_t> image_sample;
    int ret;

    while (currentState != 5)
    {
        ret = video_client.GetImageSample(image_sample);
        std::string imageName = "/picture/capture.png";
        if (ret == 0) {
            std::ofstream image_file(imageName, std::ios::binary);
            if (image_file.is_open()) {
                image_file.write(reinterpret_cast<const char*>(image_sample.data()), image_sample.size());
                image_file.close();
                std::cout << "Image saved successfully as " << imageName << std::endl;
            }
        }

        Py_Initialize();
        std::string inputPath = "/home/nakio/CLionProjects/nakio/include/vision";
        PyObject * pSysPath = PySys_GetObject("path");
        PyList_Append(pSysPath, PyUnicode_DecodeFSDefault(inputPath.c_str()));

        PyObject * pName = PyUnicode_DecodeFSDefault("vision");
        PyObject * pModule = PyImport_Import(pName);
        PyObject * pFunc = PyObject_GetAttrString(pModule,"detectState");
        PyObject * pArgs = PyTuple_New(1);
        PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(imageName.c_str()));
        PyObject * pValue = PyObject_CallObject(pFunc, pArgs);
        currentState = static_cast<int>(PyLong_AsLong(pValue));
        if (currentState > 5) {
            currentState = 5;
        }
        Py_Finalize();
    }
    return currentState;
}

int moveAngle(const std::string &Interface) {
    int State;
    double xCoordinate;
    unitree::robot::ChannelFactory::Instance()->Init(0, Interface);
    unitree::robot::go2::VideoClient video_client;
    video_client.SetTimeout(1.0f);
    video_client.Init();

    std::vector<uint8_t> image_sample;
    int ret;

    while (State != 2)
    {
        ret = video_client.GetImageSample(image_sample);
        std::string imageName = "/picture/capture.png";
        if (ret == 0) {
            std::ofstream image_file(imageName, std::ios::binary);
            if (image_file.is_open()) {
                image_file.write(reinterpret_cast<const char*>(image_sample.data()), image_sample.size());
                image_file.close();
                std::cout << "Image saved successfully as " << imageName << std::endl;
            }
        }

        Py_Initialize();
        std::string inputPath = "./module";
        PyObject * pSysPath = PySys_GetObject("path");
        PyList_Append(pSysPath, PyUnicode_DecodeFSDefault(inputPath.c_str()));

        PyObject * pName = PyUnicode_DecodeFSDefault("vision");
        PyObject * pModule = PyImport_Import(pName);
        PyObject * pFunc = PyObject_GetAttrString(pModule,"moveAngle");
        PyObject * pArgs = PyTuple_New(1);
        PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(imageName.c_str()));
        PyObject * pValue = PyObject_CallObject(pFunc, pArgs);
        PyObject *StatePtr = PyTuple_GetItem(pValue, 0);
        PyObject *xCoordinatePtr = PyTuple_GetItem(pValue, 1);

        State = static_cast<int>(PyLong_AsLong(StatePtr));
        if (State == 2) {
            xCoordinate = PyFloat_AsDouble(xCoordinatePtr);
            break;
        }
    }
    return xCoordinate;
}
