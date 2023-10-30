#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include "Schedule.h"

class Student;
class Class {
private:
    std::vector<Student *> students_in_class;
    std::vector<Schedule> class_schedules;
    std::string uc_code;
    std::string class_code;

public:
    Class();
    Class(std::string class_code, std::string uc_code);
    [[nodiscard]] std::string getClass_code() const;
    [[nodiscard]] std::string getUc_code() const;
    void addClass_schedule(const Schedule &schedule);
    void addStudent(Student *studentPtr);
    [[nodiscard]] const std::vector<Schedule> &getSchedules() const;
    [[nodiscard]] std::vector<Student *> getStudents() const;
};

#endif
