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


int vision(const std::string& Interface)
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
        Py_Initialize();
        // todo: add error checking and add functionality that creates relative paths
        // todo: pass the vector of the image to the python script and return a cordinate to the function back. Rest is up to domenic
        std::string inputPath = "/home/nakio/CLionProjects/nakio/include/vision";
        PyObject * pSysPath = PySys_GetObject("path");
        PyList_Append(pSysPath, PyUnicode_DecodeFSDefault(inputPath.c_str()));

        PyObject * pName = PyUnicode_DecodeFSDefault("vision");
        PyObject * pModule = PyImport_Import(pName);
        PyObject * pFunc = PyObject_GetAttrString(pModule,"vision");
        PyObject * pArgs = PyTuple_New(1);
        PyTuple_SetItem(pArgs, 0, PyLong_FromLong(10));
        PyObject * pValue = PyObject_CallObject(pFunc, pArgs);
        long result = PyLong_AsLong(pValue);
        std::cout << result << std::endl;
        Py_Finalize();
    }
}