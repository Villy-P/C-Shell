#include <stdio.h>
#include <stdbool.h>

#include "exec.h"
#include "unistd.h"

#define LINE_BUFFER_SIZE 255

int main() {
    while (true) {
        char cwd[4096];
        getcwd(cwd, sizeof(cwd));
        char input[LINE_BUFFER_SIZE];
        printf("%s >>>", cwd);
        fgets(input, LINE_BUFFER_SIZE, stdin);
    //     execute(input);
    }
}