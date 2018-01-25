cmake_minimum_required(VERSION 3.8)
project(ueb06naji)

set(CMAKE_CXX_STANDARD 11)

include_directories("header" "src")

set(SOURCE_FILES
        header/database.h
        header/datastructure.h
        header/datetime.h
        header/list.h
        header/menu.h
        header/sort.h
        header/teams.h
        header/tools.h
        src/xml/team.xml
        src/xml/teams.xml
        src/database.c
        src/datetime.c
        src/list.c
        src/main.c
        src/menu.c
        src/sort.c
        src/teams.c
        src/tools.c)

add_executable(ueb06naji ${SOURCE_FILES})