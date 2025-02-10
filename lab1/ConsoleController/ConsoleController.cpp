#include "ConsoleController.h"

#include <termios.h>
#include <unistd.h>

namespace ConsoleController {
void ConsoleController(bool isCanon, bool isEchoOn) {
    struct termios currentState = {};
    tcgetattr(STDIN_FILENO, &currentState);
    struct termios newState = currentState;
    if (isCanon) {
        newState.c_lflag |= (ICANON);
    } else {
        newState.c_lflag &= (~ICANON);
    }
    if (isEchoOn) {
        newState.c_lflag |= (ECHO);
    } else {
        newState.c_lflag &= (~ECHO);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &newState);
}
}  // namespace ConsoleController
