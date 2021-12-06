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
    getcwd(str, sizeof(str));
    if(fl_P) {
        mx_printstr(str);
        mx_printchar('\n');
    }else {
        system("pwd -L");
    }
    
    
    
}
