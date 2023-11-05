/**
 * @file main.cpp
 * @brief The main function for the Very Optimized Schedule Manager.
 *
 * This function presents a menu-driven interface that allows users to consult
 * and manage schedules and requests.
 * Users can choose between "Consult" and "Requests" options and navigate through submenus.
 *
 * @return Returns 0 upon successful execution.
 */
/**
* @mainpage Very Optimized Schedule Manager Documentation
*
* Welcome to the documentation for the Very Optimized Schedule Manager program. This documentation provides an overview
* of the program's functionalities and usage.
*
* @subpage Consult
* @subpage Requests
* @subpage Extra Functions Subpage
*@tableofcontents

* @section save_request_log_data Save Request Log Data
* Allows the user to save the request log to a file.
* @section load_request_log_data Load Request Log Data
* Allows the user to load the request log.

*@authors
 * - João Parada
 * - Luciano Ferreira
 * - António Cunha
*/

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
        std::cout << "4. Save Request Log" << std::endl;
        std::cout << "5. Load Request Log" << std::endl;
        std::cout << "6. Exit" << std::endl;
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
                    /** @page Consult Consult Subpage
                   *
                   * @tableofcontents
                   *
                   * @section consult_intro Introduction
                   * The "Consult" section allows users to perform various consultation tasks.
                   *
                   * @section consult_options Available Options
                   * Users can choose from the following options:
                   * - [Consult Student Schedule](#consult_student_schedule)
                   * - [Consult Class Schedule](#consult_class_schedule)
                   * - [Consult Class Students](#consult_class_students)
                   * - [Consult UC Students](#consult_uc_students)
                   * - [Consult Students by Year](#consult_students_by_year)
                   * - [Count Students in N or more UCs](#count_students_in_n_or_more_ucs)
                   * - [Consult Class Occupation](#consult_class_occupation)
                   * - [Consult Year Occupation](#consult_year_occupation)
                   * - [Consult UC Occupation](#consult_uc_occupation)
                   * - [Consult UCs with most students](#consult_ucs_with_most_students)
                   */
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
                /** @page Requests Requests Subpage
                     * @tableofcontents
                     *
                     * @section requests_intro Introduction
                     * The "Requests" section allows users to handle various request-related tasks.
                     *
                     * @section requests_options Available Options
                     * Users can choose from the following options:
                     * - [See Requests](#see_requests)
                     * - [Create Add Request](#create_add_request)
                     * - [Create Remove Request](#create_remove_request)
                     * - [Create Switch Request](#create_switch_request)
                     * - [Process Next Request](#process_next_request)
                     * - [Process All Remaining Requests](#process_all_remaining_requests)
                     * - [Undo All Requests](#undo_all_requests)
                       */
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
                /**
                 * @page Extra Extra Functions Subpage
                 *
                 * @tableofcontents
                 *
                 * @section extra_intro Introduction
                 * The "Extra Functions" section provides access to various additional functions.
                 *
                 * @section extra_options Available Options
                 * Users can choose from the following options:
                 * - [See Request Log](#see_request_log)
                 * - [Check Student Avg per UC](#check_student_avg_per_uc)
                 * - [Check Course Class Occupation](#check_course_class_occupation)
                 * - [Change Class Cap](#change_class_cap)
                 * - [Exit to Main Menu](#exit_to_main_menu)
                 *
                 * @subsection see_request_log 1. See Request Log
                 * This option allows you to view the request log.
                 *
                 * @subsection check_student_avg_per_uc 2. Check Student Avg per UC
                 * Use this option to check the student average per UC.
                 *
                 * @subsection check_course_class_occupation 3. Check Course Class Occupation
                 * This option helps you check the occupation of course classes.
                 *
                 *  @subsection change_class_cap 4. Change Class Cap
                 * This option allows you to change the class cap.
                 *
                 * @subsection exit_to_main_menu 5. Exit to Main Menu
                 * Choose this option to return to the main menu.
                 */

                int extra_choice;

                while(true){
                    std::cout << "Extra Functions Menu" << std::endl;
                    std::cout << "1. See Request Log" << std::endl;
                    std::cout << "2. Check Student Avg per UC" << std::endl;
                    std::cout << "3. Check Course Class Occupation" << std::endl;
                    std::cout << "4. Change Class Cap" << std::endl;
                    std::cout << "5. Exit to Main Menu" << std::endl;
                    std::cin >> extra_choice;
                    switch(extra_choice) {
                        case 1: Datamanager::seeRequest_log();
                            break;
                        case 2: Datamanager::setAverage_Nstudents_perUC();
                            break;
                        case 3: Datamanager::consultCourseClassOccupation();
                            break;
                        case 4:
                            Datamanager::changeClass_cap();
                            break;
                        case 5: break;
                        default:    std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                    if (extra_choice == 5) break;
                }
                break;
            case 4:

                Datamanager::saveRequest_log_data("../Data/requestlogdata.txt");
                std::cout << "Request log saved!" << std::endl;
                break;
            case 5:
                Datamanager::loadRequest_log("../Data/requestlogdata.txt");
                std::cout << "Request log loaded!" << std::endl;
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }

    }

}


