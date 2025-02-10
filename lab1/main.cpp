#include <iostream>
#include "ConsoleController/ConsoleController.h"
#include "newmath/newmath.h"

int main() {
    std::cout << "One, two, three, four, five plus five = ";
    std::cout << newmath::sum(1, newmath::sum(2, newmath::sum(3, newmath::sum(4, newmath::sum(5, 5))))) << std::endl;

    ConsoleController::ConsoleController(false, false);
    char keystroke = ' ';
    int counter = 0;
    while (counter < 1000) {
        std::cout << "Press a key! ";
        fread(&keystroke, 1, 1, stdin);
        std::cout << "You pressed [" << keystroke << "] (" << static_cast<int>(keystroke) << ")\n";
        std::cout << counter << " + " << static_cast<int>(keystroke) << " = ";
        counter = newmath::sum(counter, static_cast<int>(keystroke));
        std::cout << counter << '\n';
    }

    ConsoleController::ConsoleController(true, true);
    return 0;
}
