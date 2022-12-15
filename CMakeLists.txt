# make min version 3.12
cmake_minimum_required(VERSION 3.12)

# this is to make vcpkg work
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# add our project
project(CurveNet CXX)

find_package(NGL CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)

# find Qt libs first we check for Version 6
find_package(Qt6 COMPONENTS OpenGL Widgets QUIET )
if ( Qt6_FOUND )
    message("Found Qt6 Using that")
else()
    message("Found Qt5 Using that")
    find_package(Qt5 COMPONENTS OpenGL Widgets REQUIRED)
endif()

#set some project values
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

#add an executable name for this program
add_executable(CurveNet)

#add source files for my project
include_directories(include $ENV{HOME}/NGL/include)
target_sources(CurveNet PRIVATE  ${PROJECT_SOURCE_DIR}/src/main.cpp  
${PROJECT_SOURCE_DIR}/src/NGLScene.cpp  
${PROJECT_SOURCE_DIR}/include/NGLScene.h  
src/Intersection.cpp include/Intersection.h src/Segment.cpp include/Segment.h src/Curve.cpp include/Curve.h src/Spline.cpp include/Spline.h)
target_link_libraries(CurveNet PRIVATE Qt::Widgets Qt::OpenGL NGL)

#Add testing stuff

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(MathTest)
include_directories(include)
target_sources(MathTest PRIVATE tests/Test.cpp
${CMAKE_SOURCE_DIR}/include/Intersection.h
${CMAKE_SOURCE_DIR}/src/Intersection.cpp
${CMAKE_SOURCE_DIR}/include/Segment.h
${CMAKE_SOURCE_DIR}/src/Segment.cpp) 
target_link_libraries(MathTest PRIVATE GTest::gtest GTest::gtest_main)
gtest_discover_tests(MathTest)
