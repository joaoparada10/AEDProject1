#include "Student.h"

Student::Student(){};
Student::Student(int student_code, std::string student_name){
    this->student_name = student_name;
    this->student_code = student_code;
}
std::string Student::getName() {
    return student_name;
}
 int Student::getStudent_code(){
    return student_code;
}
void Student::addClass(const Class student_class) {
    student_classes.push_back(student_class);
}



/*void Student::fillSchedule(const std::vector<Class>& attendedClasses) {
    for (const Class& attendedClass : attendedClasses) {
        studentSchedule.addClass(attendedClass);
    }
}*/
/*Schedule Student::getSchedule() {

    return studentSchedule;
}*/

std::unordered_map<int,Student> readStudentClassesCSV(const std::string& filename) {
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

                // Create a Student object and add it to the map

                if (studentMap.find(student_code) == studentMap.end()) {
                    // If student with the same code does not exist, create a new Student object.
                    studentMap[student_code] = Student(student_code, student_name);
                } else {
                    // A student with the same code already exists.
                    // You can handle this case here, for example, by updating the existing student.
                    // studentMap[student_code].update(student_name);
                }

                std::string class_key = uc_code + class_code;

                if (classes.find(class_key) != classes.end()) {
                    studentMap[student_code].addClass(classes[class_key]);
                }

            }

        }
        file.close();
    }
    return studentMap;
}

