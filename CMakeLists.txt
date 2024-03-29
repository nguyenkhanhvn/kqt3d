cmake_minimum_required(VERSION 3.14)

project(kqt3d LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("debug mode")
#    add_definitions(-DRENDER_LOG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    message("release mode")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

include_directories(kqtcore3d/include)
add_subdirectory(kqtcore3d)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick OpenGL)

file(GLOB_RECURSE  HEADER_FILES "include/*.h")
file(GLOB_RECURSE  SOURCE_FILES "src/*.cpp")
add_library(kqt3d STATIC
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

include_directories(include)

target_include_directories(kqt3d PRIVATE include/kqt3d include/kqt3d/interfaces include/kqt3d/components include/kqt3d/components/opengl include/kqt3d/models)

if(WIN32)
    set(GRAPHIC_API opengl32)
else()
    message(FATAL_ERROR "platform: platform not support")
endif()

target_link_libraries(kqt3d
    PRIVATE
    Qt6::Quick
    Qt6::OpenGL
    ${GRAPHIC_API}
    kqtcore3d
)
