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
        std::cout << "3. Extra Functions" << std::endl;
        std::cout << "4. Exit" << std::endl;
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
                    std::cout << "6. Count Number of Students in N or more UCs" << std::endl;
                    std::cout << "7. Consult Class Occupation" << std::endl;
                    std::cout << "8. Consult Year Occupation" << std::endl;
                    std::cout << "9. Consult Uc Occupation" << std::endl;
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
                }
                break;

            case 2:
                int requestsChoice;
                while (true) {
                    std::cout << "Requests Menu" << std::endl;
                    std::cout << "1. See Requests" << std::endl;
                    std::cout << "2. Create Add Request" << std::endl;
                    std::cout << "3. Create Remove Request" << std::endl;
                    std::cout << "4. Create Switch Request" << std::endl;
                    std::cout << "5. Process Next Request" << std::endl;
                    std::cout << "6. Process All Remaining Requests" << std::endl;
                    std::cout << "7. Undo Last Request" << std::endl;
                    std::cout << "8. Undo All Requests" << std::endl;
                    std::cout << "9. Back to Main Menu" << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> requestsChoice;
                    switch (requestsChoice) {
                        case 1:
                            Datamanager::seeRequests();
                            break;
                        case 2:
                            Datamanager::createAdd_request();
                            break;
                        case 3:
                            Datamanager::createRemove_request();
                            break;
                        case 4:
                            Datamanager::createSwitch_request();
                            break;
                        case 5:
                            Datamanager::processNext_request();
                            break;
                        case 6:
                            Datamanager::processRemaining_requests();
                            break;
                        case 7:
                            Datamanager::undoLast_request();
                            break;
                        case 8:
                            Datamanager::undoAll_requests();
                            break;
                        case 9:
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                    if (requestsChoice == 9) break;
                }
                break;
            case 3:
                int extra_choice;
                while(true){
                    std::cout << "Extra Functions Menu" << std::endl;
                    std::cout << "1. See Request Log" << std::endl;
                    std::cout << "2. Check Student Avg per UC" << std::endl;
                    std::cout << "3. Check Course Class Occupation" << std::endl;
                    std::cout << "4. Exit to Main Menu" << std::endl;
                    std::cin >> extra_choice;
                    switch(extra_choice) {
                        case 1: Datamanager::seeRequest_log();
                        break;
                        case 2: Datamanager::setAverage_Nstudents_perUC();
                        break;
                        case 3: Datamanager::consultCourseClassOccupation();
                        break;
                        case 4:
                            break;
                        default:    std::cout << "Invalid choice. Please try again." << std::endl;
                        break;
                    }
                    if (extra_choice == 4) break;
                }
                break;

            case 4:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

