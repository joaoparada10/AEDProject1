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
    bool operator==(const Class& other) const {
        return (this->getClass_key() == other.getClass_key());
    }
    [[nodiscard]] std::string getClass_code() const;
    [[nodiscard]] std::string getUc_code() const;
    [[nodiscard]] std::string getClass_key() const;
    void addClass_schedule(const Schedule &schedule);
    void removeClass_schedule(const Schedule &schedule);
    void addStudent(Student *studentPtr);
    void removeStudent(Student *studentPtr);
    [[nodiscard]] const std::vector<Schedule> &getSchedules() const;
    [[nodiscard]] std::vector<Student *> getStudents() const;
};

#endif
