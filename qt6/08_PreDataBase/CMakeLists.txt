#cmake_minimum_required(VERSION 3.5)
#
#project(08_PreDataBase VERSION 0.1 LANGUAGES CXX)
#
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/opt/qt@5/lib/cmake")
#
## Укажите путь к папке с драйверами
#set(PG_LIBS_PATH "${CMAKE_SOURCE_DIR}/PG_Libs")
#set(POSTGRESQL_INCLUDE "/opt/homebrew/opt/postgresql@15/include")
#set(POSTGRESQL_LIB "/opt/homebrew/opt/postgresql@15/lib")
#
#find_package(Qt5 REQUIRED COMPONENTS Widgets Sql Concurrent)
#
#set(PROJECT_SOURCES
#        main.cpp
#        mainwindow.cpp
#        mainwindow.h
#        mainwindow.ui
#        database.h
#        database.cpp
#        dbdata.h
#        dbdata.cpp
#        dbdata.ui
#)
#
#add_executable(${PROJECT_NAME}
#        ${PROJECT_SOURCES}
#)
#
## Добавляем пути для заголовочных файлов
#target_include_directories(${PROJECT_NAME} PRIVATE
#        ${PG_LIBS_PATH}/include # Заголовочные файлы из PG_Libs
#        ${POSTGRESQL_INCLUDE}   # Заголовочные файлы PostgreSQL
#        /opt/homebrew/opt/libpqxx/include
#        /opt/homebrew/opt/openssl/include
#        /opt/homebrew/opt/libiconv/include
#)
#
## Добавляем пути для библиотек
#target_link_directories(${PROJECT_NAME} PRIVATE
#        ${PG_LIBS_PATH}/lib # Библиотеки из PG_Libs
#        ${POSTGRESQL_LIB}   # Библиотеки PostgreSQL
#        /opt/homebrew/opt/libpqxx/lib
#        /opt/homebrew/opt/libpq/lib
#        /opt/homebrew/opt/openssl/lib
#        /opt/homebrew/opt/libiconv/lib
#)
#
## Подключаем библиотеки вручную
#target_link_libraries(${PROJECT_NAME} PRIVATE
#        Qt5::Widgets
#        Qt5::Sql
#        Qt5::Concurrent
#        pqxx
#        pq
#        crypto
#        iconv
#        ssl
#     #   intl
#)

cmake_minimum_required(VERSION 3.16)

project(08_PreDataBase VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/opt/qt6/lib/cmake")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/opt/homebrew/opt/qt-postgresql/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Concurrent)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        database.h
        database.cpp
        dbdata.h
        dbdata.cpp
        dbdata.ui
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        /opt/homebrew/opt/qt-postgresql/include
        /opt/homebrew/opt/postgresql@15/include
)

target_link_directories(${PROJECT_NAME} PRIVATE
        /opt/homebrew/opt/qt-postgresql/lib
        /opt/homebrew/opt/postgresql@15/lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Widgets
        Qt6::Sql
        Qt6::Concurrent
        pq
)