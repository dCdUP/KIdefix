from reportlab.lib.colors import saddlebrown

# Naki'O

## How to get the SDK running? 

### Prerequisites

*  Ubuntu 20.04.6 LTS

```bash
# Update your system 
sudo apt update && sudo apt upgrade
```


### Installation

#### IDE and other needed applications/packages

```bash
# install you ide of choice
sudo snap install clion --classic
# install git, build-essentials, g++ and cmake
sudo apt install git && sudo apt install build-essentials && sudo apt install g++ && sudo apt install cmake
```

#### Installing the SDK
```bash
# create the required directory where the sdk needs to be installed
mkdir /opt/unitree_robotics/
# clone the repository to you home directory
cd ~
git clone https://github.com/unitreerobotics/unitree_sdk2.git
#move into the git repo and build the SDK
cd unitree_sdk2/
mkdir build && cd ./build
cmake cmake .. -DCMAKE_INSTALL_PREFIX=/opt/unitree_robotics
sudo make install 
```
The compilation of the SDK should start now and complete without an error.

### Working with the IDE / CMake

We recommend working with CMakeLists.txt file that builds the executable independent of the environment or IDE.

```CMake
## Assuming your project is called foo
cmake_minimum_required(VERSION 3.28)
project(foo)

set(CMAKE_CXX_STANDARD 17)

## Additional cmake module path
list(APPEND CMAKE_PREFIX_PATH "/opt/unitree_robotics/lib/cmake")

## Find required packages
find_package(unitree_sdk2 REQUIRED)

add_executable(foo ../tests/main.cpp
        image_save.cpp)
target_link_libraries(foo unitree_sdk2)
```

**The list(), find_package(), and target_link_libraries() functions must be in place 
for the SDK to work within your project.**

### Testing if it worked

Copy the content of the build_test.cpp file from example into your IDE and compile. If there are no errors the SDK is working correctly.

# How to run applications on the dog?

Read the following website beginning at the start of the "Configuring network environment" section for that information: [https://support.unitree.com/home/en/developer/Quick_start](https://support.unitree.com/home/en/developer/Quick_start)

# Other

## Python/C(++) API
To access the Python/C(++) Api you need to install the dev version of python

```bash
# Update your system 
sudo apt update && sudo apt upgrade

# Install the dev version of python
sudo apt-get install python3-dev
```
and you need to append the following commands to the CMakeLists.txt file 

```cmake
# This includes the python interpreter into the application
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# This takes care of the path variables for the programm
include_directories(${Python3_INCLUDE_DIRS})
⚠️ 
# This includes the specified python libraries in the .py files into the application
target_link_libraries(nakio ${Python3_LIBRARIES})
```
> ⚠️ This has only been tested with the python installation of the machine
> pyenv or venv has not been tested. ⚠️