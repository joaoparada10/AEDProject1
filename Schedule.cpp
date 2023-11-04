/**
 * @file Schedule.cpp
 * @brief Implementation of the Schedule class methods
 *
 */

#include "Schedule.h"

Schedule::Schedule()= default;
/**@brief Default constructor*/
Schedule::Schedule(std::string class_code, std::string uc_code, std::string weekday, double start_hour, double duration, std::string type) {
    this->class_code = class_code;
    this->uc_code = uc_code;
    this->weekday = weekday;
    this->start_hour = start_hour;
    this->duration = duration;
    this->type = type;

}
bool Schedule::operator==(const Schedule& other) const {
    return ((this->getClass_code() == other.getClass_code())
            && (this->getUc_code() == other.getUc_code())
            && (this->getWeekday() == other.getWeekday())
            && (this->getStart_hour() == other.getStart_hour())
            && (this->getDuration() == other.getDuration())
            && (this->getType() == other.getType()));
}

bool Schedule::operator<(const Schedule& other) const {
    static const std::map<std::string, int> weekdayOrder = {
            {"Monday", 1},
            {"Tuesday", 2},
            {"Wednesday", 3},
            {"Thursday", 4},
            {"Friday", 5}
    };

    int thisWeekdayOrder = weekdayOrder.at(this->getWeekday());
    int otherWeekdayOrder = weekdayOrder.at(other.getWeekday());

    if (thisWeekdayOrder < otherWeekdayOrder) {
        return true;  // This schedule's weekday comes before the other.
    } else if (thisWeekdayOrder > otherWeekdayOrder) {
        return false;  // This schedule's weekday comes after the other.
    } else {
        // Weekdays are the same, so use start time as a tiebreaker.
        return this->getStart_hour() < other.getStart_hour();
    }
}

/**@return Returns the class code*/
std::string Schedule::getClass_code() const {
    return class_code;
}
/**@return Returns the UC code*/
std::string Schedule::getUc_code() const {
    return uc_code;
}
/**@return Returns the weekday*/
std::string Schedule::getWeekday() const {
    return weekday;
}
/**@return Returns the starting hour of that class*/
double Schedule::getStart_hour() const {
    return start_hour;
}
/**@return Returns the duration of that class*/
double Schedule::getDuration() const {
    return duration;
}
/**@return Returns the type of the class*/
std::string Schedule::getType() const {
    return type;
}
