#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>

class Schedule {

public:
    bool operator==(const Schedule& other) const {
        return ((this->getClass_code() == other.getClass_code())
        && (this->getUc_code() == other.getUc_code())
        && (this->getWeekday() == other.getWeekday())
        && (this->getStart_hour() == other.getStart_hour())
        && (this->getDuration() == other.getDuration())
        && (this->getType() == other.getType()));
    }
    Schedule();
    Schedule(std::string class_code, std::string uc_code, std::string weekday, double start_hour, double duration, std::string type);
    [[nodiscard]] std::string getClass_code() const;
    [[nodiscard]] std::string getUc_code() const;
    [[nodiscard]] std::string getWeekday() const;
    [[nodiscard]] double getStart_hour() const;
    [[nodiscard]] double getDuration() const;
    [[nodiscard]] std::string getType() const;
private:
    std::string class_code;
    std::string uc_code;
    std::string weekday;
    double start_hour{};
    double duration{};
    std::string type;
};

#endif