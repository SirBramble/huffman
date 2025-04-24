#ifndef _huffman_h_
#define _huffman_h_

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100

//extern int huffman_encode[256][MAX_TREE_HT];

typedef struct
{
  int key[MAX_TREE_HT];
  int size;
} huffman_encode_t;

extern huffman_encode_t huffman_encode[256];

void HuffmanCodes(char data[], int freq[], int size);

#endif // _huffman_h_