#include "../inc/ush.h"

void signal_catcher(int sig) { 
  switch(sig) {
    case SIGINT:
        printf("catch signal\n");
        kill(getpid(), sig);
        break;
    case SIGTERM:
        printf("catch signal sigterm\n");
        kill(getpid(), sig);
        break;
  }
  (void)signal(SIGINT, SIG_DFL); 
}

int main() {
    char inputString[MAXCOM], **parsedArgs;
    int amount, i = 0, shift = 0;
    char **cmds;
    while (true) {
        (void)signal(SIGINT, signal_catcher);
        (void)signal(SIGTERM, signal_catcher);

        parsedArgs = malloc(sizeof(char*) * MAXLIST);
        // take input
        if (get_input(inputString))
            continue;
        // process
        validate_input(inputString, parsedArgs);
        amount = get_amount_cmds(parsedArgs);
        // execute
        do {
            cmds = fix_command_list(&parsedArgs, &shift); // separator processing
            if(!exec_own_cmds(cmds))
                exec_sys_cmds(cmds);
            i++;
        } while (i < amount);
        parsedArgs -= shift;
        i = 0; shift = 0;
        free(parsedArgs);
        parsedArgs = NULL;
    }
    return 0;
}

