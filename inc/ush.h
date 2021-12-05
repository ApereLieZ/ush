#ifndef SH
#define SH

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported
#define clear() mx_printstr("\033[H\033[J")

#include "../libmx/inc/libmx.h"
#include <dirent.h>
#include <sys/types.h>
#include <limits.h> 
#include <sys/acl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <editline/readline.h>


int get_input(char* str);
void validate_input(char* str, char** parsed);
void exec_sys_cmds(char** parsed);
int exec_own_cmds(char** parsed);
void mx_pwd();
char **fix_command_list(char ***input_str);
int get_amount_cmds(char **input_str);

void mx_unset (char **parsed);
void mx_export (char** parsed);
#endif

