#include <iostream>
#include "Class.h"
#include "Student.h"
#include "Datamanager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::unordered_map<std::string, Class> classes = Datamanager::getEmpty_classes_map();
    std::unordered_map<std::string, Class> classMap = Datamanager::getClasses_map();
    printClassSchedules(classMap);
    std::unordered_map<int,Student> studentMap = Datamanager::getStudent_map();

    for (const auto& pair : studentMap) {
        Student student = pair.second;

        std::cout << "Student Code: " << student.getStudent_code() << std::endl;
        std::cout << "Student Name: " << student.getName() << std::endl;

    }

        return 0;

}
