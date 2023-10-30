#include "Filereader.h"
#include "Datamanager.h"
#include <sstream>

std::unordered_map<std::string, Class>
Filereader::classMap(const std::string &filename) {
    std::unordered_map<std::string, Class> classMap;
    std::vector<Class> class_list;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string uc_code, class_code;

            if (std::getline(iss, uc_code, ',') &&
                std::getline(iss, class_code, '\r')) {
                class_list.emplace_back(class_code, uc_code);
            }
        }
    }
    for (const Class &cls: class_list) {
        std::string key = cls.getClass_key();
        classMap[key] = cls;
    }
    return classMap;
}

std::unordered_map<std::string, Class>
Filereader::readClassesCSV(const std::string &filename) {
    std::unordered_map<std::string, Class> classes = Datamanager::empty_classes_map;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string class_code, uc_code, weekday, type;
            double start_hour, duration;
            if (std::getline(iss, class_code, ',') &&
                std::getline(iss, uc_code, ',') &&
                std::getline(iss, weekday, ',') &&
                iss >> start_hour && iss.get() == ',' &&
                iss >> duration && iss.get() == ',' &&
                std::getline(iss, type, '\r')) {
                std::string key = uc_code + class_code;
                if (classes.find(key) != classes.end()) {
                    Schedule class_schedule(class_code, uc_code, weekday, start_hour, duration, type);
                    classes[key].addClass_schedule(class_schedule);
                }
            }
        }
        file.close();
    }
    return classes;
}

std::unordered_map<int, Student> Filereader::readStudentClassesCSV(const std::string &filename) {
    std::unordered_map<std::string, Class> classes = Datamanager::classes_map;
    std::unordered_map<int, Student> studentMap;
    std::ifstream file(filename);
    if (file.is_open()) {

        std::string line;
        while (std::getline(file, line)) {
            // Skip the header line
            if (line.find("StudentCode,StudentName,UcCode,ClassCode") != std::string::npos) {
                continue;
            }
            int student_code;
            std::string student_name, uc_code, class_code;
            std::istringstream iss(line);
            if (iss >> student_code && iss.get() == ',' &&
                std::getline(iss, student_name, ',') &&
                std::getline(iss, uc_code, ',') &&
                std::getline(iss, class_code, '\r')) {

                if (studentMap.find(student_code) == studentMap.end()) {
                    studentMap[student_code] = Student(student_code, student_name);
                }
                std::string class_key = uc_code + class_code;

                if (classes.find(class_key) != classes.end()) {
                    studentMap[student_code].addStudent_schedule(classes[class_key].getSchedules());
                    studentMap[student_code].addClass(classes[class_key]);
                    Datamanager::classes_map[class_key].addStudent(&studentMap[student_code]);
                }
            }
        }
        file.close();
    }
    return studentMap;
}