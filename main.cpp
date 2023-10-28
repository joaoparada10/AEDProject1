#include <iostream>
#include "Class.h"
#include "Student.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::unordered_map<std::string, Class> classes = classMap("/home/joao/AED23/AEDProject1/Data/schedule/classes_per_uc.csv");

    std::unordered_map<std::string, Class> classMap = readClassesCSV("/home/joao/AED23/AEDProject1/Data/schedule/classes.csv");
    printClassSchedules(classMap);
    std::unordered_map<int,Student> studentMap = readStudentClassesCSV("/home/joao/AED23/AEDProject1/Data/schedule/students_classes.csv");


    for (const auto& pair : studentMap) {
        Student student = pair.second;

        std::cout << "Student Code: " << student.getStudent_code() << std::endl;
        std::cout << "Student Name: " << student.getName() << std::endl;

    }

        return 0;

}
