#include "Schedule.h"


Schedule::Schedule() {
    classes = std::vector<Class>();
}

bool Schedule::canAddClass(const Class &newClass) {

}

void Schedule::addClass(const Class &newClass) {
    classes.emplace_back(newClass);

}

void Schedule::removeClass(const Class &classToRemove) {
    auto it = std::remove(classes.begin(), classes.end(), classToRemove);
    classes.erase(it, classes.end());
}

void Schedule::showSchedule() const {
    if (classes.empty()) {
        std::cout << "Schedule is empty." << std::endl;
        return;
    }

    std::cout << "Class Schedule:" << std::endl;
    for (const Class& classInSchedule : classes) {
        std::cout << "Class Code: " << classInSchedule.getClassCode() << std::endl;
        std::cout << "UC Code: " << classInSchedule.getUcCode() << std::endl;
        std::cout << "Weekday: " << classInSchedule.getWeekday() << std::endl;
        std::cout << "Start Hour: " << classInSchedule.getStartHour() << std::endl;
        std::cout << "Duration: " << classInSchedule.getDuration() << " hours" << std::endl;
        std::cout << "Type: " << classInSchedule.getType() << std::endl;
        std::cout << "--------------------------" << std::endl;
    }

}




