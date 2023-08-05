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

void handleSigChild(int signum);
char* getJobStatus(int status);
int getNextJobID();
Job* addJob(pid_t pid, char* name, int status);
void execute(char* command);

#endif