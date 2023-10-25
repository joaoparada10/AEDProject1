#include "Class.h"

#include <utility>

Class::Class(std::string  code, std::string  ucCode, std::string  weekday, double startHour, double duration, std::string  type)
        : code(code), ucCode(std::move(ucCode)), weekday(std::move(weekday)), startHour(startHour), duration(duration), type(std::move(type)) {
}

std::vector<Class> readClassesCSV(const std::string& filename) {
    std::vector<Class> classes;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string code, ucCode, weekday, type;
            double startHour, duration;

            if (std::getline(iss, code, ',') &&
                std::getline(iss, ucCode, ',') &&
                std::getline(iss, weekday, ',') &&
                iss >> startHour && iss.get() == ',' &&
                iss >> duration && iss.get() == ',' &&
                std::getline(iss, type)){
                    classes.emplace_back(code, ucCode, weekday, startHour, duration, type);
                }
        }

        file.close();
    }
    return classes;
}

std::string Class::getCode() const {
    return code;
}

std::string Class::getUcCode() const {
    return ucCode;
}

std::string Class::getWeekday() const {
    return weekday;
}

double Class::getStartHour() const {
    return startHour;
}

double Class::getDuration() const {
    return duration;
}

std::string Class::getType() const {
    return type;
}

void Class::setCode(const std::string& newCode) {
    code = newCode;
}

void Class::setUcCode(const std::string& newUcCode) {
    ucCode = newUcCode;
}

void Class::setWeekday(const std::string& newWeekday) {
    weekday = newWeekday;
}

void Class::setStartHour(double newStartHour) {
    startHour = newStartHour;
}

void Class::setDuration(double newDuration) {
    duration = newDuration;
}

void Class::setType(const std::string& newType) {
    type = newType;
}
