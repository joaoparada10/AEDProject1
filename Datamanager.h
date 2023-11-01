#ifndef AEDPROJECT1_DATAMANAGER_H
#define AEDPROJECT1_DATAMANAGER_H

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <stack>
#include <queue>
#include <chrono>
#include <ctime>
#include "Student.h"
#include "Filereader.h"
#include "Request.h"

class Datamanager {
public:
    static std::unordered_map<std::string, Class> getEmpty_classes_map();
    static std::unordered_map<std::string, Class> getClasses_map();
    static std::unordered_map<int, Student> getStudent_map();
    static void consultStudent_schedule();
    static void consultClass_schedule();
    static void consultStudents_in_class();
    static void consultStudentsByUCCode();
    static void consultStudentsByYear();
    static void countStudentsInNOrMoreUCs();
    static void consultClassOccupation();
    static void consultCourseClassOccupation();
    static void consultYearOccupation();
    static void consultUcOccupation();
    static void consultGreatestUcs();
    static std::unordered_map<std::string, Class> empty_classes_map;
    static std::unordered_map<std::string, Class> classes_map;
    static std::unordered_map<int, Student> students_map;
    static std::stack<Request> request_log;
    static std::queue<Request> requests;
    std::unordered_map<std::string, double> setAverage_Nstudents_perUC1();
    static void setAverage_Nstudents_perUC();
    static void seeRequests();
    static void seeRequest_log();
    static void createAdd_request();
    static void createRemove_request();
    static void createSwitch_request();
    static void processNext_request();
    static void processRemaining_requests();
    static void saveRequestLogToFile(Request request);
};

#endif