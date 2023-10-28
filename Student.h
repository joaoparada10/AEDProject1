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
        void addClass(const Class student_class);
        void removeClass();
        void switchClass();


        };
std::unordered_map<int,Student> readStudentClassesCSV(const std::string& filename);

#endif