/**
 * @file Request.cpp
 * @brief Implementation for the Request class methods
 */

#include <fstream>
#include "Request.h"

Request::Request(Student involvedStudent, std::string type, Class class1, Class class2) {
    this->involvedStudent_ = involvedStudent;
    this->type_ = type;
    this->class_ = class1;
    this->newClass_ = class2;
    this->timestamp_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

Request::Request(Student involvedStudent, std::string type, Class class1) {
    this->involvedStudent_ = involvedStudent;
    this->type_ = type;
    this->class_ = class1;
    this->newClass_ = Class("A","A");
    this->timestamp_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}
Request::Request(Student involvedStudent, std::string type, Class class1, std::time_t timestamp) {
    this->involvedStudent_ = involvedStudent;
    this->type_ = type;
    this->class_ = class1;
    this->newClass_ = Class("A","A");
    this->timestamp_ = timestamp;
}

Request::Request(Student involvedStudent, std::string type, Class class1, Class class2, std::time_t timestamp){
    this->involvedStudent_ = involvedStudent;
    this->type_ = type;
    this->class_ = class1;
    this->newClass_ = class2;
    this->timestamp_ = timestamp;
}
/**@return Returns the student that made the request*/
Student Request::getRequest_student() {
    return this->involvedStudent_;
}
/**@return Returns the type of request made*/
std::string Request::getRequest_type() {
    return this->type_;
}
/**@return Returns the class the student is in before the request*/
Class Request::getRequest_class() {
    return this->class_;
}
/**@return Returns the class the student might switch to*/
Class Request::getRequest_newclass() {
    return this->newClass_;
}
/**@return Returns the timestamp of the request*/
std::time_t Request::getTimestamp() const {
    return this->timestamp_;
}
void Request::updateTimestamp() {
    this->timestamp_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}




