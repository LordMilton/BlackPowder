# CMakeList.txt : CMake project for BlackPowder, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.31)

project ("BlackPowder")

# Add piksel library
add_subdirectory(lib/piksel)

# Add source to this project's executable.
add_executable (BlackPowder "src/GameMaster.cpp")

set(CMAKE_CXX_STANDARD C++20)

target_include_directories(BlackPowder
    PUBLIC src
    PUBLIC lib/piksel/src
    PUBLIC inc
)
target_link_libraries(BlackPowder
    piksel
)

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET BlackPowder PROPERTY CXX_STANDARD 20)
#endif()

# TODO: Add tests and install targets if needed.