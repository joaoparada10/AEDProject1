/**
 * @file Datamanager.cpp
 * @brief Implementation of the Datamanager class methods
 */

#include <map>
#include <climits>
#include <algorithm>
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
    /**
     * @return Returns a single student schedule
     *
     * @param student_code The unique code of each student
     *
     * @complextity O(n)
     */
    int student_code;
    std::cout << "Enter student code: ";
    std::cin >> student_code;

    if (students_map.find(student_code) == students_map.end()) {
        std::cout << "Student with code " << student_code << " not found." << std::endl;
        return;
    }
    Student student = students_map[student_code];
    std::vector<Schedule> student_schedule = student.getStudent_schedule();
    std::sort(student_schedule.begin(), student_schedule.end());

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
    /**
    *@return Returns the schedule of all UC classes  from one set of students within the same class
    *
    * @param class_code Unique code for each class
    *
    * Time Complexity O(n*log(n))
    */
    std::string class_code;
    std::cout << "Enter class: ";
    std::cin >> class_code;
    std::vector<Schedule> schedules;

    for (const auto& class_pair: classes_map) {
        const Class current_class = class_pair.second;
        if (current_class.getClass_code() == class_code) {
            const std::vector<Schedule> &classSchedules = current_class.getSchedules();
            schedules.insert(schedules.end(), classSchedules.begin(), classSchedules.end());
        }
    }
    std::sort(schedules.begin(), schedules.end());
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
    /**
     *@return Returns all of the students name and respective codes on the same class that are registered on a specific UC.
     *
     * @param uc_code Unique code for each UC
     * @param class_code Unique code for each class
     *
     *Time Complexity O(n*log(n))
     */
    std::string class_code, uc_code, key;
    std::vector<Student> students;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::cout << "Enter class: ";
    std::cin >> class_code;
    key = uc_code + class_code;
    std::vector<Student *> students_in_class = Datamanager::classes_map[key].getStudents();
    for (const Student* ptr : students_in_class) {
        students.push_back(*ptr);
    }
    std::sort(students.begin(), students.end());
    for (Student student: students) {
        std::cout << "Student name: " << student.getStudent_name() << ", Student code: " << student.getStudent_code() << std::endl;
    }
}

void Datamanager::consultStudentsByUCCode() {
    /**
    *@return Returns all students registered on a UC.
    *
    *@param uc_code Unique code for each UC
     *
     *Time Complexity O(n^2)
    */
    std::string uc_code;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::set<Student> studentsWithUCCode;   // também podiamos ter usado um vector, dar std::sort nele e remover os duplicados
    for (const auto &class_pair: Datamanager::classes_map) {
        const Class &current_class = class_pair.second;
        if (current_class.getUc_code() == uc_code) {
            const std::vector<Student *> &studentsInClass = current_class.getStudents();
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
    /**
    *@return  Returns all students on the same academic year.
    *
    *@param year Academic year (from 1 to 3)
     *
     * Time Complexity O(n^2)
    */
    int year;
    std::cout << "Enter the year: ";
    std::cin >> year;
    std::set<Student> uniqueStudents;   // também podiamos ter usado um vector, dar std::sort nele e remover os duplicados

    for (const auto &class_pair: Datamanager::classes_map) {
        const Class &current_class = class_pair.second;
        if (current_class.getClass_code()[0] - '0' == year) {
            const std::vector<Student *> &studentsInClass = current_class.getStudents();
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
    /**
    * @return  Returns the number os students registered in  n or more UCs
    *
    * @param n Number of UCs
     *
     *Time Complexity O(n^2)
    */

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
    /**
    * @return Returns the number of students in a specific class , registered in a sinlge UC.
    *
    * @param uc_code Unique code for each UC
    * @param class_code Unique code for each class
     *
     * Time Complexity O(1)
    */
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
/**
 * @return Returns the number os students of one class
 * @Time Complexity O(n)
 */
void Datamanager::consultCourseClassOccupation() {
    std::map<std::string, Class> ordered_classes_map;
    for (std::pair<std::string, Class> class1 : classes_map) {
        ordered_classes_map.insert(class1);
    }
    for (std::pair<std::string, Class> class1 : ordered_classes_map) {

        std::cout << "The class " << class1.second.getClass_code() << " of " << class1.second.getUc_code() <<
                  " has " << class1.second.getStudent_count() << " students!" << std::endl;
    }
}
/**
 * @return  Returns the number of students per year.
 *
 * @param year Academic year.
 *
 * @Time Complexity 0(n^2)
 */
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
    for (const auto &class_pair: Datamanager::classes_map) {
        const Class &current_class = class_pair.second;
        if (current_class.getClass_code()[0] - '0' == year) {
            const std::vector<Student *> &studentsInClass = current_class.getStudents();
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
    /**
     * @return  Returns the number of registered students per UC
     *
     * @param uc_code Unique code for each UC
     *
     * @Time Complexity O(n^2)
     */

    std::string uc_code;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::set<Student> studentsWithUCCode;
    for (const auto &class_pair: Datamanager::classes_map) {
        const Class &current_class = class_pair.second;
        if (current_class.getUc_code() == uc_code) {
            const std::vector<Student *> &studentsInClass = current_class.getStudents();
            for (const Student *student: studentsInClass) {
                studentsWithUCCode.insert(*student);
            }
        }
    }
    std::cout << "There are " << studentsWithUCCode.size() << " students registered in " << uc_code << "!" << std::endl;
}

void Datamanager::consultGreatestUcs() {
    /**
     * @return Returns the top n UCs ranked by occupation
     *
     * @param n Number of UCs to rank
     *
     * Time Complexity O(n^2)
     */
    std::unordered_map<std::string, int> ucOccupation;

    for (const auto &class_pair: Datamanager::classes_map) {
        const Class &current_class = class_pair.second;
        const std::string uc_code = current_class.getUc_code();
        ucOccupation[uc_code] += current_class.getStudent_count();
    }
    std::map<int, std::string, std::greater<>> sortedUcs;
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

/**@return Returns the average number of students per UC
 * Time Complexity O(n^2)
 */
void Datamanager::setAverage_Nstudents_perUC() {
    std::map<std::string, std::pair<int, int>> uc_student_count_and_class_count;

    for (const auto& class_pair : Datamanager::classes_map) {
        const std::string& uc_code = class_pair.second.getUc_code();
        uc_student_count_and_class_count[uc_code].first = 0;
        uc_student_count_and_class_count[uc_code].second = 0;
    }

    for (const auto& student_pair : students_map) {
        Student student = student_pair.second;
        for (const auto& class_entry : student.getClasses()) {
            const std::string& uc_code = class_entry.getUc_code();
            uc_student_count_and_class_count[uc_code].first++;
        }
    }

    for (const auto& class_pair : classes_map) {
        const std::string& uc_code = class_pair.second.getUc_code();
        uc_student_count_and_class_count[uc_code].second++;
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
/**@return Returns all requests on the queue
 * Time Complexity O(n)
 */
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
/**@return Returns the request log
 * Time Complexity O(n)
 */
void Datamanager::seeRequest_log() {
    std::cout  << request_log.size() << " approved requests so far!" << std::endl;
    std::stack<Request> copy = request_log;
    while(!copy.empty()){
        copy.top().printTimestamp();
        if (copy.top().getRequest_type() == "Add")
            std::cout << " the student " << copy.top().getRequest_student().getStudent_name() <<
            " " << copy.top().getRequest_type() <<
            "ed a registration of the class " << copy.top().getRequest_class().getClass_code() <<
            " of " << copy.top().getRequest_class().getUc_code();
        else if (copy.top().getRequest_type() == "Remove")
            std::cout << " the student " << copy.top().getRequest_student().getStudent_name() <<
            " " << copy.top().getRequest_type() <<
            "d a registration of the class " << copy.top().getRequest_class().getClass_code() <<
            " of " << copy.top().getRequest_class().getUc_code();
        else {
            std::cout << " the student " << copy.top().getRequest_student().getStudent_name() <<
                      " " << copy.top().getRequest_type() <<
                      "ed a registration of the class " << copy.top().getRequest_class().getClass_code() <<
                      " of " << copy.top().getRequest_class().getUc_code()
                      << " with the class " << copy.top().getRequest_newclass().getClass_code()
                      << " of " << copy.top().getRequest_newclass().getUc_code();
        }
        std::cout << std::endl;
        copy.pop();

    }
}
/**@return Creates an add request
 *Time Complexity O(1)
 */
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

    requests.emplace(students_map[student_code], "Add", classes_map[class_key]);
    std::cout << "Your request has been duly noted!" << std::endl;

}
/**@return Creates a remove request
 *Time Complexity O(1)
 */
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
    std::cout << "Your request has been duly noted!" << std::endl;

}
/**@return Creates a switch request
 *Time Complexity O(1)
 */
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
/**@return Returns the class with less students
 * @param uc_code The identification code for an uc
 * Time Complexity O(n)
 */
int getLeastPopulatedClassStudentCount(const std::string& uc_code){
    int min = INT_MAX;
    for (const auto& class_pair : Datamanager::classes_map){
        if ((class_pair.second.getStudent_count() < min) && (class_pair.second.getUc_code() == uc_code))
            min = class_pair.second.getStudent_count();

    }
    return min;
}
/**@return Returns the class with the most students
 * @param uc_code The identification code for an uc
 * Time Complexity O(n)
 */
int getMostPopulatedClassStudentCount(const std::string& uc_code){
    int max = 0;
    for (const auto& class_pair : Datamanager::classes_map){
        if ((class_pair.second.getStudent_count() > max) && (class_pair.second.getUc_code() == uc_code))
            max = class_pair.second.getStudent_count();
    }
    return max;
}
/**@return Returns true if there are no conflicts between schedules
 * @param new_schedules Schedule to compare
 * @param schedules Schedule to compare
 *Time Complexity  O(n^2)
 */
bool checkScheduleCompatibility(const std::vector<Schedule>& schedules, const std::vector<Schedule>& new_schedules) {
    for (const Schedule& schedule : schedules){
        if(schedule.getType() == "TP" || schedule.getType() == "PL") {
            for (const Schedule &new_schedule: new_schedules) {
                if (new_schedule.getType() == "TP" || new_schedule.getType() == "PL") {

                    if (schedule.getWeekday() == new_schedule.getWeekday()) {
                        double start1 = schedule.getStart_hour();
                        double end1 = start1 + schedule.getDuration();
                        double start2 = new_schedule.getStart_hour();
                        double end2 = start2 + new_schedule.getDuration();

                        if ((start1 >= start2 && start1 < end2) || (start2 >= start1 && start2 < end1)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
/**@return Returns true if the class has an open slot
 * @param uc_code The identification code for an UC
 *Time Complexity 0(n)
 */
bool checkAtleastOneClassWithVacancy(const std::string& uc_code){
    for (const auto& class_pair : Datamanager::classes_map){
        if ((class_pair.second.getStudent_count() < 26 ) && (class_pair.second.getUc_code() == uc_code))
            return true;
    }
    return false;
}
/**@return Returns true if there are no conflicts between classes
 * @param student_classes Class to compare
 * @param new_class Class to compare
 *Time Complexity O(n)
 */
bool checkStudentClassCompatibility(const std::vector<Class>& student_classes, const Class& new_class){
    for (const Class& class_pair : student_classes){
        if ( class_pair.getUc_code() == new_class.getUc_code()) return false;
    }
    return true;
}
/**@return Accepts/Denies the next request
 * Time Complexity O(n²)
 */
void Datamanager::processNext_request() {
    if(requests.empty()){ std::cout << "No requests remaining" << std::endl;
        return;}
    Student student = requests.front().getRequest_student();
    int student_code = student.getStudent_code();
    std::string student_name = student.getStudent_name();
    Class request_class = requests.front().getRequest_class();
    std::string uc_code = request_class.getUc_code();
    std::string class_code = request_class.getClass_code();
    std::string class_key = request_class.getClass_key();
    std::string new_class_key = requests.front().getRequest_newclass().getClass_key();
    const std::vector<Schedule>& class_schedule = request_class.getSchedules();
    if (requests.front().getRequest_type() == "Add") {
        if (((Datamanager::classes_map[class_key].getStudent_count() -
                getLeastPopulatedClassStudentCount(uc_code)) < 4)
                && (Datamanager::classes_map[class_key].getStudent_count() < Datamanager::class_cap )
                && (Datamanager::students_map[student_code].getClasses().size() < 7)
                && (checkScheduleCompatibility(Datamanager::students_map[student_code].getStudent_schedule(),
                                               class_schedule))
                && (checkAtleastOneClassWithVacancy(uc_code))
                && (checkStudentClassCompatibility(Datamanager::students_map[student_code].getClasses(),
                                                   request_class))) {
            Datamanager::classes_map[class_key].addStudent(&Datamanager::students_map[student_code]);
            Datamanager::students_map[student_code].addClass(request_class);
            Datamanager::students_map[student_code].addStudent_schedule(class_schedule);

            requests.front().updateTimestamp();
            request_log.push(requests.front());
            saveRequestLogToFile(requests.front());

            std::cout << "Request approved! " << student_name <<
            " successfully registered in the class " << class_code
            << " of " << uc_code << std::endl;
            requests.pop();
        }
        else {
            std::cout << "Request denied! " << student_name <<
                      " didn't register for the class " << class_code
                      << " of " << uc_code << std::endl;
            requests.pop();
        }
    }

    else if (requests.front().getRequest_type() == "Remove") {
        if (getMostPopulatedClassStudentCount(uc_code) -
                     Datamanager::classes_map[class_key].getStudent_count() < 4)
        {
            Datamanager::classes_map[class_key].removeStudent(&Datamanager::students_map[student_code]);
            Datamanager::students_map[student_code].removeClass(request_class);
            Datamanager::students_map[student_code].removeStudent_schedules(class_schedule);
            requests.front().updateTimestamp();
            request_log.push(requests.front());
            saveRequestLogToFile(requests.front());
            std::cout << "Request approved! " << student_name <<
                      " successfully unregistered in the class " << class_code
                      << " of " << uc_code << std::endl;
            requests.pop();
        }
        else {
            std::cout << "Request denied! " << student_name <<
                      " didn't unregister for the class " << class_code
                      << " of " << uc_code << std::endl;
            requests.pop();
        }
    }
    else{

        Student temp_student = Datamanager::students_map[student_code];
        temp_student.removeStudent_schedules(request_class.getSchedules());
        std::vector<Schedule> temp_schedule = temp_student.getStudent_schedule();
        if((((Datamanager::classes_map[new_class_key].getStudent_count() -
                 getLeastPopulatedClassStudentCount(requests.front().getRequest_newclass().getUc_code())) < 4)
               && (Datamanager::classes_map[new_class_key].getStudent_count() < Datamanager::class_cap )
               && (checkScheduleCompatibility(temp_schedule,
                                              requests.front().getRequest_newclass().getSchedules()))
               && (checkAtleastOneClassWithVacancy(requests.front().getRequest_newclass().getUc_code()))
               && (checkStudentClassCompatibility(Datamanager::students_map[student_code].getClasses(),
                                                  requests.front().getRequest_newclass())))
            && (getMostPopulatedClassStudentCount(uc_code) -
            Datamanager::classes_map[class_key].getStudent_count() < 4))
        {
            Datamanager::classes_map[new_class_key].addStudent(&Datamanager::students_map[student_code]);
            Datamanager::students_map[student_code].addClass(requests.front().getRequest_newclass());
            Datamanager::students_map[student_code].addStudent_schedule(requests.front().getRequest_newclass().getSchedules());
            Datamanager::classes_map[class_key].removeStudent(&Datamanager::students_map[student_code]);
            Datamanager::students_map[student_code].removeClass(request_class);
            Datamanager::students_map[student_code].removeStudent_schedules(class_schedule);
            requests.front().updateTimestamp();
            request_log.push(requests.front());
            saveRequestLogToFile(requests.front());
            std::cout << "Request approved! " << student_name <<
                      " successfully swapped the class " << class_code
                      << " of " << uc_code <<
                      " for the class " << requests.front().getRequest_newclass().getClass_code()
                      << " of " << requests.front().getRequest_newclass().getUc_code() << std::endl;
            requests.pop();
        }
        else {
            std::cout << "Request denied! " << student_name <<
                      " didn't swap the class " << class_code
                      << " of " << uc_code <<
                      " for the class " << requests.front().getRequest_newclass().getClass_code()
                      << " of " << requests.front().getRequest_newclass().getUc_code() << std::endl;
            requests.pop();
        }
    }
}
/**@return Processes the next request if there are any on the queue
 * Time Complexity O(n²)
 */
void Datamanager::processRemaining_requests(){
    if (requests.empty()) std::cout << "No requests remaining" << std::endl;
    while (!requests.empty()){
        processNext_request();
        if (requests.empty()) std::cout << "All remaining requests processed, request queue is now empty." << std::endl;
    }
}
/**@param request A request
 * Time Complexity O(1)
 */

void Datamanager::saveRequestLogToFile(Request request) {
    std::ofstream logFile("../Data/request_log.txt", std::ios::app);

    if (logFile.is_open()) {
        std::time_t timestamp_time = request.getTimestamp();
        std::tm* timeinfo = std::localtime(&timestamp_time);
        std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
        logFile << "Timestamp: " << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S") << std::endl;
        logFile << "Student Name: " << request.getRequest_student().getStudent_name() << std::endl;
        logFile << "Request type: " << request.getRequest_type() << std::endl;
        logFile << "Request class: " << request.getRequest_class().getClass_code() <<
        " " << request.getRequest_class().getUc_code() << std::endl;
        logFile << "------------------------------------------" << std::endl;
        logFile.close();
        std::cout << "Request log saved to 'request_log.txt'" << std::endl;
    } else {
        std::cerr << "Error opening the file for writing." << std::endl;
    }
}
/**@return Undo the last request
 * Time Complexity O(n²)
 */
void Datamanager::undoLast_request() {
    Student student = request_log.top().getRequest_student();
    int student_code = student.getStudent_code();
    std::string student_name = student.getStudent_name();
    Class request_class = request_log.top().getRequest_class();
    std::string uc_code = request_class.getUc_code();
    std::string class_code = request_class.getClass_code();
    std::string class_key = request_class.getClass_key();
    std::string new_class_key = uc_code + class_code;
    const std::vector<Schedule>& class_schedule = request_class.getSchedules();
    if (request_log.empty()) std::cout << "No requests recorded!" << std::endl;
    if (request_log.top().getRequest_type() == "Add") {
        if (getMostPopulatedClassStudentCount(uc_code) -
            Datamanager::classes_map[class_key].getStudent_count() < 4)
        {
            Datamanager::classes_map[class_key].removeStudent(&Datamanager::students_map[student_code]);
            Datamanager::students_map[student_code].removeClass(request_class);
            Datamanager::students_map[student_code].removeStudent_schedules(class_schedule);
            request_log.top().updateTimestamp();
            saveRequestLogToFile(request_log.top());
            std::cout << "Request rolled-back! " << student_name <<
                      " successfully unregistered in the class " << class_code
                      << " of " << uc_code << std::endl;
            request_log.pop();
        }
        else {
            std::cout << "Undo denied! " << student_name <<
                      " didn't unregister for the class " << class_code
                      << " of " << uc_code << std::endl;
            request_log.pop();
        }
    }
    else if (request_log.top().getRequest_type() == "Remove") {
        if (((Datamanager::classes_map[class_key].getStudent_count() -
              getLeastPopulatedClassStudentCount(uc_code)) < 4)
            && (Datamanager::classes_map[class_key].getStudent_count() < Datamanager::class_cap )
            && (Datamanager::students_map[student_code].getClasses().size() < 7)
            && (checkScheduleCompatibility(Datamanager::students_map[student_code].getStudent_schedule(),
                                           class_schedule))
            && (checkAtleastOneClassWithVacancy(uc_code))
            && (checkStudentClassCompatibility(Datamanager::students_map[student_code].getClasses(),
                                               request_class))) {
            Datamanager::classes_map[class_key].addStudent(&Datamanager::students_map[student_code]);
            Datamanager::students_map[student_code].addClass(request_class);
            Datamanager::students_map[student_code].addStudent_schedule(class_schedule);
            request_log.top().updateTimestamp();
            saveRequestLogToFile(request_log.top());

            std::cout << "Request rolled-back! " << student_name <<
                      " successfully re-registered in the class " << class_code
                      << " of " << uc_code << std::endl;
            request_log.pop();
        }
        else {
            std::cout << "Undo denied! " << student_name <<
                      " didn't re-register for the class " << class_code
                      << " of " << uc_code << std::endl;
            request_log.pop();
        }
    }
    else {
        Student temp_student = Datamanager::students_map[student_code];
        temp_student.removeStudent_schedules(request_log.top().getRequest_newclass().getSchedules());
        std::vector<Schedule> temp_schedule = temp_student.getStudent_schedule();
        if((((Datamanager::classes_map[class_key].getStudent_count() -
              getLeastPopulatedClassStudentCount(uc_code)) < 4)
            && (Datamanager::classes_map[class_key].getStudent_count() < Datamanager::class_cap )
            && (checkScheduleCompatibility(temp_schedule,
                                           request_log.top().getRequest_class().getSchedules()))
            && (checkAtleastOneClassWithVacancy(uc_code))
            && (checkStudentClassCompatibility(Datamanager::students_map[student_code].getClasses(),
                                               request_log.top().getRequest_class())))
           && (getMostPopulatedClassStudentCount(request_log.top().getRequest_newclass().getUc_code()) -
               Datamanager::classes_map[new_class_key].getStudent_count() < 4))
        {
            Datamanager::classes_map[class_key].addStudent(&Datamanager::students_map[student_code]);
            Datamanager::students_map[student_code].removeClass(request_log.top().getRequest_newclass());
            Datamanager::students_map[student_code].removeStudent_schedules(request_log.top().getRequest_newclass().getSchedules());
            Datamanager::classes_map[new_class_key].removeStudent(&Datamanager::students_map[student_code]);
            Datamanager::students_map[student_code].addClass(request_class);
            Datamanager::students_map[student_code].addStudent_schedule(class_schedule);
            request_log.top().updateTimestamp();
            saveRequestLogToFile(request_log.top());
            std::cout << "Request rolled-back! " << student_name <<
                      " successfully swapped back in the class " << class_code
                      << " of " << uc_code <<
                      " from the class " << request_log.top().getRequest_newclass().getClass_code()
                      << " of " << uc_code << std::endl;
            request_log.pop();
        }
        else {
            std::cout << "Undo denied! " << student_name <<
                      " didn't swap back in the class " << class_code
                      << " of " << uc_code <<
                      " from the class " << request_log.top().getRequest_newclass().getClass_code()
                      << " of " << uc_code << std::endl;
            request_log.pop();
        }
    }
}
/**@return Undo every request
 * Time Complexity 0(n²)
 */
void Datamanager::undoAll_requests(){
    if (request_log.empty()) std::cout << "No requests remaining" << std::endl;
    while (!request_log.empty()) {
        undoLast_request();
        if (request_log.empty()) std::cout << "Undid all requests, request stack is now empty." << std::endl;
    }
}
/**@return Saves the request log data
 * Time Complexity 0(n)
 */
void Datamanager::saveRequest_log_data(const std::string& filename) {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        std::stack<Request> tempStack = Datamanager::request_log;
        while (!tempStack.empty()) {
            Request request = tempStack.top();
            std::time_t currentTime = request.getTimestamp();
            std::tm tm = *std::localtime(&currentTime);
            outputFile << request.getRequest_student().getStudent_code() << ',' <<  request.getRequest_type() << ',' <<
            request.getRequest_class().getClass_key() << ',' << request.getRequest_newclass().getClass_key() <<
            ',' << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "\n";
            tempStack.pop();
        }
        outputFile.close();
    } else {
        std::cerr << "Failed to open the file for writing." << std::endl;
    }
}
/**@return Loads the request log data
 * Time Complexity 0(n)
 */
void Datamanager::loadRequest_log(const std::string& filename) {
    std::stack<Request> requestStack;
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            int student_code;
            std::string type, class_key, new_class_key, timestamp;
            std::istringstream iss(line);
            if (iss >> student_code && iss.get() == ',' &&
                std::getline(iss, type, ',') &&
                std::getline(iss, class_key, ',') &&
                std::getline(iss, new_class_key, ',') &&
                std::getline(iss, timestamp, '\r')) {
                // Convert the timestamp string to std::time_t
                std::tm tm = {};
                std::istringstream timestampStream(timestamp);
                timestampStream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
                std::time_t time = std::mktime(&tm);

                if (new_class_key == "AA")
                    requestStack.emplace(Datamanager::students_map[student_code],
                                         type,Datamanager::classes_map[class_key],time);
                else requestStack.emplace(Datamanager::students_map[student_code],
                                          type,Datamanager::classes_map[class_key], Datamanager::classes_map[new_class_key],
                                          time);
            }
        }
        inputFile.close();
    } else {
        std::cerr << "Failed to open the file for reading." << std::endl;
    }
    Datamanager::request_log = requestStack;
    while(!requestStack.empty()){
        int student_code = requestStack.top().getRequest_student().getStudent_code();
        Class request_class = requestStack.top().getRequest_class();
        std::string class_key = request_class.getClass_key();
        Student student = requestStack.top().getRequest_student();
        const std::vector<Schedule>& class_schedule = request_class.getSchedules();
        if (requestStack.top().getRequest_type() == "Add") {
                Datamanager::classes_map[class_key].addStudent(&Datamanager::students_map[student_code]);
                Datamanager::students_map[student_code].addClass(request_class);
                Datamanager::students_map[student_code].addStudent_schedule(class_schedule);
                requestStack.pop();
        }
        else if (requestStack.top().getRequest_type() == "Remove") {

                Datamanager::classes_map[class_key].removeStudent(&Datamanager::students_map[student_code]);
                Datamanager::students_map[student_code].removeClass(request_class);
                Datamanager::students_map[student_code].removeStudent_schedules(class_schedule);
                requestStack.pop();
            }
        else{
                Datamanager::classes_map[requestStack.top().getRequest_newclass().getClass_key()].addStudent(&Datamanager::students_map[student_code]);
                Datamanager::students_map[student_code].addClass(requestStack.top().getRequest_newclass());
                Datamanager::students_map[student_code].addStudent_schedule(requestStack.top().getRequest_newclass().getSchedules());
                Datamanager::classes_map[class_key].removeStudent(&Datamanager::students_map[student_code]);
                Datamanager::students_map[student_code].removeClass(request_class);
                Datamanager::students_map[student_code].removeStudent_schedules(class_schedule);
                requestStack.pop();
            }
    }
}
/**@return Changes the class cap
 * Time Complexity 0(1)
 */
void Datamanager::changeClass_cap(){
    int new_class_cap;
    std::cout << "Enter new class cap" << std::endl;
    std::cin >> new_class_cap;
    Datamanager::class_cap = new_class_cap;
    std::cout << "Class cap changed to " << new_class_cap << std::endl;
}





