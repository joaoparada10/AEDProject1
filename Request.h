/**
 * @file Request.h
 * @brief Header file for the Request class
 */


#ifndef REQUEST_H
#define REQUEST_H


#include <string>
#include <chrono>
#include <ctime>
#include "Student.h"
#include <iostream>
#include <iomanip>

class Request
{
private:
    Student involvedStudent_; /** student involved on the request*/
    std::string type_; /**request type (add, remove,switch)*/
    Class class_; /** class subject to being added/removed or quitting in case of a switch, the old class*/
    Class newClass_; /** In case of a switch, the new class of a student */
    std::chrono::system_clock::time_point timestamp_;
public:
    /**Default constructor*/
    Request(Student involvedStudent, std::string type, Class classe1); // so pode acontecer um add ou um remove
    /**Switch type constructor*/
    Request(Student involvedStudent, std::string type, Class classe1, Class class2); // vai acontecer um switch, um switch so pode acontcer se for entre 2 turmas da mesma uc ou entre ucs dif
    Student getRequest_student();
    std::string getRequest_type();
    Class getRequest_class();
    Class getRequest_newclass();
    std::chrono::system_clock::time_point getTimestamp();
    /**@brief Prints the time stamp */
    void printTimestamp() const {
        std::time_t timestamp_time = std::chrono::system_clock::to_time_t(timestamp_);
        std::tm* timeinfo = std::localtime(&timestamp_time);
        std::cout << "On " << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S") << std::endl;
    }
    /**@brief Updates the time stamp */
    void updateTimestamp();
};




#endif