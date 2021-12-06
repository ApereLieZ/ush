#include "../inc/ush.h"

char *prev_path = NULL;
char *cur_path = NULL;

static void swap_strings(char **str1, char **str2) {
    char *temp = mx_strdup(*str1);
    mx_strdel(str1);
    *str1 = mx_strdup(*str2);
    mx_strdel(str2);
    *str2 = mx_strdup(temp);
    mx_strdel(&temp);
}

static void get_new_pathes(char **prev_path, char **cur_path) {
        mx_strdel(prev_path);
        *prev_path = mx_strdup(*cur_path);
        mx_strdel(cur_path);
        *cur_path = malloc(sizeof(char) * 1024);
        getcwd(*cur_path, 1024);
}

static int count_args(char **args) {
    int i;
    for(i = 0; args[i] != NULL; i++);
    return i;
}

void mx_cd(char **args) {
    //struct stat buf;
    bool fl_P = false, fl_s = false;
    errno = 0;

    int res, argc = count_args(args);
    while((res = getopt(argc, args, "Ps")) != -1) {
        switch(res) {
            case 'P':
                fl_P = true;
                printf("fl_P found\n");
                break;
            case 's':
                fl_s = true;
                printf("fl_s found\n");
                break;
            default:
                break;
        }
    }

    char *path = args[argc - 1]; 

    if(!prev_path) { //init pathes
        prev_path = malloc(sizeof(char) * 1024);
        getcwd(prev_path, 1024);
        cur_path = mx_strdup(prev_path);
    }

    if(mx_strcmp(path, "cd") == 0) { //cd without path
        chdir(getenv("HOME"));
        get_new_pathes(&prev_path, &cur_path);
        return;
    }
    
    if(mx_strcmp(path, "-") == 0) { //cd - 
        char *temp = mx_replace_substr(prev_path, getenv("HOME"), "~");
        mx_printstr(temp);
        mx_printchar('\n');
        chdir(prev_path);
        swap_strings(&prev_path, &cur_path);
        mx_strdel(&temp);
        return;
    }

    

    char *fixed_path = mx_replace_substr(path, "~", getenv("HOME")); // ~ fix

    chdir(fixed_path); //default
    get_new_pathes(&prev_path, &cur_path);

    if(errno == ENOENT) {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(fixed_path);
        mx_printerr("\n");
    }
    mx_strdel(&fixed_path);
}
