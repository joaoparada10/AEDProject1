#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Class.h"
#include "Student.h"// Include your class header here

class Filereader {
private:
public:
    static std::unordered_map<std::string, Class> classMap(const std::string &filename);
    static std::unordered_map<std::string, Class> readClassesCSV(const std::string &filename);
    static std::unordered_map<int, Student> readStudentClassesCSV(const std::string &filename);
};

#endif

