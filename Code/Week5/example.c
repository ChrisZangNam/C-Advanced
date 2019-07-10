#include "btree.h"

int main(int argc, char *argv[])
{
    BTA *btfile;
    btinit();
    btfile = btcrt("test.txt", 0, FALSE);
    binsky(btfile, "akey", 99);
    btcls(btfile);

    return 0;
}
