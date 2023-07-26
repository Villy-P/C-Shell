#include <stdio.h>
#include <stdbool.h>

#include "exec.h"

#ifdef _WIN32
#include <windows.h>
#else
#include "unistd.h"
#endif

#define LINE_BUFFER_SIZE 255

int main() {
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
        execute(input);
    }
}