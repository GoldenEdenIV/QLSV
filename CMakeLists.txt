cmake_minimum_required(VERSION 3.16)

project(QLSV VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    QLDSV_TC.cpp
    QLDSV_TC.h
)

add_executable(QLDSV_TC_GUI ${PROJECT_SOURCES})

target_link_libraries(QLDSV_TC_GUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
