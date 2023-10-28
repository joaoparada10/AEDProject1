#include "Schedule.h"


Schedule::Schedule(std::string weekday, double start_hour, double duration, std::string type){
    this->weekday = weekday;
    this->start_hour = start_hour;
    this->duration = duration;
    this->type = type;
}
/*Schedule::Schedule() {
    classes = std::vector<Class>();
}


bool Schedule::canAddClass(const Class &newClass) {

}*/
std::string Schedule::getWeekday(){
    return weekday;
}
double Schedule::getStart_hour() {
    return start_hour;
}
double Schedule::getDuration(){
    return duration;
}
std::string Schedule::getType(){
    return type;
}

/*void Schedule::addClass(const Class &newClass) {
    classes.emplace_back(newClass);

}*/

/*void Schedule::removeClass(const Class &classToRemove) {
    classes.erase(std::remove(classes.begin(), classes.end(), classToRemove), classes.end());
}*/

/*void Schedule::showSchedule() const {
    if (classes.empty()) {
        std::cout << "Schedule is empty." << std::endl;
        return;
    }

    std::cout << "Class Schedule:" << std::endl;
    for (const Class& classInSchedule : classes) {
        std::cout << "Class Code: " << classInSchedule.getClass_code() << std::endl;
        std::cout << "UC Code: " << classInSchedule.getUc_code() << std::endl;
        std::cout << "Weekday: " << classInSchedule.getWeekday() << std::endl;
        std::cout << "Start Hour: " << classInSchedule.getStart_hour() << std::endl;
        std::cout << "Duration: " << classInSchedule.getDuration() << " hours" << std::endl;
        std::cout << "Type: " << classInSchedule.getType() << std::endl;
        std::cout << "--------------------------" << std::endl;
    }

}
*/



