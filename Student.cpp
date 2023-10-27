#include "Student.h"

Student::Student(){};
Student::Student(int student_code, std::string student_name, std::string uc_code, std::string class_code){
    this->student_name = student_name;
    this->uc_code = uc_code;
    this->class_code = class_code;
    this->student_code = student_code;
}
std::string Student::getName(){
    return student_name;
}

 int Student::getStudent_code(){
    return student_code;
}
Schedule Student::getSchedule() {
    return studentSchedule;
}
std::unordered_map<int,Student> readStudentClassesCSV(const std::string& filename){
    std::unordered_map<int,Student> studentMap;
    Schedule studentSchedule;
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
                std::getline(iss, class_code, ','))

                // Create a Student object and add it to the map
                studentMap[student_code] = Student(student_code, student_name, uc_code, class_code);

        }
        file.close();
    }
return studentMap;
}

