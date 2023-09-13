


#include <stdio.h>
#include <windows.h>


int main() {
    HANDLE _file_handle = CreateFileA("C:\\users\\lc\\1.txt",
        GENERIC_ALL,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    HANDLE _file_map = CreateFileMappingA(_file_handle,
        NULL,
        PAGE_EXECUTE_READWRITE,
        0,
        0,
        NULL);

    LPVOID _view_address = MapViewOfFile(_file_map,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        0);

    printf("%s\n", (char*)_view_address);
    printf("--------------------\n\n");
    *(char*)_view_address = '0';

    printf("%s\n", (char*)_view_address);
}
