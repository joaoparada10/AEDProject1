#include "Class.h"

#include <utility>

Class::Class(){};

Class::Class(std::string  class_code, std::string  uc_code)
        : class_code(class_code), uc_code(std::move(uc_code)) {
}
/*bool Class::operator==(const Class& other) const {
    return (class_code == other.class_code && uc_code == other.uc_code);
}*/
std::unordered_map<std::string,Class> classMap(const std::string& filename){ // lê o ficheiro classes_per_uc.csv
    std::unordered_map<std::string, Class> classMap;
    std::vector<Class> class_list;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        std::getline(file,line);
        while(std::getline(file,line)) {
            std::istringstream iss(line);
            std::string uc_code, class_code;

            if (std::getline(iss, uc_code, ',') &&
                std::getline(iss,class_code, '\r')){
                class_list.emplace_back(class_code, uc_code);
            }
        }

    }
    for (const Class& cls : class_list) {
        // Use a unique key that combines uc_code and class_code
        std::string key = cls.getUc_code() + cls.getClass_code();
        classMap[key] = cls;
    }
    return classMap;
}


std::unordered_map<std::string, Class> readClassesCSV(const std::string& filename) {      //lê classes.csv e preenche os horários de cada class.
    std::unordered_map<std::string, Class> classes = classMap(
            "/home/joao/AED23/AEDProject1/Data/schedule/classes_per_uc.csv");
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
                std::getline(iss, type, '\r')) {
                std::string key = uc_code + class_code;


                if (classes.find(key) != classes.end()) {
                    // Update the schedule for the matching class
                    Schedule class_schedule(weekday, start_hour, duration, type);
                    classes[key].addSchedule(class_schedule );
                }


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
void Class::addSchedule(const Schedule& schedule) {
            class_schedules.push_back(schedule);
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

