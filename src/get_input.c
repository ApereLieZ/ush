#include "../inc/ush.h"

int get_input(char* str) {
    char* buf;
    buf = readline("u$h> ");
    if(!buf) exit(0);
    if (strlen(buf) != 0) {
        add_history(buf);
        mx_strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}
