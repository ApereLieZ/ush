#include "../inc/ush.h"

char *prev_path = NULL;
char *cur_path = NULL;
bool was_in_link;

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

static void check_flags(char **args, bool *fl_P, bool *fl_s) {
    for(int i = 0; args[i] != NULL; i++) {
        if(mx_strcmp(args[i], "-") != 0 && args[i][0] == '-') {
            for(int j = 0; j < mx_strlen(args[i]); j++) {
                if(args[i][j] == 'P') *fl_P = true;
                else if(args[i][j] == 's') *fl_s = true;
            }
        }
    }
}

void mx_cd(char **args) {
    // char cur_dir[1024];
    // getcwd(cur_dir, 1024);
    // setenv("PWD", cur_dir, 1);

    struct stat buf;
    bool fl_P = false, fl_s = false;
    int argc = count_args(args);
    check_flags(args, &fl_P, &fl_s);
    char *path = args[argc - 1]; 
    
    lstat(path, &buf);
    errno = 0;
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
    
    if(mx_strcmp(path, "-") == 0 || (was_in_link && mx_strcmp(path, "..") == 0)) { //cd - 
        if(!was_in_link) {
            char *temp = mx_replace_substr(prev_path, getenv("HOME"), "~");
            mx_printstr(temp);
            mx_printchar('\n');
            mx_strdel(&temp);
        }
        chdir(prev_path);
        swap_strings(&prev_path, &cur_path);
        was_in_link = false;
        return;
    }
    
    char *fixed_path = mx_replace_substr(path, "~", getenv("HOME")); // ~ fix
    chdir(fixed_path); //default
    
    if(S_ISLNK(buf.st_mode) && !fl_P) {
        was_in_link = true;
    }
    
    if(errno == ENOENT) {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(fixed_path);
        mx_printerr("\n");
    }
    
    get_new_pathes(&prev_path, &cur_path);
    mx_strdel(&fixed_path);
}
