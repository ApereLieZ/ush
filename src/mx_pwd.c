#include "../inc/ush.h"

void mx_pwd() {
    char cur_dir[1024];
    getcwd(cur_dir, 1024);
    mx_printstr(cur_dir);
    mx_printchar('\n');
}
