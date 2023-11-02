#include <map>
#include <values.h>
#include "Datamanager.h"
#include "Student.h"
#include "Request.h"
std::unordered_map<std::string, Class> Datamanager::empty_classes_map;
std::unordered_map<std::string, Class> Datamanager::classes_map;
std::unordered_map<int, Student> Datamanager::students_map;
std::stack<Request> Datamanager::request_log;
std::queue<Request> Datamanager::requests;
int Datamanager::class_cap  = 26;

std::unordered_map<std::string, Class> Datamanager::getEmpty_classes_map() {
    empty_classes_map = Filereader::classMap("../Data/schedule/classes_per_uc.csv");
    return empty_classes_map;
}

std::unordered_map<std::string, Class> Datamanager::getClasses_map() {
    classes_map = Filereader::readClassesCSV("../Data/schedule/classes.csv");
    return classes_map;
}

std::unordered_map<int, Student> Datamanager::getStudent_map() {
    students_map = Filereader::readStudentClassesCSV("../Data/schedule/students_classes.csv");
    return students_map;
}

void Datamanager::consultStudent_schedule() {
    int student_code;
    std::cout << "Enter student code: ";
    std::cin >> student_code;

    if (students_map.find(student_code) == students_map.end()) {
        std::cout << "Student with code " << student_code << " not found." << std::endl;
        return;
    }
    Student student = students_map[student_code];
    const std::vector<Schedule> &student_schedule = student.getStudent_schedule();

    if (student_schedule.empty()) {
        std::cout << "Student with code " << student_code << " has no schedule." << std::endl;
    } else {
        std::cout << "Student Schedule for : " << student.getStudent_name() << std::endl;
        for (const Schedule& schedule: student_schedule) {
            std::cout << "Class: " << schedule.getClass_code() << std::endl;
            std::cout << "UC: " << schedule.getUc_code() << std::endl;
            std::cout << "Weekday: " << schedule.getWeekday() << std::endl;
            std::cout << "Start Hour: " << schedule.getStart_hour() << std::endl;
            std::cout << "Duration: " << schedule.getDuration() << std::endl;
            std::cout << "Type: " << schedule.getType() << std::endl;
            std::cout << std::endl;
        }
    }
}

void Datamanager::consultClass_schedule() {
    std::string class_code;
    std::cout << "Enter class: ";
    std::cin >> class_code;
    std::vector<Schedule> schedules;

    for (const auto &classEntry: classes_map) {
        const Class &currentClass = classEntry.second;
        if (currentClass.getClass_code() == class_code) {
            const std::vector<Schedule> &classSchedules = currentClass.getSchedules();
            schedules.insert(schedules.end(), classSchedules.begin(), classSchedules.end());
        }
    }
    if (schedules.empty()) {
        std::cout << "No schedules found for class code: " << class_code << std::endl;
    } else {
        std::cout << "Schedules for class code: " << class_code << std::endl;
        for (const Schedule& schedule: schedules) {
            std::cout << "UC: " << schedule.getUc_code() << std::endl;
            std::cout << "Weekday: " << schedule.getWeekday() << std::endl;
            std::cout << "Start Hour: " << schedule.getStart_hour() << std::endl;
            std::cout << "Duration: " << schedule.getDuration() << " hours" << std::endl;
            std::cout << "Type: " << schedule.getType() << std::endl;
            std::cout << std::endl;
        }
    }
}

void Datamanager::consultStudents_in_class() {
    std::string class_code, uc_code, key;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::cout << "Enter class: ";
    std::cin >> class_code;
    key = uc_code + class_code;
    for (Student *student: classes_map[key].getStudents()) {
        std::cout << "Student name: " << student->getStudent_name() << ", Student code: " << student->getStudent_code() << std::endl;
    }
}

void Datamanager::consultStudentsByUCCode() {
    std::string uc_code;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::set<Student> studentsWithUCCode;
    for (const auto &classPair: Datamanager::classes_map) {
        const Class &classObj = classPair.second;
        if (classObj.getUc_code() == uc_code) {
            const std::vector<Student *> &studentsInClass = classObj.getStudents();
            for (const Student *student: studentsInClass) {
                studentsWithUCCode.insert(*student);
            }
        }
    }
    for (Student student_ptr: studentsWithUCCode) {
        std::cout << "Student name: " << student_ptr.getStudent_name() << ", Student code: "
                  << student_ptr.getStudent_code() << "\n";
    }
}

void Datamanager::consultStudentsByYear() {
    int year;
    std::cout << "Enter the year: ";
    std::cin >> year;
    std::set<Student> uniqueStudents;

    for (const auto &classPair: Datamanager::classes_map) {
        const Class &classObj = classPair.second;
        if (classObj.getClass_code()[0] - '0' == year) {
            const std::vector<Student *> &studentsInClass = classObj.getStudents();
            for (const Student *student_ptr: studentsInClass) {
                if (student_ptr) {
                    uniqueStudents.insert(*student_ptr);
                }
            }
        }
    }
    for (Student student_ptr: uniqueStudents) {
        std::cout << "Student name: " << student_ptr.getStudent_name() << ", Student code: "
                  << student_ptr.getStudent_code() << "\n";
    }
}

void Datamanager::countStudentsInNOrMoreUCs() {
    int n;
    std::cout << "Enter number of UCs: ";
    std::cin >> n;
    int count = 0;

    for (const auto &pair: Datamanager::students_map) {
        Student student = pair.second;
        const std::vector<Class> &classes = student.getClasses();
        std::unordered_set<std::string> uniqueUCs;
        for (const Class &class1: classes) {
            uniqueUCs.insert(class1.getUc_code());
        }
        if (uniqueUCs.size() >= n) {
            count++;
        }
    }
    std::cout << "There are " << count << " students registered in " << n << " or more UCs." << std::endl;
}

void Datamanager::consultClassOccupation() {
    std::string uc_code, class_code;
    std::cout << "Enter UC Code: ";
    std::cin >> uc_code;
    std::cout << "Enter Class code: ";
    std::cin >> class_code;
    std::string key = uc_code + class_code;
    const std::vector<Student *> &students = classes_map[key].getStudents();
    std::cout << "The class " << class_code << " of "<< uc_code <<
    " has " << students.size() << " students!" << std::endl;

}
void Datamanager::consultCourseClassOccupation() {
    for (std::pair<std::string, Class> class1 : classes_map) {

        std::cout << "The class " << class1.second.getClass_code() << " of " << class1.second.getUc_code() <<
                  " has " << class1.second.getStudent_count() << " students!" << std::endl;
    }
}

void Datamanager::consultYearOccupation() {
    int year;
    std::string ordinal;
    std::cout << "Enter year: ";
    std::cin >> year;
    switch (year) {
        case 1:
            ordinal = "st";
            break;
        case 2:
            ordinal = "nd";
            break;
        case 3:
            ordinal = "rd";
            break;
        default:
            ordinal = "th";
            break;
    }

    std::set<Student> uniqueStudents;
    for (const auto &classPair: Datamanager::classes_map) {
        const Class &classObj = classPair.second;
        if (classObj.getClass_code()[0] - '0' == year) {
            const std::vector<Student *> &studentsInClass = classObj.getStudents();
            for (const Student *student_ptr: studentsInClass) {
                if (student_ptr) {
                    uniqueStudents.insert(*student_ptr);
                }
            }
        }
    }
    std::cout << "There are " << uniqueStudents.size() << " students registered in the " << year << ordinal << " year!"
              << std::endl;
}

void Datamanager::consultUcOccupation() {
    std::string uc_code;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::set<Student> studentsWithUCCode;
    for (const auto &classPair: Datamanager::classes_map) {
        const Class &classObj = classPair.second;
        if (classObj.getUc_code() == uc_code) {
            const std::vector<Student *> &studentsInClass = classObj.getStudents();
            for (const Student *student: studentsInClass) {
                studentsWithUCCode.insert(*student);
            }
        }
    }
    std::cout << "There are " << studentsWithUCCode.size() << " students registered in " << uc_code << "!" << std::endl;
}

void Datamanager::consultGreatestUcs() {
    std::unordered_map<std::string, int> ucOccupation;

    for (const auto &classPair: Datamanager::classes_map) {
        const Class &classObj = classPair.second;
        const std::string uc_code = classObj.getUc_code();
        const std::vector<Student *> &studentsInClass = classObj.getStudents();
        ucOccupation[uc_code] += studentsInClass.size();
    }
    std::multimap<int, std::string, std::greater<>> sortedUcs;
    for (const auto &entry: ucOccupation) {
        sortedUcs.insert(std::make_pair(entry.second, entry.first));
    }
    int count = 0;
    int n;
    std::cout << "Enter number of UCs: " << std::endl;
    std::cin >> n;
    std::cout << "Top " << n << " UCs by Occupation: " << std::endl;
    for (const auto &entry: sortedUcs) {
        std::cout << "UC " << entry.second << ": " << entry.first << " students" << std::endl;
        count++;
        if (count >= n) {
            break;
        }
    }
}
std::unordered_map<std::string, double> Datamanager::setAverage_Nstudents_perUC1() {
    std::unordered_map<std::string, std::pair<int, int>> uc_student_count_and_class_count;

    // Initialize counts
    for (const auto& class_pair : classes_map) {
        const std::string& uc_code = class_pair.second.getUc_code();
        uc_student_count_and_class_count[uc_code].first = 0;  // Initialize student count
        uc_student_count_and_class_count[uc_code].second = 0; // Initialize class count
    }

    // Calculate student count and class count
    for (const auto& student_pair : students_map) {
        Student student = student_pair.second;
        for (const auto& class_entry : student.getClasses()) {
            const std::string& uc_code = class_entry.getUc_code();
            uc_student_count_and_class_count[uc_code].first++; // Increment student count
        }
    }
    // Calculate the total number of classes for each UC
    for (const auto& class_pair : classes_map) {
        const std::string& uc_code = class_pair.second.getUc_code();
        uc_student_count_and_class_count[uc_code].second++; // Increment class count
    }

    std::unordered_map<std::string, double> uc_average_students_per_class;

    for (const auto& uc_count_pair : uc_student_count_and_class_count) {
        const std::string& uc_code = uc_count_pair.first;
        int student_count = uc_count_pair.second.first;
        int class_count = uc_count_pair.second.second;
        double average_students_per_class = static_cast<double>(student_count) / class_count;
        uc_average_students_per_class[uc_code] = average_students_per_class;
    }
    return uc_average_students_per_class;
}

void Datamanager::setAverage_Nstudents_perUC() {
    std::map<std::string, std::pair<int, int>> uc_student_count_and_class_count;

    // Initialize counts
    for (const auto& class_pair : classes_map) {
        const std::string& uc_code = class_pair.second.getUc_code();
        uc_student_count_and_class_count[uc_code].first = 0;  // Initialize student count
        uc_student_count_and_class_count[uc_code].second = 0; // Initialize class count
    }

    // Calculate student count and class count
    for (const auto& student_pair : students_map) {
        Student student = student_pair.second;
        for (const auto& class_entry : student.getClasses()) {
            const std::string& uc_code = class_entry.getUc_code();
            uc_student_count_and_class_count[uc_code].first++; // Increment student count
        }
    }

    // Calculate the total number of classes for each UC
    for (const auto& class_pair : classes_map) {
        const std::string& uc_code = class_pair.second.getUc_code();
        uc_student_count_and_class_count[uc_code].second++; // Increment class count
    }

    std::map<std::string, double> uc_average_students_per_class;

    for (const auto& uc_count_pair : uc_student_count_and_class_count) {
        const std::string& uc_code = uc_count_pair.first;
        int student_count = uc_count_pair.second.first;
        int class_count = uc_count_pair.second.second;
        double average_students_per_class = static_cast<double>(student_count) / class_count;
        uc_average_students_per_class[uc_code] = average_students_per_class;
    }

    std::cout << "Average Students per Class for each UC: " << std::endl;
    for (const auto& uc_avg_pair : uc_average_students_per_class) {
        const std::string& uc_code = uc_avg_pair.first;
        const double average_students_per_class = uc_avg_pair.second;
        std::cout << "UC Code: " << uc_code << ", Average Students per Class: " << average_students_per_class << std::endl;
    }
}
void Datamanager::seeRequests() {
    std::cout << "There are " << requests.size() << " ongoing requests!" << std::endl;
    std::queue<Request> copy = requests;
    while(!copy.empty()){
        copy.front().printTimestamp();
        std::cout << "The student " << copy.front().getRequest_student().getStudent_name() <<
        " requested to " << copy.front().getRequest_type() <<
        " a registration of the class " << copy.front().getRequest_class().getClass_code() <<
        " of " << copy.front().getRequest_class().getUc_code();
        if (copy.front().getRequest_newclass().getClass_key() != "AA") {
            std::cout << " with the class " << copy.front().getRequest_newclass().getClass_code()
            << " of " << copy.front().getRequest_newclass().getUc_code();
        }
        std::cout << std::endl;
        copy.pop();

    }
}
void Datamanager::seeRequest_log() {
    std::cout  << request_log.size() << " approved requests so far!" << std::endl;
    std::stack<Request> copy = request_log;
    while(!copy.empty()){
        copy.top().printTimestamp();
        std::cout << " the student " << copy.top().getRequest_student().getStudent_name() <<
                  " " << copy.top().getRequest_type() <<
                  "ed a registration of the class " << copy.top().getRequest_class().getClass_code() <<
                  " of " << copy.top().getRequest_class().getUc_code();
        if (copy.top().getRequest_newclass().getClass_key() != "AA") {
            std::cout << " with the class " << copy.top().getRequest_newclass().getClass_code()
                      << " of " << copy.top().getRequest_newclass().getUc_code();
        }
        std::cout << std::endl;
        copy.pop();

    }
}
void Datamanager::createAdd_request() {
    int student_code;
    std::string uc_code, class_code, class_key;
    std::cout << "Enter student code: " << std::endl;
    std::cin >> student_code;
    if (students_map.find(student_code) == students_map.end()) {
        std::cout << "Student with code " << student_code << " not found." << std::endl;
        return;
    }
    std::cout << "Enter UC: " << std::endl;
    std::cin >> uc_code;
    std::cout << "Enter Class: " << std::endl;
    std::cin >> class_code;
    class_key = uc_code + class_code;

    requests.emplace(students_map[student_code], "Add" , classes_map[class_key]);
    std::cout << "Your request has been dully noted!" << std::endl;

}

void Datamanager::createRemove_request() {
    int student_code;
    std::string uc_code, class_code, class_key;
    std::cout << "Enter student code: " << std::endl;
    std::cin >> student_code;
    if (students_map.find(student_code) == students_map.end()) {
        std::cout << "Student with code " << student_code << " not found." << std::endl;
        return;
    }
    std::cout << "Enter UC: " << std::endl;
    std::cin >> uc_code;
    std::cout << "Enter Class: " << std::endl;
    std::cin >> class_code;
    class_key = uc_code + class_code;

    requests.emplace(students_map[student_code], "Remove" , classes_map[class_key]);
    std::cout << "Your request has been dully noted!" << std::endl;

}

void Datamanager::createSwitch_request() {
    int student_code;
    std::string uc_code, class_code,  class_key, replacing_uc_code, replacing_class_code, replacing_class_key;
    std::cout << "Enter student code: " << std::endl;
    std::cin >> student_code;
    if (students_map.find(student_code) == students_map.end()) {
        std::cout << "Student with code " << student_code << " not found." << std::endl;
        return;
    }
    std::cout << "Enter UC: " << std::endl;
    std::cin >> uc_code;
    std::cout << "Enter Class you want to replace: " << std::endl;
    std::cin >> class_code;
    std::cout << "Enter UC of new Class you want to register to: " << std::endl;
    std::cin >> replacing_uc_code;
    std::cout << "Enter Class you want to register to: " << std::endl;
    std::cin >> replacing_class_code;
    class_key = uc_code + class_code;
    replacing_class_key = replacing_uc_code + replacing_class_code;

    requests.emplace(students_map[student_code], "Switch" , classes_map[class_key],
                     classes_map[replacing_class_key]);
    std::cout << "Your request has been dully noted!" << std::endl;

}
int getLeastPopulatedClassStudentCount(const std::string& uc_code){
    int min = INT_MAX;
    for (const auto& class_pair : Datamanager::classes_map){
        if ((class_pair.second.getStudent_count() < min) && (class_pair.second.getUc_code() == uc_code))
            min = class_pair.second.getStudent_count();

    }
    return min;
}
int getMostPopulatedClassStudentCount(const std::string& uc_code){
    int max = 0;
    for (const auto& class_pair : Datamanager::classes_map){
        if ((class_pair.second.getStudent_count() > max) && (class_pair.second.getUc_code() == uc_code))
            max = class_pair.second.getStudent_count();
    }
    return max;
}
bool checkScheduleCompatibility(const std::vector<Schedule>& schedules, const std::vector<Schedule>& new_schedules) {
    for (const Schedule& schedule : schedules){
        for (const Schedule& new_schedule : new_schedules) {

            // Check if the schedules are on the same weekday
            if (schedule.getWeekday() == new_schedule.getWeekday()) {
                // Check if there's an overlap in the time slots
                double start1 = schedule.getStart_hour();
                double end1 = start1 + schedule.getDuration();
                double start2 = new_schedule.getStart_hour();
                double end2 = start2 + new_schedule.getDuration();

                // If either of the schedules starts during the other's time or if they overlap
                if ((start1 >= start2 && start1 < end2) || (start2 >= start1 && start2 < end1)) {
                    // There's a time conflict
                    return false;
                }
            }
        }
    }

    // No conflict found
    return true;
}
bool checkAtleastOneClassWithVacancy(const std::string& uc_code){
    for (const auto& class_pair : Datamanager::classes_map){
        if ((class_pair.second.getStudent_count() < 26 ) && (class_pair.second.getUc_code() == uc_code))
            return true;
    }
    return false;
}
bool checkStudentClassCompatibility(const std::vector<Class>& student_classes, const Class& new_class){
    for (const Class& class_pair : student_classes){
        if ( class_pair.getUc_code() == new_class.getUc_code()) return false;
    }
    return true;
}

void Datamanager::processNext_request() {
    int student_code = requests.front().getRequest_student().getStudent_code();
    std::string class_key = requests.front().getRequest_class().getClass_key();
    std::string new_class_key = requests.front().getRequest_newclass().getClass_key();
    if (requests.front().getRequest_type() == "Add") {
        if (((Datamanager::classes_map[class_key].getStudent_count() -
                getLeastPopulatedClassStudentCount(requests.front().getRequest_class().getUc_code())) < 4)
                && (Datamanager::classes_map[class_key].getStudent_count() < Datamanager::class_cap )
                && (Datamanager::students_map[student_code].getClasses().size() < 7)
                && (checkScheduleCompatibility(Datamanager::students_map[student_code].getStudent_schedule(),
                                               requests.front().getRequest_class().getSchedules()))
                && (checkAtleastOneClassWithVacancy(requests.front().getRequest_class().getUc_code()))
                && (checkStudentClassCompatibility(Datamanager::students_map[student_code].getClasses(),
                                                   requests.front().getRequest_class()))) {

            Datamanager::students_map[student_code].addClass(requests.front().getRequest_class());

            Datamanager::students_map[student_code].addStudent_schedule(requests.front().getRequest_class().getSchedules());

            requests.front().updateTimestamp();
            request_log.push(requests.front());
            saveRequestLogToFile(requests.front());

            std::cout << "Request approved! " << requests.front().getRequest_student().getStudent_name() <<
            " successfully registered in the class " << requests.front().getRequest_class().getClass_code()
            << " of " << requests.front().getRequest_class().getUc_code() << std::endl;
            requests.pop();
        }
        else {
            std::cout << "Request denied! " << requests.front().getRequest_student().getStudent_name() <<
                      " didn't register for the class " << requests.front().getRequest_class().getClass_code()
                      << " of " << requests.front().getRequest_class().getUc_code() << std::endl;
            requests.pop();
        }
    }

    else if (requests.front().getRequest_type() == "Remove") {
        if (getMostPopulatedClassStudentCount(requests.front().getRequest_class().getUc_code()) -
                     Datamanager::classes_map[class_key].getStudent_count() < 4)
        {
            Datamanager::students_map[student_code].removeClass(requests.front().getRequest_class());
            Datamanager::students_map[student_code].removeStudent_schedules(requests.front().getRequest_class().getSchedules());
            requests.front().updateTimestamp();
            request_log.push(requests.front());
            saveRequestLogToFile(requests.front());
            std::cout << "Request approved! " << requests.front().getRequest_student().getStudent_name() <<
                      " successfully unregistered in the class " << requests.front().getRequest_class().getClass_code()
                      << " of " << requests.front().getRequest_class().getUc_code() << std::endl;
            requests.pop();
        }
        else {
            std::cout << "Request denied! " << requests.front().getRequest_student().getStudent_name() <<
                      " didn't unregister for the class " << requests.front().getRequest_class().getClass_code()
                      << " of " << requests.front().getRequest_class().getUc_code() << std::endl;
            requests.pop();
        }
    }
    else{
        if((((Datamanager::classes_map[new_class_key].getStudent_count() -
                 getLeastPopulatedClassStudentCount(requests.front().getRequest_newclass().getUc_code())) < 4)
               && (Datamanager::classes_map[new_class_key].getStudent_count() < Datamanager::class_cap )
               && (requests.front().getRequest_student().getClasses().size() < 7)
               && (checkScheduleCompatibility(Datamanager::students_map[student_code].getStudent_schedule(),
                                              requests.front().getRequest_class().getSchedules()))
               && (checkAtleastOneClassWithVacancy(requests.front().getRequest_newclass().getUc_code()))
               && (checkStudentClassCompatibility(Datamanager::students_map[student_code].getClasses(),
                                                  requests.front().getRequest_newclass())))
            && (getMostPopulatedClassStudentCount(requests.front().getRequest_class().getUc_code()) -
            Datamanager::classes_map[class_key].getStudent_count() < 4))
        {
            Datamanager::students_map[student_code].addClass(requests.front().getRequest_newclass());
            Datamanager::students_map[student_code].addStudent_schedule(requests.front().getRequest_newclass().getSchedules());
            Datamanager::students_map[student_code].removeClass(requests.front().getRequest_class());
            Datamanager::students_map[student_code].removeStudent_schedules(requests.front().getRequest_class().getSchedules());
            requests.front().updateTimestamp();
            request_log.push(requests.front());
            saveRequestLogToFile(requests.front());
            std::cout << "Request approved! " << requests.front().getRequest_student().getStudent_name() <<
                      " successfully swapped the class " << requests.front().getRequest_class().getClass_code()
                      << " of " << requests.front().getRequest_class().getUc_code() <<
                      " for the class " << requests.front().getRequest_newclass().getClass_code()
                      << " of " << requests.front().getRequest_newclass().getUc_code() << std::endl;
            requests.pop();
        }
        else {
            std::cout << "Request denied! " << requests.front().getRequest_student().getStudent_name() <<
                      " didn't swap the class " << requests.front().getRequest_class().getClass_code()
                      << " of " << requests.front().getRequest_class().getUc_code() <<
                      " for the class " << requests.front().getRequest_newclass().getClass_code()
                      << " of " << requests.front().getRequest_newclass().getUc_code() << std::endl;
            requests.pop();
        }
    }
}

void Datamanager::processRemaining_requests(){
    if (requests.empty()) std::cout << "No requests remaining" << std::endl;
    while (!requests.empty()){
        processNext_request();
        if (requests.empty()) std::cout << "All remaining requests processed, request queue is now empty." << std::endl;
    }
}

void Datamanager::saveRequestLogToFile(Request request) {
    std::ofstream logFile("../Data/request_log.txt", std::ios::app); // Open file in append mode

    if (logFile.is_open()) {
        std::time_t timestamp_time = std::chrono::system_clock::to_time_t(request.getTimestamp());
        std::tm* timeinfo = std::localtime(&timestamp_time);

        // Format the timestamp
        std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");

        // Write the log entry to the file
        logFile << "Timestamp: " << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S") << std::endl;
        logFile << "Student Name: " << request.getRequest_student().getStudent_name() << std::endl;
        logFile << "Request type: " << request.getRequest_type() << std::endl;
        logFile << "Request class: " << request.getRequest_class().getClass_code() <<
        " " << request.getRequest_class().getUc_code() << std::endl;
        logFile << "------------------------------------------" << std::endl;

        logFile.close(); // Close the file
        std::cout << "Request log saved to 'request_log.txt'" << std::endl;
    } else {
        std::cerr << "Error opening the file for writing." << std::endl;
    }
}

void Datamanager::undoLast_request() {
    int student_code = request_log.top().getRequest_student().getStudent_code();
    std::string class_key = request_log.top().getRequest_class().getClass_key();
    std::string new_class_key = request_log.top().getRequest_newclass().getClass_key();
    if (request_log.empty()) std::cout << "No requests recorded!" << std::endl;
    if (request_log.top().getRequest_type() == "Add") {
        if (getMostPopulatedClassStudentCount(request_log.top().getRequest_class().getUc_code()) -
            Datamanager::classes_map[class_key].getStudent_count() < 4)
        {
            Datamanager::students_map[student_code].removeClass(request_log.top().getRequest_class());
            Datamanager::students_map[student_code].removeStudent_schedules(request_log.top().getRequest_class().getSchedules());
            request_log.top().updateTimestamp();
            saveRequestLogToFile(request_log.top());
            std::cout << "Request rolled-back! " << request_log.top().getRequest_student().getStudent_name() <<
                      " successfully unregistered in the class " << request_log.top().getRequest_class().getClass_code()
                      << " of " << request_log.top().getRequest_class().getUc_code() << std::endl;
            request_log.pop();
        }
        else {
            std::cout << "Undo denied! " << request_log.top().getRequest_student().getStudent_name() <<
                      " didn't unregister for the class " << request_log.top().getRequest_class().getClass_code()
                      << " of " << request_log.top().getRequest_class().getUc_code() << std::endl;
            request_log.pop();
        }
    }
    else if (request_log.top().getRequest_type() == "Remove") {
        if (((Datamanager::classes_map[class_key].getStudent_count() -
              getLeastPopulatedClassStudentCount(request_log.top().getRequest_class().getUc_code())) < 4)
            && (Datamanager::classes_map[class_key].getStudent_count() < Datamanager::class_cap )
            && (Datamanager::students_map[student_code].getClasses().size() < 7)
            && (checkScheduleCompatibility(Datamanager::students_map[student_code].getStudent_schedule(),
                                           request_log.top().getRequest_class().getSchedules()))
            && (checkAtleastOneClassWithVacancy(request_log.top().getRequest_class().getUc_code()))
            && (checkStudentClassCompatibility(Datamanager::students_map[student_code].getClasses(),
                                               request_log.top().getRequest_class()))) {
            Datamanager::students_map[student_code].addClass(request_log.top().getRequest_class());
            Datamanager::students_map[student_code].addStudent_schedule(request_log.top().getRequest_class().getSchedules());
            request_log.top().updateTimestamp();
            saveRequestLogToFile(request_log.top());

            std::cout << "Request rolled-back! " << request_log.top().getRequest_student().getStudent_name() <<
                      " successfully re-registered in the class " << request_log.top().getRequest_class().getClass_code()
                      << " of " << request_log.top().getRequest_class().getUc_code() << std::endl;
            request_log.pop();
        }
        else {
            std::cout << "Undo denied! " << request_log.top().getRequest_student().getStudent_name() <<
                      " didn't re-register for the class " << request_log.top().getRequest_class().getClass_code()
                      << " of " << request_log.top().getRequest_class().getUc_code() << std::endl;
            request_log.pop();
        }
    }
    else {
        if((((Datamanager::classes_map[new_class_key].getStudent_count() -
              getLeastPopulatedClassStudentCount(request_log.top().getRequest_newclass().getUc_code())) < 4)
            && (Datamanager::classes_map[new_class_key].getStudent_count() < Datamanager::class_cap )
            && (Datamanager::students_map[student_code].getClasses().size() < 7)
            && (checkScheduleCompatibility(Datamanager::students_map[student_code].getStudent_schedule(),
                                           request_log.top().getRequest_newclass().getSchedules()))
            && (checkAtleastOneClassWithVacancy(request_log.top().getRequest_newclass().getUc_code()))
            && (checkStudentClassCompatibility(Datamanager::students_map[student_code].getClasses(),
                                               request_log.top().getRequest_newclass())))
           && (getMostPopulatedClassStudentCount(request_log.top().getRequest_class().getUc_code()) -
               Datamanager::classes_map[class_key].getStudent_count() < 4))
        {
            Datamanager::students_map[student_code].addClass(request_log.top().getRequest_newclass());
            Datamanager::students_map[student_code].addStudent_schedule(request_log.top().getRequest_newclass().getSchedules());
            Datamanager::students_map[student_code].removeClass(request_log.top().getRequest_class());
            Datamanager::students_map[student_code].removeStudent_schedules(request_log.top().getRequest_class().getSchedules());
            request_log.top().updateTimestamp();
            saveRequestLogToFile(request_log.top());
            std::cout << "Request rolled-back! " << request_log.top().getRequest_student().getStudent_name() <<
                      " successfully swapped back in the class " << request_log.top().getRequest_class().getClass_code()
                      << " of " << request_log.top().getRequest_class().getUc_code() <<
                      " from the class " << request_log.top().getRequest_newclass().getClass_code()
                      << " of " << request_log.top().getRequest_newclass().getUc_code() << std::endl;
            request_log.pop();
        }
        else {
            std::cout << "Undo denied! " << request_log.top().getRequest_student().getStudent_name() <<
                      " didn't swap back in the class " << request_log.top().getRequest_class().getClass_code()
                      << " of " << request_log.top().getRequest_class().getUc_code() <<
                      " from the class " << request_log.top().getRequest_newclass().getClass_code()
                      << " of " << request_log.top().getRequest_newclass().getUc_code() << std::endl;
            request_log.pop();
        }
    }
}
void Datamanager::undoAll_requests(){
    if (request_log.empty()) std::cout << "No requests remaining" << std::endl;
    while (!request_log.empty()) {
        undoLast_request();
        if (request_log.empty()) std::cout << "Undid all requests, request stack is now empty." << std::endl;
    }
}



