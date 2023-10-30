#include "Student.h"
#include "Class.h"
Student::Student()= default;

Student::Student(int student_code, std::string student_name) {
    this->student_name = student_name;
    this->student_code = student_code;
}

bool Student::operator<(const Student& other) const {
    return student_name < other.student_name;
}

std::string Student::getStudent_name() {
    return student_name;
}

int Student::getStudent_code() const {
    return student_code;
}

void Student::addClass(const Class& student_class) {
    student_classes.push_back(student_class);
}

std::vector<Class> &Student::getClasses() {
    return student_classes;
}

void Student::addStudent_schedule(const std::vector<Schedule>& schedule) {
    for (const Schedule& sch: schedule)
        student_schedule.push_back(sch);
}

std::vector<Schedule> &Student::getStudent_schedule() {
    return student_schedule;
}