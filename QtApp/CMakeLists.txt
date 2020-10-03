cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME QtApp)

project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

file(GLOB_RECURSE PROJECT_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

set(PROJECT_HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
include_directories(${PROJECT_HEADER})

file(GLOB QT_DEPENDENCIES "qt_dependencies/*")
file(COPY ${QT_DEPENDENCIES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(QT5_PLUGINS Core Gui Widgets Bluetooth)
find_package(Qt5 COMPONENTS ${QT5_PLUGINS} REQUIRED)

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SRC})

foreach(plugin ${QT5_PLUGINS})
    target_link_libraries(${PROJECT_NAME} Qt5::${plugin})
    set_target_properties(Qt5::${plugin} PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "DEBUG")
endforeach()

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME BikUS CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
