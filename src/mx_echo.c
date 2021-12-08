#include "../inc/ush.h"

void mx_echo(char **args) {
    char * arr = cat_str_array(args, " ");
    system(arr);
    
}
