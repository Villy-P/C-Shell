// #include <stdio.h>
// #include <windows.h>

// #include "exec.h"

// void execErr() {
//     DWORD error = GetLastError();
//     LPSTR errorMessage = NULL;
//     FormatMessageA(
//         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//         NULL,
//         error,
//         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//         (LPSTR)&errorMessage,
//         0,
//         NULL
//     );
//     printf("%s\n", errorMessage);
// }

// void execute(char* command) {
//     STARTUPINFO si = { sizeof(si) };
//     PROCESS_INFORMATION pi;

//     char* runcmd = "cmd /c ";
//     size_t runcmdLen = strlen(runcmd);
//     size_t commandLen = strlen(command);
//     char* cmd = (char*)malloc(runcmdLen + commandLen + 1);

//     strcpy(cmd, runcmd);
//     strcat(cmd, command);

//     ZeroMemory( &si, sizeof(si) );
//     si.cb = sizeof(si);
//     ZeroMemory( &pi, sizeof(pi) );

//     if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
//         execErr();
//         return;
//     }

//     WaitForSingleObject(pi.hProcess, INFINITE);

//     CloseHandle(pi.hProcess);
//     CloseHandle(pi.hThread);
// }