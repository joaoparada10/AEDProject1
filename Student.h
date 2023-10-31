#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Schedule.h"
#include "Class.h"
/**
 * ... student class ...
 */
class Student {
private:
    std::string student_name;
    int student_code;
    std::vector<Class> student_classes;
    std::vector<Schedule> student_schedule;

public:
    Student();
    Student(int student_code, std::string student_name);
    bool operator==(const Student& other) const {
        return (this->getStudent_code() == other.getStudent_code());
    }
    bool operator<(const Student& other) const;
    std::string getStudent_name();
    [[nodiscard]] int getStudent_code() const;
    void addClass(const Class& student_class);
    std::vector<Class> &getClasses();
    void removeClass(const Class& class_of_student);
    void switchClass();
    void addStudent_schedule(const std::vector<Schedule>& schedule);
    void removeStudent_schedule(Schedule& schedule);
    std::vector<Schedule> &getStudent_schedule();
};
#endif