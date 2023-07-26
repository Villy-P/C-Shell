#ifndef __EXEC_H__
#define __EXEC_H__

#include <unistd.h>

#define MAXIM_JOBS 255

typedef struct {
    pid_t pid;
    char* name;
} Job;

extern int currentJob;
extern Job** jobs;

void addJob(pid_t pid, char* name);
void execute(char* command);

#endif