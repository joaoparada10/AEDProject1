#ifndef SCHEDULE_H
#define SCHEDULE_H


#include <string>

class Schedule {

public:
    Schedule(std::string class_code, std::string uc_code, std::string weekday, double start_hour, double duration, std::string type);
    std::string getClass_code();
    std::string getUc_code();
    std::string getWeekday();
    double getStart_hour();
    double getDuration();
    std::string getType();
private:
    std::string class_code;
    std::string uc_code;
    std::string weekday;
    double start_hour;
    double duration;
    std::string type;
};

#endif