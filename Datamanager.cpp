//
// Created by joao on 29-10-2023.
//

#include "Datamanager.h"
std::unordered_map<std::string, Class> Datamanager::empty_classes_map;
std::unordered_map<std::string, Class> Datamanager::classes_map;
std::unordered_map<int, Student> Datamanager::students_map;

std::unordered_map<std::string, Class> Datamanager::getEmpty_classes_map() {
    empty_classes_map = Filereader::classMap("/home/joao/AED23/AEDProject1/Data/schedule/classes_per_uc.csv");
    return empty_classes_map;
}

std::unordered_map<std::string, Class> Datamanager::getClasses_map() {
    classes_map = Filereader::readClassesCSV("/home/joao/AED23/AEDProject1/Data/schedule/classes.csv\"");
    return classes_map;
}

std::unordered_map<int, Student> Datamanager::getStudent_map() {
    students_map = Filereader::readStudentClassesCSV("/home/joao/AED23/AEDProject1/Data/schedule/students_classes.csv");
    return students_map;
}


