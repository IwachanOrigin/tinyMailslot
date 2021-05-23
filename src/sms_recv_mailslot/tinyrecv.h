/**
 * @copyright Copyright (c) Yuji Iwanaga
 * @date 23th May. 2021
 */

#ifndef TINYRECV_H
#define TINYRECV_H

#include <Windows.h>

class TinyRecv
{
public:
    explicit TinyRecv();
    ~TinyRecv() {}

    bool init();
    bool recv();

private:
    HANDLE m_mailslot;
    DWORD m_nextSize;
    DWORD m_msgs;
    DWORD m_numByteRead;
    BOOL m_status;
};

#endif // TINYRECV_H
