#include <Windows.h>
#include <iostream>

using namespace std;

void printDriveInformation(wchar_t);
void ejectDevice(wchar_t);

void ejectDevice(wchar_t driveLetter){
	CHAR vpr;
	wprintf(L"Извлечь устройство? (Y/N)\n");
        scanf("%c", &vpr);
        getchar();
        if (vpr == 'Y' || vpr == 'y') {
            wstring devicePath = wstring(L"\\\\.\\") + wstring(1, driveLetter) + L":";
		    HANDLE hDevice = CreateFileW(devicePath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		    DWORD bytesReturned;
		    if (!DeviceIoControl(hDevice, IOCTL_STORAGE_EJECT_MEDIA, NULL, 0, NULL, 0, &bytesReturned, NULL)) {
		        wprintf(L"Не удалось извлечь накопитель.\n");
		        return;
		    }
		    wprintf(L"Устройство извлеченно\n");
		    return;
        }
}

void printDriveInformation(wchar_t driveLetter) {
    wchar_t volumePath[8];
    volumePath[0] = driveLetter;
    volumePath[1] = L':';
    volumePath[2] = L'\\';

    DWORD attributes = GetFileAttributesW(volumePath);
    if (attributes == INVALID_FILE_ATTRIBUTES || !(attributes & FILE_ATTRIBUTE_DIRECTORY)) {
        wprintf(L"Не удалось получить информацию о томе %c:\n", driveLetter);
    }
    
    if (GetDriveTypeW(volumePath) == DRIVE_CDROM) {
        wprintf(L"DVD привод подключен.\n");
        ejectDevice(driveLetter);
	}
		
    wchar_t fileSystemName[MAX_PATH + 1];
    DWORD fileSystemFlags = 0;
    if (GetVolumeInformationW(volumePath, nullptr, 0, nullptr, nullptr, &fileSystemFlags, fileSystemName, sizeof(fileSystemName))) {
        wprintf(L"Буква диска: %c:\n", driveLetter);
        wprintf(L"Файловая система: %s\n", fileSystemName);
        wprintf(L"Съемный: %s\n", (GetDriveTypeW(volumePath) == DRIVE_REMOVABLE) ? L"Yes" : L"No");
        ULARGE_INTEGER totalSpace, freeSpace;
        if (GetDiskFreeSpaceExW(volumePath, &freeSpace, &totalSpace, NULL)) {
			wprintf(L"Общий объем %i GB\n", totalSpace.QuadPart / (1024 * 1024 * 1024));
			wprintf(L"Свободное место %i GB\n", freeSpace.QuadPart / (1024 * 1024 * 1024));
        }
        if (GetDriveTypeW(volumePath) == DRIVE_REMOVABLE) {
          ejectDevice(driveLetter);
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "");
    DWORD drives = GetLogicalDrives();
    wchar_t driveLetter = L'A';
    while (drives != 0) {
        if (drives & 1) {
            printDriveInformation(driveLetter);
        }
        drives >>= 1;
        ++driveLetter;
    }
    return 0;
}
