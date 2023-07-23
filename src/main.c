#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "exec.h"

#define LINE_BUFFER_SIZE 255

int main() {
    while (true) {
        char input[LINE_BUFFER_SIZE];
        TCHAR buffer[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, buffer);
        printf("%s >", buffer);
        fgets(input, LINE_BUFFER_SIZE, stdin);

        execute(input);
    }
}