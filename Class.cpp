#include "Class.h"

#include <utility>

Class::Class(std::string  class_code, std::string  uc_code, std::string  weekday, double start_hour, double duration, std::string  type)
        : class_code(class_code), uc_code(std::move(uc_code)), weekday(std::move(weekday)), start_hour(start_hour), duration(duration), type(std::move(type)) {
}

std::vector<Class> readClassesCSV(const std::string& filename) {
    std::vector<Class> classes;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string class_code, uc_code, weekday, type;
            double start_hour, duration;

            if (std::getline(iss, class_code, ',') &&
                std::getline(iss, uc_code, ',') &&
                std::getline(iss, weekday, ',') &&
                iss >> start_hour && iss.get() == ',' &&
                iss >> duration && iss.get() == ',' &&
                std::getline(iss, type)){
                    classes.emplace_back(class_code, uc_code, weekday, start_hour, duration, type);
                }
        }

        file.close();
    }
    return classes;
}

std::string Class::getClass_code() const {
    return class_code;
}

std::string Class::getUc_code() const {
    return uc_code;
}

std::string Class::getWeekday() const {
    return weekday;
}

double Class::getStart_hour() const {
    return start_hour;
}

double Class::getDuration() const {
    return duration;
}

std::string Class::getType() const {
    return type;
}
Schedule getClass_schedule(){
    return
}

void Class::setClass_code(const std::string& newClass_code) {
    class_code = newClass_code;
}

void Class::setUc_code(const std::string& newUc_code) {
    uc_code = newUc_code;
}

void Class::setWeekday(const std::string& newWeekday) {
    weekday = newWeekday;
}

void Class::setStart_hour(double newStart_hour) {
    start_hour = newStart_hour;
}

void Class::setDuration(double newDuration) {
    duration = newDuration;
}

void Class::setType(const std::string& newType) {
    type = newType;
}
