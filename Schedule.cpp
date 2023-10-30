#include "Schedule.h"


Schedule::Schedule(std::string class_code, std::string uc_code, std::string weekday, double start_hour, double duration, std::string type) {
    this->class_code = class_code;
    this->uc_code = uc_code;
    this->weekday = weekday;
    this->start_hour = start_hour;
    this->duration = duration;
    this->type = type;

}

std::string Schedule::getClass_code() {
    return class_code;
}

std::string Schedule::getUc_code() {
    return uc_code;
}

std::string Schedule::getWeekday() {
    return weekday;
}

double Schedule::getStart_hour() {
    return start_hour;
}

double Schedule::getDuration() {
    return duration;
}

std::string Schedule::getType() {
    return type;
}


