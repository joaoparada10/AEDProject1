//
// Created by joao on 31-10-2023.
//
#include "Request.h"

Request::Request(Student involvedStudent, std::string type, Class classe1, Class class2) {
    this->involvedStudent_ = involvedStudent;
    this->type_ = type;
    this->class_ = classe1;
    this->newClass_ = class2;
}

Request::Request(Student involvedStudent, std::string type, Class classe1) {
    this->involvedStudent_ = involvedStudent;
    this->type_ = type;
    this->class_ = classe1;
    this->newClass_ = Class("A","A");
}

void Request::processRequest() {

    if(newClass_.getClass_code() == "A"){ // significa que estamos a usar a dummyClass entao vai acontecer um add ou um remove

        if(type_ == "Add"){

        }

        if(type_ == "Remove"){
            involvedStudent_;
        }

        else{
            std::cout<< "Invalid Option" << std::endl;
            std::cout<< "Please try again" << std::endl;
        }

    }
    else{ // vai acontecer um switch entre duas classes ( ou demos o switch de uma cadeira ou de uma turma)

    }
}