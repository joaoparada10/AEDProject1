#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <algorithm>
#include <iostream>

class Schedule{

public:
    Schedule(std::string weekday,double start_hour,double duration,std::string type);
    std::string getWeekday();
    double getStart_hour();
    double getDuration();
    std::string getType();

    /*bool canAddClass(const Class& newClass);
    void addClass(const Class& newClass);
    void removeClass(const Class& classToRemove);*/
    /*void showSchedule() const;*/

private:
    std::string weekday;
    double start_hour;
    double duration;
    std::string type;
    /*std::vector<Class> classes;*/

};

#endif