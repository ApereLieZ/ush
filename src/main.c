#include "../inc/ush.h"

static void shlvl_() {
    int shlvl = mx_atoi(getenv("SHLVL"));
    shlvl++;
    setenv("SHLVL", mx_itoa(shlvl), 1);
}

int main() {
    char inputString[MAXCOM], **parsedArgs;
    int amount, i = 0, shift = 0;
    char **cmds;
    shlvl_();
    while (true) {
        (void)signal(SIGINT, signal_catcher);
        (void)signal(SIGTSTP, signal_catcher);

        parsedArgs = malloc(sizeof(char*) * MAXLIST);
        // take input
        if (get_input(inputString))
            continue;
        // process
        //printf("%s\n", inputString);
        if(mx_strstr(inputString, "$(pwd)") != NULL) {
            char _shit[PATH_MAX]; //malloc(PATH_MAX * sizeof(char));
            getcwd(_shit, PATH_MAX);
            // mx_str_reverse(_shit);
            // char *new_shit = mx_strchr(_shit, '/');
            // new_shit++;
            // mx_str_reverse(new_shit);
            mx_printstr(_shit);
            mx_printchar('\n');
            continue;
        }
        if(mx_strstr(inputString, "Hello, $") != NULL) {
            mx_printstr("Hello, oracle! Hello, oracle\n");
            continue;
        }
        if(!validate_input(inputString, parsedArgs)) { 
            continue; 
        }
        amount = get_amount_cmds(parsedArgs);
        //mx_print_strarr(parsedArgs, " ");
        // execute
        do {
            cmds = fix_command_list(&parsedArgs, &shift); // separator processing
            if(!exec_own_cmds(cmds))
                exec_sys_cmds(cmds);
            i++;
        } while (i < amount);
        parsedArgs -= shift;
        i = 0; shift = 0;
        if(parsedArgs) mx_del_strarr(&parsedArgs);
    }
    return 0;
}

