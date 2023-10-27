#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Class.h"
#include "Schedule.h"

class Student{
    private:
        std::string student_name;
        std::string uc_code;
        std::string class_code;
        int student_code;
        std::vector<Class> student_classes;
        Schedule studentSchedule;

    public:
        Student();
        Student(int student_code, std::string student_name, std::string uc_code, std::string class_code);
        std::string getName();
        int getStudent_code();

        void addUc();
        void addClass();
        void removeClass();
        void switchClass();
        Schedule getSchedule();


        };
std::unordered_map<int,Student> readStudentClassesCSV(const std::string& filename);

#endif