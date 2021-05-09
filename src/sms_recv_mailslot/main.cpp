
#include <Windows.h>
#include <iostream>

int main(int argc, char **argv) {

    char toDisptxt[100];
    HANDLE hSMS_slot;
    DWORD nextsize;
    DWORD msgs;
    DWORD numBytesRead;
    BOOL status;

    // create mail slots;
    hSMS_slot = CreateMailslot("\\\\.\\mailslot\\sms", 0, 0, (LPSECURITY_ATTRIBUTES)NULL);
    if (hSMS_slot == INVALID_HANDLE_VALUE) {
        std::cerr << "failed." << std::endl;
        return -1;
    }

    while (1) {
        status = GetMailslotInfo(hSMS_slot, (LPDWORD)NULL, &nextsize, &msgs, (LPDWORD)NULL);
        if (!status) {
            std::cerr << "failed" << std::endl;
            CloseHandle(hSMS_slot);
            return -1;
        }

        if (msgs) {
            if (!ReadFile(hSMS_slot, toDisptxt, nextsize, &numBytesRead, (LPOVERLAPPED)NULL)) {
                std::cerr << "failed." << std::endl;
                CloseHandle(hSMS_slot);
                return (-1);
            }
            // output txt.
            std::cout << toDisptxt << std::endl;
        } else {
            // check twice in 1 second.
            Sleep(500);
        }
    }

    return 0;
}
