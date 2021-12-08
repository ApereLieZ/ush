#include "../inc/ush.h"

void mx_fg(pid_t pid) {
    kill(pid, SIGCONT);
}
