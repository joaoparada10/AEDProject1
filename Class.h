/**
 * @file Class.h
 * @brief Header file for the Class class, each class object has an unique combination of uc_code + class_code
 */


#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include "Schedule.h"

class Student;
class Class {
private:
    std::vector<Student *> students_in_class;/** All students in the class*/
    std::vector<Schedule> class_schedules; /** The schedule of the class*/
    std::string uc_code;/** Unique code for each uc */
    std::string class_code;/** Unique code for each class */

public:
    /**@brief Default constructor*/
    Class();
    /**@brief Parameterized constructor*/
    Class(std::string class_code, std::string uc_code);
    /**@brief == overload, making it possible to check if 2 classes are the same*/
    bool operator==(const Class& other) const {
        return (this->getClass_key() == other.getClass_key());
    }
    /**@brief Returns the class code */
    [[nodiscard]] std::string getClass_code() const;
    /**@brief Returns the UC identification code*/
    [[nodiscard]] std::string getUc_code() const;
    /**@brief Returns the Class key ( uc_code + class_code)*/
    [[nodiscard]] std::string getClass_key() const;
    /**@brief Returns the amount of students in a class*/
    [[nodiscard]] int getStudent_count() const;
    /**@brief Adds a class to the student's schedule*/
    void addClass_schedule(const Schedule &schedule);
    /**@brief Removes a class from the student's schedule*/
    [[maybe_unused]] void removeClass_schedule(const Schedule &schedule);
    /**@brief Adds a student to one class*/
    void addStudent(Student *studentPtr);
    /**@brief Removes a student from one class*/
    void removeStudent(Student *studentPtr);
    /**@brief Returns a class schedule's*/
    [[nodiscard]] const std::vector<Schedule> &getSchedules() const;
    /**@brief Returns all students in the class*/
    [[nodiscard]] std::vector<Student *> getStudents() const;
};

#endif
