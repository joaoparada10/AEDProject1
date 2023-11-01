//
// Created by joao on 31-10-2023.
//
#include <fstream>
#include "Request.h"

Request::Request(Student involvedStudent, std::string type, Class classe1, Class class2) {
    this->involvedStudent_ = involvedStudent;
    this->type_ = type;
    this->class_ = classe1;
    this->newClass_ = class2;
    this->timestamp_ = std::chrono::system_clock::now();
}

Request::Request(Student involvedStudent, std::string type, Class classe1) {
    this->involvedStudent_ = involvedStudent;
    this->type_ = type;
    this->class_ = classe1;
    this->newClass_ = Class("A","A");
    this->timestamp_ = std::chrono::system_clock::now();
}

Student Request::getRequest_student() {
    return this->involvedStudent_;
}
std::string Request::getRequest_type() {
    return this->type_;
}
Class Request::getRequest_class() {
    return this->class_;
}
Class Request::getRequest_newclass() {
    return this->newClass_;
}
std::chrono::system_clock::time_point Request::getTimestamp() {
    return this->timestamp_;
}

void Request::updateTimestamp() {
    this->timestamp_ = std::chrono::system_clock::now();
}




