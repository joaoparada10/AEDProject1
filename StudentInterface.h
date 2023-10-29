#ifndef STUDENT_INTERFACE_H
#define STUDENT_INTERFACE_H

class StudentInterface {
public:
    virtual ~StudentInterface() {}
    void addStudent(Student student);
    // Define the interface methods that Student objects need to access.
};

#endif
