
#include "tinyrecv.h"

int main(int argc, char **argv)
{
    TinyRecv tr;
    if (tr.init()) {
        tr.recv();
    }

    return 0;
}
