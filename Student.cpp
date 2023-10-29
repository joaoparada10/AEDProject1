#include "Student.h"
#include "Class.h"

Student::Student(){};
Student::Student(int student_code, std::string student_name){
    this->student_name = student_name;
    this->student_code = student_code;
}
std::string Student::getName() {
    return student_name;
}
 int Student::getStudent_code(){
    return student_code;
}
void Student::addClass(Class student_class) {
    student_classes.push_back(student_class);
}



/*void Student::fillSchedule(const std::vector<Class>& attendedClasses) {
    for (const Class& attendedClass : attendedClasses) {
        studentSchedule.addClass(attendedClass);
    }
}*/
/*Schedule Student::getSchedule() {

    return studentSchedule;
}*/



