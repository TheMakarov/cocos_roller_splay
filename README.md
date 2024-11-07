# Minimalistic Game using Cocos2d-x

## Overview

This project is a small, minimalistic game developed using the Cocos2d-x framework in C++. It contains various scenes from the game, including an intro scene, a menu scene, and multiple game scenes. The project is not fully runnable and does not include the complete framework skeleton; it focuses on showcasing the different scenes and their implementations.


## Prerequisites

- Cocos2d-x framework
- C++ compiler (e.g., `g++` or `clang++`)
- CMake (for building the project)

## Setup

### Building the Project ( download the framework's skeleton from other sources )

1. Create a build directory:
    ```sh
    mkdir build
    cd build
    ```

2. Generate the build files using CMake:
    ```sh
    cmake ..
    ```

3. Build the project:
    ```sh
    make
    ```

## Scenes

### Intro Scene

- **Intro.cpp**: Implementation of the intro scene.
- **Intro.h**: Header file for the intro scene.

### Menu Scene

- **Menu_scene.cpp**: Implementation of the menu scene.
- **Menu_scene.h**: Header file for the menu scene.

### Game Scenes

- **Scene1.cpp**: Implementation of the first game scene.
- **Scene1.h**: Header file for the first game scene.
- **Scene2.cpp**: Implementation of the second game scene.
- **Scene2.h**: Header file for the second game scene.
- **Scene3.cpp**: Implementation of the third game scene.
- **Scene3.h**: Header file for the third game scene.

## How It Works

- The project uses the Cocos2d-x framework to create and manage different scenes in the game.
- Each scene is implemented in its respective `.cpp` and `.h` files, showcasing the structure and functionality of the game.
- The `AppDelegate` class manages the application lifecycle and transitions between scenes.

## Note

Please be aware that this project contains some bad words in the code. We apologize for any offense caused and will work on cleaning up the language in future updates.

## Acknowledgments

- Thanks to the Cocos2d-x community for their excellent documentation and support.
- Thanks to the C++ community for their comprehensive resources and tools.
