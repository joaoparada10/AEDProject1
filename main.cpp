#include <iostream>
#include "Class.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<Class> classes = readClassesCSV("/home/joao/AED23/AEDProject1/Data/schedule/classes.csv");
    for (Class &c: classes) {
        std::cout << "Class Code: " << c.getCode() << std::endl;
        std::cout << "UC Code: " << c.getUcCode() << std::endl;
        std::cout << "Weekday: " << c.getWeekday() << std::endl;
        std::cout << "Start Hour: " << c.getStartHour() << std::endl;
        std::cout << "Duration: " << c.getDuration() << std::endl;
        std::cout << "Type: " << c.getType() << std::endl;

    }

        return 0;

}
