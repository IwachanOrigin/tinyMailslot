/**
 * @copyright Copyright (c) Yuji Iwanaga
 * @date 23th May. 2021
 */

#include "tinyrecv.h"

int main(int argc, char **argv)
{
    TinyRecv tr;
    if (tr.init()) {
        tr.recv();
    }

    return 0;
}
