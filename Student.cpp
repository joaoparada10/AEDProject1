/**
 * @file Student.cpp
 * @brief Implementation of the Student class methods
 */

#include <algorithm>
#include "Student.h"
#include "Class.h"
Student::Student()= default;

Student::Student(int student_code, std::string student_name) {
    this->student_name = student_name;
    this->student_code = student_code;
}

bool Student::operator<(const Student& other) const {
    return this->student_name < other.student_name;
}

std::string Student::getStudent_name() {
    return this->student_name;
}
/**@param class_of_student A class*/
void Student::removeClass(const Class& class_of_student) {
    for (auto it = student_classes.begin(); it != student_classes.end(); ++it) {
        if (*it == class_of_student) {
            student_classes.erase(it);
            break;
        }
    }
}
int Student::getStudent_code() const {
    return this->student_code;
}
/**@param student_class A class*/
void Student::addClass(const Class& student_class) {
    this->student_classes.push_back(student_class);
}

std::vector<Class> &Student::getClasses() {
    return student_classes;
}
/**@param schedule A vector with the student's schedule*/
void Student::addStudent_schedule(const std::vector<Schedule>& schedule) {
    for (const Schedule& sch: schedule)
        student_schedule.push_back(sch);
}
/**@param schedule A schedule*/
void Student::removeStudent_schedule(Schedule &schedule) {
    auto it = std::find(student_schedule.begin(), student_schedule.end(), schedule);
    if (it != student_schedule.end()) {
        student_schedule.erase(it);
    }
}
/**@param schedule A schedule*/
void Student::removeStudent_schedules(const std::vector<Schedule>& schedule) {
    for (const Schedule& schedule2 : schedule) {
        auto it = std::find(student_schedule.begin(), student_schedule.end(), schedule2);
        if (it != student_schedule.end()) {
            student_schedule.erase(it);
        }
    }
}
/**@return Returns the student's schedule*/
std::vector<Schedule> &Student::getStudent_schedule() {
    return student_schedule;
}
/**@return Returns the number of registered UCs of the student*/
int Student::getNumberOfRegisteredUCs() {
    return student_classes.size();
    }



