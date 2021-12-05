#include "../inc/ush.h"

void mx_unset (char **parsed) {
    if (!parsed[1]) {
       mx_printerr("unset: not enough arguments");
       return;
    }
    parsed++;
    while(*parsed) {
        unsetenv(*parsed);
        parsed++;
    }
}
