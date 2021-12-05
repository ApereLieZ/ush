#include "../inc/ush.h"

int validate_input(char* str, char** parsed) {
    for (int i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");
  
        if (parsed[i] == NULL)
            break;
        if (mx_strlen(parsed[i]) == 0)
            i--;
    }
    return exec_own_cmds(parsed) ? 0 : 1;
}
