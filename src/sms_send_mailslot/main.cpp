/**
 * @copyright Copyright (c) Yuji Iwanaga
 * @date 23th May. 2021
 */

#include "tinysend.h"

int main(int argc, char **argv)
{
    TinySend ts;
    if (ts.init()) {
        ts.send();
    }

    return 0;
}
