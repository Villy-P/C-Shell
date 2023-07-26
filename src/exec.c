#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "exec.h"

#ifdef _WIN32
#include <windows.h>
#else
#include "unistd.h"
#include <sys/wait.h>
#endif

int currentJob = 1;
Job** jobs = (Job**)NULL;

void addJob(pid_t pid, char* name) {
    printf("Job added");
    if (currentJob > MAXIM_JOBS)
        return;
    Job* j = (Job*)malloc(sizeof(Job));
    j->pid = pid;
    j->name = name;
    jobs = (Job**)realloc(jobs, sizeof(Job*) * (currentJob + 1));
    jobs[currentJob - 1] = j;
    jobs[currentJob] = NULL;
    currentJob++;
}

void execute(char* command) {
    #ifdef _WIN32
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

        if (strncmp(command, "cd ", 3) == 0) {
            command += 3;
            if (!SetCurrentDirectoryA(command)) {
                printf("The system cannot find the path specified.\n");
                return;
            }
        } else {
            char* runcmd = "cmd /c ";
            size_t runcmdLen = strlen(runcmd);
            size_t commandLen = strlen(command);
            char* cmd = (char*)malloc(runcmdLen + commandLen + 1);

            strcpy(cmd, runcmd);
            strcat(cmd, command);
            if (!CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
                printf("Failed to execute command. (Are you running as an administrator?)\n");
                return;
            }
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    #else
        bool bg = false;
        __pid_t pid = fork();
        if (pid < 0) {
            printf("fork() caused an error.");
            exit(1);
        } else if (pid == 0) {
            size_t cmdlen = strlen(command);
            if (command[cmdlen - 1] == '&' && command[cmdlen - 2] == ' ') {
                bg = true;
                command[cmdlen - 2] = '\0';
            }
            if (strncmp(command, "cd ", 3) == 0) {
                command += 3;
                chdir(command);
            } else if (strcmp(command, "jobs") == 0) {
                int current = 0;
                while (jobs[current] != NULL) {
                    printf(
                        "[%d]%c Running\t\t%s", 
                        current + 1, 
                        jobs[current + 1] == NULL 
                            ? '+' 
                            : '-', 
                        jobs[current]->name);
                    current++;
                }
            } else {
                char* token = strtok(command, " ");
                char* cmd;
                strcpy(cmd, token);
                token = strtok(NULL, " ");
                execlp(cmd, cmd, token, (char *)NULL);
                perror("");
            }
        } else {
            printf("%d\n", bg);
            int childStatus;
            if (!bg)
                wait(&childStatus);
            else
                printf("WOW");
        }
    #endif
}