#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Schedule.h"

class Class {

    void setClass_code(const std::string& class_code);
    void setUc_code(const std::string& uc_code);
    void setWeekday(const std::string& weekday);
    void setStart_hour(double start_hour);
    void setDuration(double duration);
    void setType(const std::string& type);

public:
    Class(std::string  class_code, std::string  uc_code, std::string  weekday,
          double start_hour, double duration, std::string  Type);

    std::string getClass_code() const;

    std::string getUc_code() const;
    std::string getWeekday() const;

    double getStart_hour() const;

    double getDuration() const;

    std::string getType() const;
    Schedule getClass_schedule();

private:
    std::string class_code;
    std::string uc_code;
    std::string weekday;
    double start_hour;
    double duration;
    std::string type;

};
std::vector<Class> readClassesCSV(const std::string& filename);


#endif
