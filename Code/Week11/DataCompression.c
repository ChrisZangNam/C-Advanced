#include <stdio.h>
#include <stdlib.h>
#include "DataCompression.h"

int main()
{
    char buffer[] = "AAAAAABBCCC";
    Coding huffmanTable[256];
    // Create a Huffman tree
    HuffmanTree huf = makeHuffman(buffer, strlen(buffer));
    // Create a code table for each characters
    createHuffmanTable(huf, huffmanTable);
}
