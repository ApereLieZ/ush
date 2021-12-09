#include "../inc/ush.h"

pid_t child_pid;

// Function where the system command is executed
void exec_sys_cmds(char** parsed) {
    pid_t pid = fork();
    child_pid = pid; 
    if (pid == -1) {
        mx_printerr("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        printf("child pid %d\n", getpid());
        if (execvp(parsed[0], parsed) < 0) {
            mx_printerr("ush: command not found: ");
            mx_printerr(parsed[0]);
            mx_printerr("\n");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        if(mx_strcmp(parsed[0], "./ush") != 0)
            wait(NULL); 
        return;
    }
}
