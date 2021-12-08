#include "../inc/ush.h"

static void parce_flag_pwd(char** args, bool* fl_P ) {
    
    for(int i = 0; args[i] != NULL; i++) {
        
        if(args[i][0] == '-') {
            
            for(int j = 0; j < mx_strlen(args[i]); j++) {
                
                if(args[i][j] == 'P') *fl_P = true;
            }
            
        }
        
    }
}

void mx_pwd(char** argc) {
    
    bool fl_P = false;
    parce_flag_pwd(argc, &fl_P);
    char str[1024];
    getcwd(str, 1024);
    if(fl_P) {
        mx_printstr(str);
    }else {
        if(was_in_link){ 
            mx_printstr(getenv("LINKPATH"));
        }
        else mx_printstr(str);
    }
    mx_printchar('\n');
}
    
    
