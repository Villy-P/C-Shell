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

enum JOB_STATUS {
    FG,
    BG,
    STOPPED,
    KILLED
};

int jobsLen;
Job** jobs;

int getNextJobID() {
    if (jobsLen == 0)
        return 1;
    return jobs[jobsLen - 1]->id + 1;
}

void addJob(pid_t pid, char* name, int status) {
    printf("Job: %s\n", name);
    int id = getNextJobID();
    if (status == BG)
        printf("[%d] %d\n", id, pid);
    Job* j = (Job*)malloc(sizeof(Job));
    j->pid = pid;
    j->name = name;
    j->id = id;
    j->status = status;
    jobs = (Job**)realloc(jobs, sizeof(Job*) * (jobsLen + 2));
    jobs[jobsLen] = j;
    jobs[jobsLen + 1] = NULL;
    jobsLen++;
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
        bool bg;
        size_t cmdlen = strlen(command);
        if (command[cmdlen - 1] == '&') {
            bg = true;
            command[cmdlen - 1] = '\0';
        } else {
            bg = false;
        }
        __pid_t pid = fork();
        if (pid < 0) {
            printf("fork() caused an error.");
            exit(1);
        } else if (pid == 0) {
            printf("\n");
            if (strncmp(command, "cd ", 3) == 0) {
                command += 3;
                chdir(command);
            } else if (strcmp(command, "jobs") == 0) {
                int current = 0;
                printf("0-index: %s\n", jobs[0]->name);
                while (jobs[current] != NULL) {
                    printf(
                        "[%d]%c Running\t\t%s\n", 
                        jobs[current]->id, 
                        jobs[current + 1] == NULL 
                            ? '+' 
                            : '-', 
                        jobs[current]->name);
                    current++;
                }
            } else {
                char* token = strtok(command, " ");
                char* cmd = malloc(cmdlen + 1);
                strcpy(cmd, token);
                token = strtok(NULL, " ");
                execlp(cmd, cmd, token, (char *)NULL);
                free(cmd);
                perror("");
            }
        } else {
            int childStatus;
            printf("Command: %s\n", command);
            addJob(pid, command, bg ? BG : FG);
            if (!bg)
                wait(&childStatus);
        }
    #endif
}