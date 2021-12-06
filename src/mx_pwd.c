#include "../inc/ush.h"

void mx_pwd() {
    char cur_dir[1024];
    getcwd(cur_dir, 1024);
    if(!was_in_link)
        mx_printstr(cur_dir);
    else    
        mx_printstr(getenv("PWD"));
    mx_printchar('\n');
}
