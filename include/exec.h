#ifndef __EXEC_H__
#define __EXEC_H__

#include <unistd.h>

#define MAXIM_JOBS 255

typedef struct {
    int id;
    pid_t pid;
    char* name;
    int status;
} Job;

int getNextJobID();
void addJob(pid_t pid, char* name, int status);
void execute(char* command);

#endif