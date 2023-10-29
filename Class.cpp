#include "Class.h"
#include "Student.h"

#include <utility>

Class::Class(){};

Class::Class(std::string  class_code, std::string  uc_code)
        : class_code(class_code), uc_code(std::move(uc_code)) {
}
/*bool Class::operator==(const Class& other) const {
    return (class_code == other.class_code && uc_code == other.uc_code);
}*/

std::string Class::getClass_code() const {
    return class_code;
}

std::string Class::getUc_code() const {
    return uc_code;
}
void Class::addSchedule(const Schedule& schedule) {
            class_schedules.push_back(schedule);
        }
void Class::addStudent(Student* studentPtr){
    students_in_class.push_back(studentPtr);
}


const std::vector<Schedule>& Class::getSchedules() const {
    return class_schedules;
        }

void printClassSchedules(const std::unordered_map<std::string, Class> classMap) {
    for (const auto& entry : classMap) {
        const Class& cls = entry.second; // Access the class object

        std::cout << "Class: " << cls.getClass_code() << " (" << cls.getUc_code() << ")" << std::endl;

        const std::vector<Schedule>& schedules = cls.getSchedules();
        for (Schedule schedule : schedules) {
            std::cout << "Schedule Information:" << std::endl;
            std::cout << "Weekday: " << schedule.getWeekday() << std::endl;
            std::cout << "Start Time: " << schedule.getStart_hour() << std::endl;
            std::cout << "Duration: " << schedule.getDuration() << std::endl;
            std::cout << "Type: " << schedule.getType() << std::endl;
            std::cout << std::endl;
        }
    }
}
/*void Class::setClass_code(const std::string& newClass_code) {
    class_code = newClass_code;
}

void Class::setUc_code(const std::string& newUc_code) {
    uc_code = newUc_code;
}
*/

