#include "Filereader.h"
#include <sstream>

std::unordered_map<std::string,Class> Filereader::classMap(const std::string& filename){ // lê o ficheiro classes_per_uc.csv
    std::unordered_map<std::string, Class> classMap;
    std::vector<Class> class_list;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        std::getline(file,line);
        while(std::getline(file,line)) {
            std::istringstream iss(line);
            std::string uc_code, class_code;

            if (std::getline(iss, uc_code, ',') &&
                std::getline(iss,class_code, '\r')){
                class_list.emplace_back(class_code, uc_code);
            }
        }

    }
    for (const Class& cls : class_list) {
        // Use a unique key that combines uc_code and class_code
        std::string key = cls.getUc_code() + cls.getClass_code();
        classMap[key] = cls;
    }
    return classMap;
}

std::unordered_map<std::string, Class> Filereader::readClassesCSV(const std::string& filename) {      //lê classes.csv e preenche os horários de cada class.
    std::unordered_map<std::string, Class> classes = classMap(
            "/home/joao/AED23/AEDProject1/Data/schedule/classes_per_uc.csv");
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
                    // Update the schedule for the matching class
                    Schedule class_schedule(weekday, start_hour, duration, type);
                    classes[key].addSchedule(class_schedule );
                }
            }
        }
        file.close();
    }
    return classes;
}

std::unordered_map<int,Student> Filereader::readStudentClassesCSV(const std::string& filename) {
    std::unordered_map<std::string, Class> classes = readClassesCSV("/home/joao/AED23/AEDProject1/Data/schedule/classes.csv");
    std::unordered_map<int, Student> studentMap;
    std::ifstream file(filename);
    if (file.is_open()) {

        std::string line;
        while (std::getline(file, line)) {
            // Skip the header line if necessary
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

                if (classes.find(class_key) != classes.end()){
                    studentMap[student_code].addClass(classes[class_key]);
                    /*classes[class_key].addStudent(studentMap[student_code]);*/}

            }
        }
        file.close();
    }
    return studentMap;
}
std::unordered_map<std::string, Class> Filereader::getEmpty_classes_map(const std::string &filename) {
    return classMap(filename);
}
std::unordered_map<std::string, Class> Filereader::getClasses_map(const std::string &filename) {
    return readClassesCSV(filename);
}