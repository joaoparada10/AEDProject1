#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "Schedule.h"
#include "Class.h"
#include <string>
#include <vector>
#include "Student.h"

class Request
{
private:
    Student involvedStudent_; // estudante envolvido na request
    std::string type_; // tipo de request feita, (add, remove,switch)
    Class class_; // class a qual queremos adicionar/remover/ sair de para trocar o aluno
    Class newClass_; // class para a qual queremos trocar o aluno no caso de um switch

public:
    Request(Student involvedStudent, std::string type, Class classe1); // so pode acontecer um add ou um remove
    Request(Student involvedStudent, std::string type, Class classe1, Class class2); // vai acontecer um switch, um switch so pode acontcer se for entre 2 turmas da mesma uc ou entre ucs dif
    void processRequest();
};




#endif