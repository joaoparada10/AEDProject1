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
    std::time_t timestamp_;
public:
    /**Default constructor*/
    Request(Student involvedStudent, std::string type, Class classe1);
    /**Switch type constructor*/
    Request(Student involvedStudent, std::string type, Class classe1, Class class2);
    Request(Student involvedStudent, std::string type, Class class1, std::time_t timestamp);
    Request(Student involvedStudent, std::string type, Class class1, Class class2, std::time_t timestamp);
    Student getRequest_student();
    std::string getRequest_type();
    Class getRequest_class();
    Class getRequest_newclass();
    [[nodiscard]] std::time_t getTimestamp() const;
    /**@brief Prints the time stamp */
    void printTimestamp() const {
        std::tm* timeinfo = std::localtime(&this->timestamp_);
        std::cout << "On " << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    }
    /**@brief Updates the time stamp */
    void updateTimestamp();
};




#endif