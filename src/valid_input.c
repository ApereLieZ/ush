#include "../inc/ush.h"

void validate_input(char* str, char** parsed) {
    for (int i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");
        if (parsed[i] == NULL)
            break;
        if (mx_strlen(parsed[i]) == 0)
            i--;
    }
}
