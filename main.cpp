#include "windows.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char* argv[]) {
    //filedate.exe <fileName> [time]
    SYSTEMTIME spec_time;

    if (argc == 2) {
        sscanf_s("2012-11-08", "%d-%d-%d", &spec_time.wYear, &spec_time.wMonth, &spec_time.wDay);
        sscanf_s("09:00:00", "%d:%d:%d", &spec_time.wHour, &spec_time.wMinute, &spec_time.wSecond);
    }
    else {
        sscanf_s(argv[2], "%d-%d-%d", &spec_time.wYear, &spec_time.wMonth, &spec_time.wDay);
        sscanf_s(argv[3], "%d:%d:%d", &spec_time.wHour, &spec_time.wMinute, &spec_time.wSecond);
    }

    spec_time.wDayOfWeek = 1;
    spec_time.wMilliseconds = 0;

    HANDLE hFile = CreateFile(argv[1],
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Get file handle failed, error = %s\n", GetLastError());
        return -1;
    }

    FILETIME ft, LocalFileTime;
    SystemTimeToFileTime(&spec_time, &ft);
    LocalFileTimeToFileTime(&ft, &LocalFileTime);

    if (SetFileTime(hFile, &LocalFileTime, (LPFILETIME)NULL, &LocalFileTime)) {
        printf("Set file time success\n");
    }
    else {
        printf("Set file time failed\n");
    }
    CloseHandle(hFile);
    return 0;
}