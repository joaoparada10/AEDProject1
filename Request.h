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
    Student involvedStudent_; // estudante envolvido na request
    std::string type_; // tipo de request feita, (add, remove,switch)
    Class class_; // class a qual queremos adicionar/remover/ sair de para trocar o aluno
    Class newClass_; // class para a qual queremos trocar o aluno no caso de um switch
    std::chrono::system_clock::time_point timestamp_;
public:
    Request(Student involvedStudent, std::string type, Class classe1); // so pode acontecer um add ou um remove
    Request(Student involvedStudent, std::string type, Class classe1, Class class2); // vai acontecer um switch, um switch so pode acontcer se for entre 2 turmas da mesma uc ou entre ucs dif
    Student getRequest_student();
    std::string getRequest_type();
    Class getRequest_class();
    Class getRequest_newclass();
    std::chrono::system_clock::time_point getTimestamp();
    void undoLast_request();
    void printTimestamp() const {
        std::time_t timestamp_time = std::chrono::system_clock::to_time_t(timestamp_);
        std::tm* timeinfo = std::localtime(&timestamp_time);
        std::cout << "On " << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S") << std::endl;
    }
    void updateTimestamp();
};




#endif