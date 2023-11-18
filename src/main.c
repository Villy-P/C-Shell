#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "exec.h"

#ifdef _WIN32
#include <windows.h>
#else
#include "unistd.h"
#include <signal.h>
#endif

#define LINE_BUFFER_SIZE 255

extern int jobsLen;
extern Job** jobs;

void handleSigTerminalStop(int signum) {
    // printf("I WAS HERE");
    Job* lastJob = jobs[jobsLen - 1];
    if (lastJob->status != 0)
        return;
    lastJob->status = 3;
    // printf("[%d]+ Stopped\t\t%s\n", lastJob->id, lastJob->name);
    kill(lastJob->pid, SIGTSTP);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handleSigTerminalStop;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    jobsLen = 0;
    jobs = calloc(sizeof(Job*), 1);
    while (true) {
        char cwd[4096];
        #ifdef _WIN32
            GetCurrentDirectory(sizeof(cwd), cwd);
        #else
            getcwd(cwd, sizeof(cwd));
        #endif
        char input[LINE_BUFFER_SIZE];
        printf("%s >>>", cwd);
        fgets(input, LINE_BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = 0;
        char* cmd = malloc(strlen(input) + 1);
        strcpy(cmd, input);
        execute(cmd);
    }
}