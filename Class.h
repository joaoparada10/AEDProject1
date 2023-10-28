#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Schedule.h"
#include <list>

class Class {
private:

    /*void setClass_code(const std::string& class_code);
    void setUc_code(const std::string& uc_code);*/
    std::vector<Schedule> class_schedules;

    std::string uc_code;
    std::string class_code;

public:
    Class();
    Class(std::string  class_code, std::string  uc_code);
    /*bool operator==(const Class& other) const;*/
    std::string getClass_code() const;

    std::string getUc_code() const;
    void addSchedule(const Schedule& schedule);

    const std::vector<Schedule>& getSchedules() const;
};
/*std::vector<Class> classes_per_uc(const std::string& filename);*/
std::unordered_map<std::string,Class> classMap(const std::string& filename);
std::unordered_map<std::string, Class>readClassesCSV(const std::string& filename);
void printClassSchedules(const std::unordered_map<std::string, Class> classMap);



#endif
