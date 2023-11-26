#ifndef __EXEC_H__
#define __EXEC_H__

#ifndef _WIN32
#include <unistd.h>
#include <sys/wait.h>
#endif

#define MAXIM_JOBS 255

typedef struct {
    int id;
    pid_t pid;
    char* name;
    int status;
} Job;

void handleSigTerminalStop(int signum);
Job* getByPid(pid_t pid);
void removeByPid(pid_t pid);
void handleSigChild(int signum);
char* getJobStatus(int status);
int getNextJobID();
Job* addJob(pid_t pid, char* name, int status);
void execute(char* command);

#endif