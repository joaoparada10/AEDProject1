cmake_minimum_required(VERSION 3.26)
project(AEDProject1)

set(CMAKE_CXX_STANDARD 17)

add_executable(AEDProject1 main.cpp
        Class.h
        Class.cpp
        Student.h
        Student.cpp
        Schedule.cpp
        Filereader.cpp
        Filereader.h
        Datamanager.cpp
        Datamanager.h
        Filereader.cpp
        Request.cpp
        Request.h
)
