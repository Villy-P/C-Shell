#include <stdio.h>
#include <stdbool.h>

#include "exec.h"

#ifdef _WIN32
#include <windows.h>
#elif linux
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
        char c;
        int i = 0;
        bool esc = false;

        printf("%s >>>", cwd);
        while (true) {
            c = getchar();
            if (c == '\n')
                break;
            if (c == EOF) {
                printf("\nExiting...\n");
                exit(0);
            }
            if (i < LINE_BUFFER_SIZE - 1)
                input[i++] = c;
        }
        input[i] = '\0';
        execute(input);
    }
}