#include "../inc/ush.h"

void mx_exit(char **parsed) {
    if(parsed[1] == NULL) 
        exit(0);
    else
        exit(mx_atoi(parsed[1]));
}
