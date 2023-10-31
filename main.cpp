#include <iostream>
#include "Datamanager.h"

int main() {
    std::cout << "Very optimized schedule manager!" << std::endl;
    Datamanager::getEmpty_classes_map();
    Datamanager::getClasses_map();
    Datamanager::getStudent_map();
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
                    std::cout << "6. Count Students in N or more UCs" << std::endl;
                    std::cout << "7. Consult Class Occupation" << std::endl;
                    std::cout << "8. Consult Year Occupation" << std::endl;
                    std::cout << "9. Consult Uc     Occupation" << std::endl;
                    std::cout << "10. Consult UCs with most students" << std::endl;
                    std::cout << "11. Back to Main Menu" << std::endl;
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
                            Datamanager::countStudentsInNOrMoreUCs();
                            break;
                        case 7:
                            Datamanager::consultClassOccupation();
                            break;
                        case 8:
                            Datamanager::consultYearOccupation();
                            break;
                        case 9:
                            Datamanager::consultUcOccupation();
                            break;
                        case 10:
                            Datamanager::consultGreatestUcs();
                            break;
                        case 11:
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                    if (consultChoice == 11) break;
                    case 2:
                        int requestsChoice;
                    while (true) {
                        std::cout << "Requests Menu" << std::endl;
                        std::cout << "1. See Requests" << std::endl;
                        std::cout << "2. Create New Request" << std::endl;
                        std::cout << "3. Cancel Request" << std::endl;
                        std::cout << "4. See Request Log" << std::endl;
                        std::cout << "5. Check Student Avg per UC" << std::endl;
                        std::cout << "6. Back to Main Menu" << std::endl;
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
                                Datamanager::setAverage_Nstudents_perUC();
                                break;
                            default:
                                std::cout << "Invalid choice. Please try again." << std::endl;
                                break;
                        }
                        if (requestsChoice == 6) break;
                    }
                    case 3:
                        std::cout << "Exiting..." << std::endl;
                    return 0;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
        }
    }
}
