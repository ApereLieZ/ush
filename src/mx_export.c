#include "../inc/ush.h"

bool comp (char *s1, char *s2) {
    while (*s1 != '\0' && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *s1 < *s2;
}

void mx_export (char** parsed) {
    parsed++;
    if (*parsed) {
        while (*parsed) {
            putenv(*parsed);
            parsed++;
        }
    }
    else {
        extern char** environ;
        int e_size = 0;
        for (int i = 0; environ[i] != NULL; i++) {
            e_size++;
        }
        char **e = malloc(e_size * sizeof(char*));
        for (int i = 0; environ[i] != NULL; i++) {
            e[i] = mx_strdup(environ[i]);
        }
        e[e_size] = NULL;
        mx_bubble_sort(e, e_size, comp);
        for (int i = 0; e[i] != NULL; i++) {
            mx_printstr(e[i]);
            mx_printchar('\n');
        }
        mx_del_strarr(&e);
    }
}

