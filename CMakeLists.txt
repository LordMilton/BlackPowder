﻿# CMakeList.txt : CMake project for BlackPowder, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.31)

project ("BlackPowder")

# Add piksel library
add_subdirectory(lib/piksel)

# Add source to this project's executable.
add_executable (BlackPowder
                "src/App.cpp"
                "src/GameMaster.cpp"
                "src/Interactions.cpp"
                "src/Menu.cpp"
                "src/Storage.cpp"
                "src/powders/Fire.cpp"
                "src/powders/Powder.cpp"
                "src/powders/Sand.cpp"
                "src/powders/Wall.cpp"
                "src/powders/Water.cpp")

set(CMAKE_CXX_STANDARD C++20)

target_include_directories(BlackPowder
    PUBLIC lib/piksel/src
    PUBLIC lib/piksel/lib
    PUBLIC lib/piksel/lib/glm/glm/detail
    PUBLIC inc
    PUBLIC inc/powders
)
target_link_libraries(BlackPowder
    piksel
)

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET BlackPowder PROPERTY CXX_STANDARD 20)
#endif()

# TODO: Add tests and install targets if needed.