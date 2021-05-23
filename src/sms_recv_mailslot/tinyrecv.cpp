/**
 * @copyright Copyright (c) Yuji Iwanaga
 * @date 23th May. 2021
 */

#include "tinyrecv.h"
#include <iostream>

TinyRecv::TinyRecv()
    : m_mailslot(0)
    , m_nextSize(0)
    , m_msgs(0)
    , m_numByteRead(0)
    , m_status(FALSE)
{}

bool TinyRecv::init()
{
    m_mailslot = CreateMailslot(L"\\\\.\\mailslot\\sms", 0, 0, (LPSECURITY_ATTRIBUTES)NULL);
    if (m_mailslot == INVALID_HANDLE_VALUE) {
        std::cerr << "failed create mail slot." << std::endl;
        return false;
    }
    return true;
}

bool TinyRecv::recv()
{
    char buff[100];

    while (1) {
        m_status = GetMailslotInfo(m_mailslot, (LPDWORD)NULL, &m_nextSize, &m_msgs, (LPDWORD)NULL);
        if (!m_status) {
            std::cerr << "failed get mail slot info." << std::endl;
            CloseHandle(m_mailslot);
            return false;
        }

        if (m_msgs) {
            if (!ReadFile(m_mailslot, buff, m_nextSize, &m_numByteRead, (LPOVERLAPPED)NULL)) {
                std::cerr << "failed read file." << std::endl;
                CloseHandle(m_mailslot);
                return false;
            }
            std::cout << buff << std::endl;
        } else {
            Sleep(500);
        }
    }

    return true;
}
