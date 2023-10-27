#include <iostream>
#include "Class.h"
#include "Student.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::unordered_map<int,Student> studentMap = readStudentClassesCSV("/home/joao/AED23/AEDProject1/Data/schedule/student_classes.csv");
    std::vector<Class> classes = readClassesCSV("/home/joao/AED23/AEDProject1/Data/schedule/classes.csv");
    for (Class &c: classes) {
        std::cout << "Class Code: " << c.getClass_code() << std::endl;
        std::cout << "UC Code: " << c.getUc_code() << std::endl;
        std::cout << "Weekday: " << c.getWeekday() << std::endl;
        std::cout << "Start Hour: " << c.getStart_hour() << std::endl;
        std::cout << "Duration: " << c.getDuration() << std::endl;
        std::cout << "Type: " << c.getType() << std::endl;

    }
    for (const auto& pair : studentMap) {
        int student_code = pair.first;
        const Student& student = pair.second;

        std::cout << "Student Code: " << student_code << std::endl;
        std::cout << "Student Name: " << student.getName() << std::endl;
        std::cout << "UC Code: " << student.getUcCode() << std::endl;
        std::cout << "Class Code: " << student.getClassCode() << std::endl;

    }

        return 0;

}
