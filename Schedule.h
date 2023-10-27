#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Class.h"

class Schedule{

public:
    Schedule();

    bool canAddClass(const Class& newClass);
    void addClass(const Class& newClass);
    void removeClass(const Class& classToRemove);
    void showSchedule() const;

private:
    std::vector<Class> classes;

};

#endif