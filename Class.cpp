/**
 * @file Class.cpp
 * @brief Implementation for the Class class methods
 */



#include <algorithm>
#include "Class.h"
#include "Student.h"

Class::Class() = default;

Class::Class(std::string class_code, std::string uc_code)
        : class_code(class_code), uc_code(std::move(uc_code)) {
}

std::string Class::getClass_code() const {
    return class_code;
}
std::string Class::getUc_code() const {
    return uc_code;
}
/**@return Class key (uc code + class code)*/
std::string Class::getClass_key() const {
    return uc_code + class_code;
}

void Class::addClass_schedule(const Schedule &schedule) {
    class_schedules.push_back(schedule);
}
/**@param schedule A schedule*/
void Class::removeClass_schedule(const Schedule& schedule) {
    auto it = std::find(class_schedules.begin(), class_schedules.end(), schedule);
    if (it != class_schedules.end()) {
        class_schedules.erase(it);
    }
}
/**@param studentPtr A pointer to a student*/
void Class::addStudent(Student *studentPtr) {
    students_in_class.push_back(studentPtr);
}
/**@param studentPtr A pointer to a student*/
void Class::removeStudent(Student *studentPtr){
    for (auto it = students_in_class.begin(); it != students_in_class.end(); ++it) {
        if (*it == studentPtr) {
            students_in_class.erase(it);
            break;
        }
    }
}
std::vector<Student *> Class::getStudents() const {
    return students_in_class;
}

const std::vector<Schedule> &Class::getSchedules() const {
    return class_schedules;
}

int Class::getStudent_count() const {

    return students_in_class.size();
}


