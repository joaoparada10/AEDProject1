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

void Class::addClass_schedule(const Schedule &schedule) {
    class_schedules.push_back(schedule);
}

void Class::addStudent(Student *studentPtr) {
    students_in_class.push_back(studentPtr);
}

std::vector<Student *> Class::getStudents() const {
    return students_in_class;
}

const std::vector<Schedule> &Class::getSchedules() const {
    return class_schedules;
}