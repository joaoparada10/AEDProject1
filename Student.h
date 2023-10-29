#ifndef STUDENT_H
#define STUDENT_H

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

class Student{
    private:
        std::string student_name;
        int student_code;
        std::vector<Class> student_classes;

    public:
        Student();
        Student(int student_code, std::string student_name);
        std::string getName();
        int getStudent_code();

        void addUc();
        void addClass(Class student_class);
        void removeClass();
        void switchClass();


        };

#endif