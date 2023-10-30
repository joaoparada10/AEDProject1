#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Schedule.h"
#include <string>
#include <vector>  // Include this for a smart pointer like std::shared_ptr

class Student;
class Class {
private:

    /*void setClass_code(const std::string& class_code);
    void setUc_code(const std::string& uc_code);*/
    std::vector<Student*> students_in_class;
    std::vector<Schedule> class_schedules;
    std::string uc_code;
    std::string class_code;

public:
    Class();
    Class(std::string  class_code, std::string  uc_code);
    /*bool operator==(const Class& other) const;*/
    std::string getClass_code() const;

    std::string getUc_code() const;
    void addClass_schedule(const Schedule& schedule);
    void addStudent(Student* studentPtr);
    const std::vector<Schedule>& getSchedules() const;
    std::vector<Student *> getStudents() const;
};
/*std::vector<Class> classes_per_uc(const std::string& filename);*/
void printClassSchedules(const std::unordered_map<std::string, Class> classMap);



#endif
