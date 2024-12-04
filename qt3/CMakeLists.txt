cmake_minimum_required(VERSION 3.16)

# Название проекта
project(DbConnectionDialogApp LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/opt/qt@5/lib/cmake")
# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем, что используем Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Указываем источники проекта
set(SOURCES
        main.cpp
        DbConnectionDialog.cpp
)

set(HEADERS
        DbConnectionDialog.h
)

set(UI_FILES
        DbConnectionDialog.ui
)

# Генерация файлов из .ui
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        ${UI_HEADERS}
)

# Указываем путь, где CMake генерирует `ui_*` файлы
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})

# Подключаем библиотеки Qt
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)