#ifndef AEDPROJECT1_DATAMANAGER_H
#define AEDPROJECT1_DATAMANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include "Student.h"
#include "Filereader.h"

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
    static void consultYearOccupation();
    static void consultUcOccupation();
    static void consultGreatestUcs();
    static std::unordered_map<std::string, Class> empty_classes_map;
    static std::unordered_map<std::string, Class> classes_map;
    static std::unordered_map<int, Student> students_map;
    static void setAverage_Nstudents_perUC(std::unordered_map<std::string, Class> classes_map);
};

#endif