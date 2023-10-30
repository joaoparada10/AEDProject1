//
// Created by joao on 29-10-2023.
//

#ifndef AEDPROJECT1_DATAMANAGER_H
#define AEDPROJECT1_DATAMANAGER_H


#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include "Student.h"
#include "Filereader.h"

class Datamanager {
private:
    static std::unordered_map<std::string, Class> empty_classes_map;
    static std::unordered_map<int, Student> students_map;

public:
    static Datamanager& getInstance() {
        static Datamanager instance;
        return instance;
    }

    static std::unordered_map<std::string, Class> getEmpty_classes_map();


    static std::unordered_map<std::string, Class>getClasses_map();

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
    // You can add methods to initialize, update, or manipulate the maps here.
    static std::unordered_map<std::string, Class> classes_map;
};



#endif //AEDPROJECT1_DATAMANAGER_H
