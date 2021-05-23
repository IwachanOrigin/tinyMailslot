/**
 * @copyright Copyright (c) Yuji Iwanaga
 * @date 23th May. 2021
 */

#include "tinysend.h"

TinySend::TinySend()
    : m_mailslot(0)
    , m_bufflen(100)
    , m_numbyteswritten(0)
    , m_status(FALSE)
{}

bool TinySend::init()
{
    m_mailslot = CreateFile(L"\\\\.\\mailslot\\sms", GENERIC_WRITE, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
    if (m_mailslot == INVALID_HANDLE_VALUE) {
        std::cerr << "failed create mail slot." << std::endl;
        return false;
    }

    return true;
}

bool TinySend::send()
{
    char tosendtxt[100], buff[100];
    errno_t err;

    // create send message.
    GetComputerNameA(buff, &m_bufflen);

    err = strcpy_s(tosendtxt, "send string from this computer : ");
    if (err != 0) {
        std::cerr << "failed strcpy_s." << std::endl;
        return false;
    }

    err = strcat_s(tosendtxt, buff);
    if (err != 0) {
        std::cerr << "failed strcat_s." << std::endl;
        return false;
    }

    while (1) {
        std::cout << "sending..." << std::endl;
        m_status = WriteFile(m_mailslot, tosendtxt, (DWORD)strlen(tosendtxt) + 1, &m_numbyteswritten, (LPOVERLAPPED)NULL);
        if (!m_status) {
            std::cerr << "failed sending message." << std::endl;
            CloseHandle(m_mailslot);
            return false;
        }

        Sleep(1000);
    }

    return true;
}
