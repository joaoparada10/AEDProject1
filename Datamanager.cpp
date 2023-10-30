//
// Created by joao on 29-10-2023.
//

#include "Datamanager.h"
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
    std::vector<Student*> studentsWithUCCode;

    // Iterate through the classes
    for (const auto& classPair : Datamanager::classes_map) {
        const Class& classObj = classPair.second;

        // Check if the class's UC code matches the desired UC code
        if (classObj.getUc_code() == uc_code) {
            // Retrieve students associated with this class
            const std::vector<Student *> studentsInClass = classObj.getStudents();
            for (Student *student: studentsInClass) {
                std::cout << "Student Code: " << student->getStudent_code() << std::endl;
                std::cout << "Student Name: " << student->getStudent_name() << std::endl;
                // Print other student information as needed
            }

            // Append students to the list
        }
    }

    // Now, studentsWithUCCode contains all students with the desired UC code
    // You can further process or display this list of students as needed.
}


