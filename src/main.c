#include "../inc/ush.h"

void signal_catcher(int sig) { 
  switch(sig) {
    case SIGINT:
        exit(0);
  }
}

int main() {
    char inputString[MAXCOM], **parsedArgs;
    int amount, i = 0;
    char **cmds;
    while (true) {
        (void)signal(SIGINT, signal_catcher);

        parsedArgs = malloc(sizeof(char*) * MAXLIST);
        // take input
        if (get_input(inputString))
            continue;
        // process
        validate_input(inputString, parsedArgs);
        amount = get_amount_cmds(parsedArgs);
        // execute
        do {
            cmds = fix_command_list(&parsedArgs);
            if(!exec_own_cmds(cmds))
                exec_sys_cmds(cmds);
            i++;
        } while (i < amount);
        i = 0;
       //mx_del_strarr(&parsedArgs);
    }
    return 0;
}

