#include "../inc/ush.h"

int main() {
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    int execFlag = 0;
    while (true) {
        // take input
        if (get_input(inputString))
            continue;
        // process
        execFlag = validate_input(inputString, parsedArgs);
        // execflag returns zero if there is no command
        // or it is a builtin command,
        // 1 if it is a simple command
  
        // execute
        if (execFlag)
            exec_sys_cmds(parsedArgs);
    }
    return 0;
}

