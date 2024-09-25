# KIdefix

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

# Image Object Detection

## YOLO

### Prerequisites
Install Ultralytics via pip. The different methods are found here: https://pytorch.org/get-started/locally/ 
A good quickstart guide can be found here: https://docs.ultralytics.com/quickstart/#use-ultralytics-with-cli 
```python
# Install the ultralytics package from PyPI
pip install ultralytics
```
If you want to use it on a Windows machine only with CPU computing:
```python
pip3 install torch torchvision torchaudio
```
### Use Ultralytics with Python
YOLOv8's Python interface allows for seamless integration into your Python projects, making it easy to load, run, and process the model's output. For example, users can load a model, train it, evaluate its performance on a validation set. 

# Train a custom model
## Dataset
You need a dataset in order to train your model. For example you can find already annotated datasets on this website: https://www.kaggle.com/datasets
If you want to create your own dataset you need many different pictures with the object you want to detect. Next you need to annotate every picture with bounding boxes and a label. On this website you can create those bounding boxes and label them: https://www.cvat.ai/ 
A good Tutorial can be found here: https://youtu.be/m9fH9OWn8YM?si=RkcKTrRAjdondD2F 
We use YOLO, so you need to export the dataset in the YOLO format from the website. After that put the images and labels in the right folder structure. For example: \Bilderkennung\images\train and \Bilderkennung\labels\train 

## Config.yaml
Next you need to create a config.yaml file containing every needed information for the training. For example:

```python
path: #here insert the absolute path to the folder containing the train and labels folder
train: images/train
val: images/train 

names: 
  0: kreis
  1: raute
  2: x
  3: pfeil
  4: dreieck 
```
The config.yaml and the .py file must be in the same folder. 

## Training the model
If you did everything you can train your custom YOLO model with the following code:

```python
from ultralytics import YOLO 

# Load a model
model = YOLO("yolov10n.yaml")  # build a new model from YAML
model = YOLO("yolov10n.pt")  # load a pretrained model (recommended for training)
#model = YOLO("yolov8n.yaml").load("yolov8n.pt")  # build from YAML and transfer weights

# Train the model
model.train(data="config.yaml", epochs=200, batch =32) 
``` 
Congratulations you have created a custom YOLO model. You can find the model in the folder, where your training image folder is: \runs\detect\train\weights 
It's recommended using the last.pt model for further usage. 

# Using the model
We want to analyse an image, detect multiple objects and if the confidence score is above a specific value and a specific object is detected KIdefix will do a task. We use the following code:

```python
from ultralytics import YOLO

model = YOLO("traffic signs.pt") #lädt das Modell

source = r"C:\Users\domen\OneDrive\Hochschule Studium\SS 24\Advanced Data- and Information Management Technologies\Bilderkennung\Trainingsbilder\nstopg.jpg" #Pfad des Bildes

results = model(source) #gibt das Bild ins Modell zur Analyse

for result in results:
    boxes = result.boxes #the bounding boxes 
    masks = result.masks #Masks object containing the detected instance masks
    keypoints = result.keypoints #Keypoints of the image
    probs = result.probs #used to index, get top1 and top5 indices and scores of classification
    obb = result.obb 

#Loop through each detected object
    for box in boxes:
        class_id = box.cls #was erkannt wurde
        confidence = box.conf #der confidence score des erkannten Objekts
        x_min, y_min, x_max, y_max = box.xyxy[0] #die Koordinaten des erkannten Objekts

        print(f"Detected object with Class ID: {class_id} and Confidence: {confidence}")
        print(f"Bounding Box: [{x_min}, {y_min}, {x_max}, {y_max}]")

    result.show() #öffnet das Bild mit eingezeichneten Boxen und Ergebnissen
    result.save(filename = "result.jpg") #speichert das Ergebnis als Bild 

if boxes.conf.item() >0.3 and boxes.cls == 40. : #wenn der Konfidenzscore über 30% ist und das Stopschild (ID= 40.) erkannt wurde
    print("folgendes gefunden: ",result.boxes.cls)
else:
    print("Nichts gefunden") 
```
