#include "../inc/ush.h"
// Function to execute builtin commands
int exec_own_cmds(char** parsed) {
    int amount = 6, switch_args = 0;
    char* cmd_list[amount];
    char* username;
    cmd_list[0] = "exit";
    cmd_list[1] = "cd";
    cmd_list[2] = "pwd";
    cmd_list[3] = "hello";
    cmd_list[4] = "export";
    cmd_list[5] = "unset";
  
    for (int i = 0; i < amount; i++) {
        if (mx_strcmp(parsed[0], cmd_list[i]) == 0) {
            switch_args = i + 1;
            break;
        }
    }
    switch (switch_args) {
    case 1:
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        mx_pwd();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
        return 1;
    case 5:
        mx_export(parsed);
        return 1;
    case 6:        
        mx_unset(parsed);
        return 1;
    default:
        break;
    }
    return 0;
}
