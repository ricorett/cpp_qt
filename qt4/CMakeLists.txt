cmake_minimum_required(VERSION 3.16)

project(WidgetApp LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/opt/qt@5/lib/cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
set(SOURCES
        main.cpp
        mainwindow.cpp
)

set(HEADERS
        mainwindow.h
)

set(UI_FILES
        mainwindow.ui
)

qt5_wrap_ui(UI_HEADERS ${UI_FILES})
add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        ${UI_HEADERS}
)


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
