#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

void GenerateRandomFilename(wchar_t* buffer, size_t bufferSize) {
    const wchar_t* alphabet = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const size_t alphabetLength = wcslen(alphabet);

    for (size_t i = 0; i < bufferSize - 1; ++i) {
        buffer[i] = alphabet[rand() % alphabetLength];
    }
    buffer[bufferSize - 1] = L'\0';
}

int main() {
    srand((unsigned int)time(NULL));
    typedef int (WINAPI* sleepFunction)(DWORD);
    sleepFunction CopySleep;

    const wchar_t* sourceFilePath = L"C:\\Windows\\SysWOW64\\kernel32.dll";
    const wchar_t* sourceFilePath2 = L"C:\\Windows\\SysWOW64\\ntdll.dll";

    wchar_t randomFilename[5];
    GenerateRandomFilename(randomFilename, 5);

    wchar_t destinationFilePath[MAX_PATH];
    PathCombineW(destinationFilePath, L"C:\\", randomFilename);

    wcscat(destinationFilePath, L".tmp");


    if (CopyFile(sourceFilePath, destinationFilePath, FALSE)) {
        printf("kernel32 copied successfully.\n");
    }

    HMODULE kernelbaseCopyModule = LoadLibraryEx(destinationFilePath, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);

    if (kernelbaseCopyModule != NULL) {
        CopySleep = (sleepFunction)GetProcAddress(kernelbaseCopyModule, "Sleep");

        if (CopySleep != NULL) {
            DWORD milliseconds = 2000; 
            CopySleep(milliseconds);
            printf("Sleep function called for %d milliseconds.\n", milliseconds);
        }
        else {
            printf("GetProcAddress failed to retrieve Sleep function pointer.\n");
        }
        FreeLibrary(kernelbaseCopyModule);
    }
    else {
        printf("Failed to load module.\n");
    }
    DeleteFile(destinationFilePath);
    system("PAUSE");
    return 0;
}