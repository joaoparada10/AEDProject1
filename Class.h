#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>

class Class {

    void setCode(const std::string& code);
    void setUcCode(const std::string& ucCode);
    void setWeekday(const std::string& weekday);
    void setStartHour(double startHour);
    void setDuration(double duration);
    void setType(const std::string& type);

public:
    Class(std::string  ClassCode, std::string  UcCode, std::string  Weekday, double StartHour, double Duration, std::string  Type);

    std::string getCode() const;

    std::string getUcCode() const;

    std::string getWeekday() const;

    double getStartHour() const;

    double getDuration() const;

    std::string getType() const;

private:
    std::string code;
    std::string ucCode;
    std::string weekday;
    double startHour;
    double duration;
    std::string type;

};
std::vector<Class> readClassesCSV(const std::string& filename);

#endif
