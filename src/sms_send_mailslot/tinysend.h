/**
 * @copyright Copyright (c) Yuji Iwanaga
 * @date 23th May. 2021
 */

#ifndef TINYSEND_H
#define TINYSEND_H

#include <Windows.h>

class TinySend
{
public:
    explicit TinySend();
    ~TinySend() {}

    bool init();
    bool send();

private:
    HANDLE m_mailslot;
    DWORD m_bufflen;
    DWORD m_numbyteswritten;
    BOOL m_status;
};


#endif // TINYSEND_H
