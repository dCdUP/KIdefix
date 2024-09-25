#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include "statemachine.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "No networkInterface defined. Please define an interface" << std::endl;
        exit(-1);
    }

    const std::string Interface = argv[1];
    std::cout << "Initialized!" << std::endl;
    Py_Initialize();
    statemachine(Interface);
    Py_Finalize();
    return 0;
}