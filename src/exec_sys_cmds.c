#include "../inc/ush.h"

// Function where the system command is executed
void exec_sys_cmds(char** parsed) {
    pid_t pid = fork(); 

    if (pid == -1) {
        mx_printerr("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            mx_printerr("ush: command not found: ");
            mx_printerr(parsed[0]);
            mx_printerr("\n");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}
