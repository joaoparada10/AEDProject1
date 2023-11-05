/**
 * @file Student.h
 * @brief Header file for the Student class which holds
 * students information
 */
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Schedule.h"
#include "Class.h"

class Student {
private:
    std::string student_name;
    int student_code; /** Unique code that identifies each student */
    std::vector<Class> student_classes;/** All classes of one student*/
    std::vector<Schedule> student_schedule;/** The schedule of a student, a set of classes*/


public:
    Student();
    /**@brief Default constructor*/
    Student(int student_code, std::string student_name);
    bool operator==(const Student& other) const;
    bool operator<(const Student& other) const;
    /**@brief Returns the schedule's student's name*/
    std::string getStudent_name();
    /**@brief Returns the schedule's student's identification code*/
    [[nodiscard]] int getStudent_code() const;
    /**@brief Adds a class to the student´s schedule*/
    void addClass(const Class& student_class);
    std::vector<Class> &getClasses();
    /**@brief Removes a class from the student schedule*/
    void removeClass(const Class& class_of_student);
    /**@brief Adds a schedule to the student profile*/
    void addStudent_schedule(const std::vector<Schedule>& schedule);
    /**@brief Removes the student´s schedule*/
    void removeStudent_schedule(Schedule& schedule);
    /**@brief Removes the student´s schedules*/
    void removeStudent_schedules(const std::vector<Schedule>& schedule);
    std::vector<Schedule> &getStudent_schedule();
    /**@brief Returns the number of registered UCs of a student*/
    [[maybe_unused]] int getNumberOfRegisteredUCs();

};
#endif