#include "../inc/ush.h"

pid_t ush_pid;

void signal_catcher(int sig) { 
  switch(sig) {
    case SIGINT:
        printf("catch SIGINT pid %d\n", child_pid);
        kill(child_pid, sig);
        (void)signal(SIGINT, SIG_DFL); 
        break;
    case SIGTSTP:
        printf("catch SIGTSTP pid %d\n", child_pid);
        //system(mx_strjoin("kill -SIGSTOP ", mx_itoa(child_pid)))
        kill(child_pid, sig);
        // kill(getpid(), SIGINT);
        printf("pid ush %d\n", getpid());
        char **dick = malloc(sizeof(char *) * 1);
        dick[0] = mx_strdup("./ush");
        exec_sys_cmds(dick);
        //system("./ush");
        exit(0);
        (void)signal(SIGTSTP, SIG_DFL); 
        break;
    case SIGCONT:
        printf("catch SIGCONT cont\n");
        kill(child_pid, sig);
        (void)signal(SIGCONT, SIG_DFL);
        break; 
    default:
        (void)signal(sig, SIG_IGN); 
  }
  
}

int main() {
    //printf("ppid %d\n",getppid());
    //if(getppid() != 2551) system(mx_strjoin("kill -9 ", mx_itoa(getppid())));
    add_history("./ush");
    char inputString[MAXCOM], **parsedArgs;
    int amount, i = 0, shift = 0;
    char **cmds;
    while (true) {
        (void)signal(SIGINT, signal_catcher);
        (void)signal(SIGTSTP, signal_catcher);
        (void)signal(SIGCONT, signal_catcher);


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

