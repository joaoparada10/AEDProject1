/**
 * @file Datamanager.h
 * @brief Header file for the Datamanager class which
 * supports all the functionalities of the program
 */

#ifndef AEDPROJECT1_DATAMANAGER_H
#define AEDPROJECT1_DATAMANAGER_H

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <stack>
#include <queue>
#include <chrono>
#include <ctime>
#include "Student.h"
#include "Filereader.h"
#include "Request.h"

class Datamanager {
public:
    static std::unordered_map<std::string, Class> getEmpty_classes_map();
    static std::unordered_map<std::string, Class> getClasses_map();
    static std::unordered_map<int, Student> getStudent_map();
    /**@brief This method allows the user to consult a student's schedule */
    static void consultStudent_schedule();
    /**@brief This method allows the user to consult a class schedule. */
    static void consultClass_schedule();
    /**@brief This method allows the user to consult the list of students in a specific class. */
    static void consultStudents_in_class();
    /**@brief This method allows the user to consult students by UC  code. */
    static void consultStudentsByUCCode();
    /**@brief This method allows the user to consult students by their year of study.*/
    static void consultStudentsByYear();
    /**@brief This method counts students who are enrolled in N or more UCs*/
    static void countStudentsInNOrMoreUCs();
    /**@brief This method allows the user to consult the occupation of a class. */
    static void consultClassOccupation();
    /**@brief This method allows the user to consult the
     * occupation of every class in the course. */
    static void consultCourseClassOccupation();
    /**@brief This method allows the user to consult the occupation of a specific academic year.*/
    static void consultYearOccupation();
    /**@brief This method allows the user to consult the occupation of a UC.*/
    static void consultUcOccupation();
    /**@brief This method allows the user to consult the N UCs with the most students. */
    static void consultGreatestUcs();
    static std::unordered_map<std::string, Class> empty_classes_map;
    static std::unordered_map<std::string, Class> classes_map;
    static std::unordered_map<int, Student> students_map;
    static std::stack<Request> request_log;
    static std::queue<Request> requests;
    static int class_cap;
    /**@brief This method shows the average number of students per class in each UC*/
    static void setAverage_Nstudents_perUC();
    /**@brief This method allows the user to see the requests on the queue*/
    static void seeRequests();
    /**@brief This method allows the user to see the request log*/
    static void seeRequest_log();
    /**@brief This method creates an Add request*/
    static void createAdd_request();
    /**@brief This method creates a Remove request*/
    static void createRemove_request();
    /**@brief This method creates a Switch request*/
    static void createSwitch_request();
    /**@brief This method checks if the front request is valid or not and processes it accordingly  */
    static void processNext_request();
    /**@brief This method calls processNext_request until the request queue is empty*/
    static void processRemaining_requests();
    /**@brief This method saves every processed request to a file*/
    static void saveRequestLogToFile(Request request);
    /**@brief This method undoes the past request*/
    static void undoLast_request();
    /**@brief This method undoes all past requests*/
    static void undoAll_requests();
    /**@brief This method saves the request log to a file so it can be loaded later */
    static void saveRequest_log_data(const std::string &filename);
    /**@brief This method loads the saved request log*/
    static void loadRequest_log(const std::string &filename);
    /**@brief This method allows the user to temporarily change the class cap */
    static void changeClass_cap();
};

#endif