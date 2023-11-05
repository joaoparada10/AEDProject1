/**
 * @file Schedule.h
 * @brief Header file for the Schedule class, responsible to store information
 * about each class of each student
 */

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <map>

class Schedule {

public:
    /**@brief Default constructor*/
    Schedule();
    /**@brief Parameterized constructor*/
    Schedule(std::string class_code, std::string uc_code, std::string weekday, double start_hour, double duration,
             std::string type);
    /**@brief operator == overload, making it possible to see if 2 schedules are the same*/
    bool operator==(const Schedule &other) const;
    /**@brief operator < overload, making it possible to sort schedules chronologically*/
    bool operator<(const Schedule &other) const;
    /**@brief Returns the Class identification code for a class*/
    [[nodiscard]] std::string getClass_code() const;
    /**@brief Returns the UC code of a class*/
    [[nodiscard]] std::string getUc_code() const;
    /**@brief Returns the weekday of the class*/
    [[nodiscard]] std::string getWeekday() const;
    /**@brief Returns the starting hour of a class*/
    [[nodiscard]] double getStart_hour() const;
    /**@brief Returns the duration of a class*/
    [[nodiscard]] double getDuration() const;
    /**@brief Returns the type of a class*/
    [[nodiscard]] std::string getType() const;

private:
    std::string class_code;/** Unique code for each class*/
    std::string uc_code; /** Unique code for each UC*/
    std::string weekday;/** The day of the week where the class is scheduled*/
    double start_hour{};/** The starting hour of a class*/
    double duration{}; /** Duration of a class in hours*/
    std::string type; /** Type of class extends within T,TP or PL*/
};

#endif