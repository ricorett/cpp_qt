cmake_minimum_required(VERSION 3.16)

project(StopwatchApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/opt/qt@5/lib/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

set(SOURCES
    main.cpp
    mainwindow.cpp
    Stopwatch.cpp
)

set(HEADERS
    mainwindow.h
    Stopwatch.h
)

set(UI ui/mainwindow.ui)



add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt::Core Qt::Gui)
