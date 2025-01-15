cmake_minimum_required(VERSION 3.5)

project(08_PreDataBase VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/opt/qt@5/lib/cmake")

# Укажите путь к папке с драйверами
set(PG_LIBS_PATH "${CMAKE_SOURCE_DIR}/PG_Libs")
set(POSTGRESQL_INCLUDE "/opt/homebrew/opt/postgresql@15/include")
set(POSTGRESQL_LIB "/opt/homebrew/opt/postgresql@15/lib")

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql Concurrent)

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

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
)

# Добавляем пути для заголовочных файлов
target_include_directories(${PROJECT_NAME} PRIVATE
        ${PG_LIBS_PATH}/include # Заголовочные файлы из PG_Libs
        ${POSTGRESQL_INCLUDE}   # Заголовочные файлы PostgreSQL
        /opt/homebrew/opt/libpqxx/include
        /opt/homebrew/opt/openssl/include
        /opt/homebrew/opt/libiconv/include
)

# Добавляем пути для библиотек
target_link_directories(${PROJECT_NAME} PRIVATE
        ${PG_LIBS_PATH}/lib # Библиотеки из PG_Libs
        ${POSTGRESQL_LIB}   # Библиотеки PostgreSQL
        /opt/homebrew/opt/libpqxx/lib
        /opt/homebrew/opt/libpq/lib
        /opt/homebrew/opt/openssl/lib
        /opt/homebrew/opt/libiconv/lib
)

# Подключаем библиотеки вручную
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Widgets
        Qt5::Sql
        Qt5::Concurrent
        pqxx
        pq
        crypto
        iconv
        ssl
     #   intl
)


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
##set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/opt/postgresql@15/lib")
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/opt/homebrew/opt/postgresql@15/lib")
#
##find_package(PostgreSQL REQUIRED)
#find_package(Qt5 REQUIRED COMPONENTS Widgets Sql Concurrent) # ${PostgreSQL_LIBRARIES})
#
## Укажите путь к папке с драйверами
#set(PG_LIBS_PATH "${CMAKE_SOURCE_DIR}/PG_Libs")
#
#set(PROJECT_SOURCES
#		main.cpp
#		mainwindow.cpp
#		mainwindow.h
#		mainwindow.ui
#		database.h
#		database.cpp
#		dbdata.h
#		dbdata.cpp
#		dbdata.ui
#)
#
#add_executable(${PROJECT_NAME}
#		${PROJECT_SOURCES}
#)
#
## Добавляем путь для заголовочных файлов
#target_include_directories(${PROJECT_NAME} PRIVATE
#		${PG_LIBS_PATH}/include # Заголовочные файлы из PG_Libs
#		/opt/homebrew/opt/libpqxx/include
#		/opt/homebrew/opt/libpq/include
#		/opt/homebrew/opt/openssl/include
#		/opt/homebrew/opt/libiconv/include
#)
#
## Добавляем путь для библиотек
#target_link_directories(${PROJECT_NAME} PRIVATE
#		${PG_LIBS_PATH}/lib # Библиотеки из PG_Libs
#		/opt/homebrew/opt/libpqxx/lib
#		/opt/homebrew/opt/libpq/lib
#		/opt/homebrew/opt/openssl/lib
#		/opt/homebrew/opt/libiconv/lib
#)
#
## Подключаем библиотеки
#target_link_libraries(${PROJECT_NAME} PRIVATE
#		Qt5::Widgets
#		Qt5::Sql
#		Qt5::Concurrent
#		pqxx
#		pq
#		crypto
#		iconv
#)
