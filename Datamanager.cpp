//
// Created by joao on 29-10-2023.
//

#include <map>
#include "Datamanager.h"
#include "Student.h"
std::unordered_map<std::string, Class> Datamanager::empty_classes_map;
std::unordered_map<std::string, Class> Datamanager::classes_map;
std::unordered_map<int, Student> Datamanager::students_map;

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

    // Check if the student with the given student_code exists
    if (students_map.find(student_code) == students_map.end()) {
        std::cout << "Student with code " << student_code << " not found." << std::endl;
        return;
    }

    // Get the student's schedule
    Student student = students_map[student_code];
    const std::vector<Schedule>& student_schedule = student.getStudent_schedule();

    if (student_schedule.empty()) {
        std::cout << "Student with code " << student_code << " has no schedule." << std::endl;
    } else {
        std::cout << "Student Schedule for : " << student.getStudent_name() << std::endl;
        for (Schedule schedule : student_schedule) {
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
    std::vector<Schedule> schedules; // Create a vector to store the schedules

    for (const auto& classEntry : classes_map) {
        const Class& currentClass = classEntry.second;

        // Check if the class_code matches
        if (currentClass.getClass_code() == class_code) {
            // Get the schedules for this class and append them to the vector
            const std::vector<Schedule>& classSchedules = currentClass.getSchedules();
            schedules.insert(schedules.end(), classSchedules.begin(), classSchedules.end());
        }
    }

    // Now 'schedules' contains all the schedules for the specified class_code
    if (schedules.empty()) {
        std::cout << "No schedules found for class code: " << class_code << std::endl;
    } else {
        std::cout << "Schedules for class code: " << class_code << std::endl;
        for (Schedule schedule : schedules) {
            // Print the schedule details
            std::cout << "Weekday: " << schedule.getWeekday() << std::endl;
            std::cout << "Start Hour: " << schedule.getStart_hour() << std::endl;
            std::cout << "Duration: " << schedule.getDuration() << " hours" << std::endl;
            std::cout << "Type: " << schedule.getType() << std::endl;
            std::cout << std::endl;
        }
    }
}
bool compareStudentsByName(Student *student1, Student *student2) {
    return student1->getStudent_name() < student2->getStudent_name();
}
void Datamanager::consultStudents_in_class() {
    std::string class_code, uc_code, key;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::cout << "Enter class: ";
    std::cin >> class_code;
    key = uc_code + class_code;
    classes_map[key].getStudents();
    // Iterate and print the sorted list of students
    for (Student *student : classes_map[key].getStudents()) {
        std::cout << "Student Code: " << student->getStudent_code() << std::endl;
        std::cout << "Student Name: " << student->getStudent_name() << std::endl;
        // Print other student information as needed
    }
}

void Datamanager::consultStudentsByUCCode() {
    std::string uc_code;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::set<Student> studentsWithUCCode;

    // Iterate through the classes
    for (const auto& classPair : Datamanager::classes_map) {
        const Class& classObj = classPair.second;

        // Check if the class's UC code matches the desired UC code
        if (classObj.getUc_code() == uc_code) {
            // Retrieve students associated with this class
            const std::vector<Student*>& studentsInClass = classObj.getStudents();
            for (const Student* student: studentsInClass) {
                studentsWithUCCode.insert(*student);
                // Print other student information as needed
            }

            // Append students to the list
        }
    }
    for (Student student_ptr : studentsWithUCCode) {
        std::cout << "Student Code: " << student_ptr.getStudent_code() << ", Student Name: " << student_ptr.getStudent_name() << "\n";
    }

    // Now, studentsWithUCCode contains all students with the desired UC code
    // You can further process or display this list of students as needed.
}
void Datamanager::consultStudentsByYear() {
    int year;
    std::cout << "Enter the year: ";
    std::cin >> year;

    std::set<Student> uniqueStudents;

    // Iterate through the classes
    for (const auto& classPair : Datamanager::classes_map) {
        const Class& classObj = classPair.second;

        // Check if the first character of the class_code matches the desired year
        if (classObj.getClass_code()[0] - '0' == year) {
            // Retrieve students associated with this class
            const std::vector<Student*>& studentsInClass = classObj.getStudents();

            // Add students to the set to ensure uniqueness
            for (const Student* student_ptr : studentsInClass) {
                if (student_ptr ){
                uniqueStudents.insert(*student_ptr);}
            }
        }
    }

    // Now, uniqueStudents contains unique students from the desired year
    // Print the unique students
    for (Student student_ptr : uniqueStudents) {
        std::cout << "Student Code: " << student_ptr.getStudent_code() << ", Student Name: " << student_ptr.getStudent_name() << "\n";
    }
}

void Datamanager::countStudentsInNOrMoreUCs() {
    int n;
    std::cout << "Enter number of UCs: ";
    std::cin >> n;

    int count = 0;

    // Iterate through all students
    for (const auto& pair : Datamanager::students_map   ) {
        Student student = pair.second;
        const std::vector<Class>& classes = student.getClasses();

        // Count the number of unique UCs
        std::unordered_set<std::string> uniqueUCs;
        for (const Class& class1 : classes) {
            uniqueUCs.insert(class1.getUc_code());
        }

        // Check if the student is registered in at least 'n' UCs
        if (uniqueUCs.size() >= n) {
            count++;
        }
    }
    std::cout << "There are " << count << " students registered in " << n << " or more UCs.";
}

void Datamanager::consultClassOccupation() {
    std::string uc_code, class_code;
    std::cout << "Enter UC Code: ";
    std::cin >> uc_code;
    std::cout << "Enter Class code: ";
    std::cin >> class_code;
    std::string key = uc_code + class_code;
        const std::vector<Student *> &students = classes_map[key].getStudents();

    std::cout << "The class " << class_code << " of " << uc_code << " has " << students.size() << " students!" << std::endl;

}
void Datamanager::consultYearOccupation() {
    int year;
    std::string ordinal;
    std::cout << "Enter year: ";
    std::cin >> year;
    switch(year){
        case 1: ordinal = "st";
            break;
        case 2: ordinal = "nd";
            break;
        case 3: ordinal = "rd";
            break;
        default: ordinal = "th";
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
    std::cout << "There are " << uniqueStudents.size() << " students registered in the " << year << ordinal << " year!" << std::endl;
}
void Datamanager::consultUcOccupation() {
    std::string uc_code;
    std::cout << "Enter UC: ";
    std::cin >> uc_code;
    std::set<Student> studentsWithUCCode;
    for (const auto& classPair : Datamanager::classes_map) {
        const Class& classObj = classPair.second;
        if (classObj.getUc_code() == uc_code) {
            const std::vector<Student*>& studentsInClass = classObj.getStudents();
            for (const Student* student: studentsInClass) {
                studentsWithUCCode.insert(*student);
            }
        }
    }
    std::cout << "There are " << studentsWithUCCode.size() << " students registered in " << uc_code << "!" << std::endl;
}

void Datamanager::consultGreatestUcs() {
    std::unordered_map<std::string, int> ucOccupation; // Map to store UC codes and their student counts

    // Iterate through all classes
    for (const auto& classPair : Datamanager::classes_map) {
        const Class& classObj = classPair.second;
        const std::string uc_code = classObj.getUc_code();
        const std::vector<Student*>& studentsInClass = classObj.getStudents();

        // Increment the student count for the corresponding UC code
        ucOccupation[uc_code] += studentsInClass.size();
    }
    std::multimap<int, std::string, std::greater<int>> sortedUcs;
    for (const auto& entry : ucOccupation) {
        sortedUcs.insert(std::make_pair(entry.second, entry.first));
    }
    int count = 0;
    int n;
    std::cout << "Enter number of UCs: " << std::endl;
    std::cin >> n;
    std::cout << "Top " << n <<" UCs by Occupation: " << std::endl;
    for (const auto& entry : sortedUcs) {
        std::cout << "UC " << entry.second << ": " << entry.first << " students" << std::endl;
        count++;
        if (count >= n) {
            break;
        }

    }
}