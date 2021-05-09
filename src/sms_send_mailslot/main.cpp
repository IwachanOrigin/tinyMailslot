
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    char toSendTxt[100], buffer[100];
    DWORD bufferLen = 100;
    HANDLE hSMS_slot;
    BOOL status;
    DWORD numBytesWritten;

    // create mail slot.
    hSMS_slot = CreateFile("\\\\.\\mailslot\\sms", GENERIC_WRITE, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
    if (hSMS_slot == INVALID_HANDLE_VALUE) {
        std::cerr << "failed" << std::endl;
        return -1;
    }

    // create send message.
    GetComputerName(buffer, &bufferLen);
    strcpy(toSendTxt, "send string from this computer : ");
    strcat(toSendTxt, buffer);

    while (1) {
        std::cout << "sending..." << std::endl;
        status = WriteFile(hSMS_slot, toSendTxt, (DWORD)strlen(toSendTxt) + 1, &numBytesWritten, (LPOVERLAPPED)NULL);
        // error check
        if (!status) {
            std::cerr << "failed" << std::endl;
            CloseHandle(hSMS_slot);
            return -1;
        }

        Sleep(4800);
    }
    
    return 0;
}
