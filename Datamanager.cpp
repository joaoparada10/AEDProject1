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
        for (Schedule schedule: student_schedule) {
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
        for (Schedule schedule: schedules) {
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