#include <iostream>
#include "Class.h"
#include "Student.h"
#include "Datamanager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::unordered_map<std::string, Class> classes = Datamanager::getEmpty_classes_map();
    std::unordered_map<std::string, Class> classMap = Datamanager::getClasses_map();
    printClassSchedules(classMap);
    std::unordered_map<int,Student> studentMap = Datamanager::getStudent_map();

    for (const auto& pair : studentMap) {
        Student student = pair.second;

        std::cout << "Student Code: " << student.getStudent_code() << std::endl;
        std::cout << "Student Name: " << student.getStudent_name() << std::endl;

    }
        int mainChoice;

        while (true) {
            std::cout << "Main Menu" << std::endl;
            std::cout << "1. Consult" << std::endl;
            std::cout << "2. Requests" << std::endl;
            std::cout << "3. Exit" << std::endl;
            std::cout << "Enter your choice: ";

            std::cin >> mainChoice;

            switch (mainChoice) {
                case 1:
                    int consultChoice;
                    while (true) {
                        std::cout << "Consult Menu" << std::endl;
                        std::cout << "1. Consult Student Schedule" << std::endl;
                        std::cout << "2. Consult Class Schedule" << std::endl;
                        std::cout << "3. Consult Class Students" << std::endl;
                        std::cout << "4. Consult UC Students" << std::endl;
                        std::cout << "5. Consult Students by Year" << std::endl;
                        std::cout << "6. Back to Main Menu" << std::endl;
                        std::cout << "Enter your choice: ";
                        std::cin >> consultChoice;
                        switch (consultChoice) {
                            case 1:
                                Datamanager::consultStudent_schedule();
                                break;
                            case 2:
                                Datamanager::consultClass_schedule();
                                break;
                            case 3:
                                Datamanager::consultStudents_in_class();
                                break;
                            case 4:
                                Datamanager::consultStudentsByUCCode();
                                break;
                            case 5:
                                Datamanager::consultStudentsByYear();
                                break;
                            case 6:
                                break;
                            default:
                                std::cout << "Invalid choice. Please try again." << std::endl;
                        }
                    }
                    break;
                case 2:
                    int requestsChoice;
                    while (true) {
                        std::cout << "Requests Menu" << std::endl;
                        std::cout << "1. See Requests" << std::endl;
                        std::cout << "2. Create New Request" << std::endl;
                        std::cout << "3. Cancel Request" << std::endl;
                        std::cout << "4. See Request Log" << std::endl;
                        std::cout << "5. Back to Main Menu" << std::endl;
                        std::cout << "Enter your choice: ";
                        std::cin >> requestsChoice;
                        switch (requestsChoice) {
                            case 1:
                                break;
                            case 2:
                                break;
                            case 3:
                                break;
                            case 4:
                                break;
                            case 5:
                                // Return to the main menu
                                break;
                            default:
                                std::cout << "Invalid choice. Please try again." << std::endl;
                        }
                    }
                    break;
                case 3:
                    std::cout << "Exiting..." << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }

        return 0;
}
