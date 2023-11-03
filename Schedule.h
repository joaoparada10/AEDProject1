#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <map>

class Schedule {

public:
    Schedule();
    Schedule(std::string class_code, std::string uc_code, std::string weekday, double start_hour, double duration, std::string type);
    bool operator==(const Schedule& other) const;
    bool operator<(const Schedule& other) const;
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