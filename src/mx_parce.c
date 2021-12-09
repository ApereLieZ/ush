#include"../inc/ush.h"


char * mx_parce_dollar(char* param, char** result) {
    char* str = mx_strchr(param, '$');
    if(str == NULL || ++str == NULL) return NULL;
    bool is_open_br = false;
    if(*str == '{' && ++str != NULL) is_open_br = true;   

    if(is_open_br) {
        while (str++)
        {
            if(*str == '{') return NULL; ///error bad substitution
            if(*str == '}') {
                return str;
            }
            mx_strjoin(*result, mx_strndup(str, 1));
        }
        return NULL;
    } else {
        *result = mx_strdup(str);
        return NULL;
    }
}

// Делайте парсер 😅
// Что бы все эти херобины \ / ‘ ~ $ корректно работали 

// Я ж приду буду сигналы дальше пытаться делать

