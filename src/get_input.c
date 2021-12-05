#include "../inc/ush.h"

int get_input(char* str) {
    char* buf;
    buf = readline("\nu$h> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}
