// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>

#include <huffman.h>

huffman_encode_t huffman_encode[256];

// A Huffman tree node
struct MinHeapNode {

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child of this node
    struct MinHeapNode *left, *right;
};

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

    // Current size of min heap
    unsigned size;

    // capacity of min heap
    unsigned capacity;

    // Array of minheap node pointers
    struct MinHeapNode** array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
        sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap
        = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode**)malloc(
        minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size
        && minHeap->array[left]->freq
               < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size
        && minHeap->array[right]->freq
               < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap,
                   struct MinHeapNode* minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i
           && minHeapNode->freq
                  < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[],
                                      int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[],
                                     int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size. Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap
        = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap)) {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3: Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not
        // used
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[],
                int top)

{

    // Assign 0 to left edge and recur
    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root)) {

        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void write_tree(struct MinHeapNode* root, int arr[],
                int top, FILE* file)

{
  if(top == 0)
  {
    fprintf(file, "\t\tcase 0:\n");
  }
  else
  {
    fprintf(file, "\t\tcase %u:\n", ((unsigned int)root))>>16;
  }
  
  int switch_set = 0;

  if (root->left)
  {
    switch_set = 1;
    fprintf(file, "\t\t\tif(input == 0)\n\t\t\t{\n\t\t\t\tputchar('0');\n\t\t\t\tstate = %u;\n\t\t\t\tbreak;\n\t\t\t\tsent_char = 0;\n\t\t\t}\n", ((unsigned int)root->left))>>16;
  }
  if (root->right)
  {
    switch_set = 1;
    fprintf(file, "\t\t\tif(input != 0)\n\t\t\t{\n\t\t\t\tputchar('1');\n\t\t\t\tstate = %u;\n\t\t\t\tbreak;\n\t\t\t\tsent_char = 0;\n\t\t\t}\n", ((unsigned int)root->right))>>16;
  }

  // Assign 0 to left edge and recur
  if (root->left) {
    //fprintf(file, "\tif(input == 0) state = %d;\n", (int)root->left);
    arr[top] = 0;
    write_tree(root->left, arr, top + 1, file);
  }

  // Assign 1 to right edge and recur
  if (root->right) {
    //fprintf(file, "\tif(input == 0) state = %d;\n", (int)root->right);
    arr[top] = 1;
    write_tree(root->right, arr, top + 1, file);
  }

  // If this is a leaf node, then
  // it contains one of the input
  // characters, print the character
  // and its code from arr[]
  if (isLeaf(root)) {
    fprintf(file, "\t\t\tstate = 0;\n");
    fprintf(file, "\t\t\t*ch = '%c';\n", root->data);
    fprintf(file, "\t\t\tsent_char = 1;\n");
    fprintf(file, "\t\t\tbreak;\n");
    printf("%c: ", root->data);
    printArr(arr, top);
  }
}

void write_decoder(struct MinHeapNode* root, int arr[], int top, FILE* f_template, FILE* f_target)
{
  char c;

  while((c = fgetc(f_template)) != EOF)
  {
    if(c == '?') break;
    fprintf(f_target, "%c", c);
  }
  

  write_tree(root, arr, top, f_target);
  while((c = fgetc(f_template)) != EOF)
  {
    fprintf(f_target, "%c", c);
  }
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void fill_huffman_encode(struct MinHeapNode* root, int arr[],
                int top, huffman_encode_t* huffman_encode)

{

    // Assign 0 to left edge and recur
    if (root->left) {

        arr[top] = 0;
        fill_huffman_encode(root->left, arr, top + 1, huffman_encode);
    }

    // Assign 1 to right edge and recur
    if (root->right) {

        arr[top] = 1;
        fill_huffman_encode(root->right, arr, top + 1, huffman_encode);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root)) {

        //printf("%c: ", root->data);
        //printArr(arr, top);
        
        for(int i = 0; i < top; i++)
        {
            huffman_encode[root->data].key[i] = arr[i];
            huffman_encode[root->data].size = top;
        }
    }
}


// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)

{   
    for(int i = 0; i < 256; i++)
    {
        for(int n = 0; n < MAX_TREE_HT; n++)
        {
            huffman_encode[i].key[n] = 0;
            huffman_encode[i].size = 0;
        }
    }
    // Construct Huffman Tree
    struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;

    FILE *f_write = fopen("test.txt", "w");
    if (f_write == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *f_target = fopen("../decoder/decoder.c", "w");
    if (f_target == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *f_template = fopen("../decoder/decoder_template.c", "r");
    if (f_template == NULL) {
        perror("Error opening file");
        return;
    }

    //printCodes(root, arr, top);

    //write_tree(root, arr, top, f_write);

    write_decoder(root, arr, top, f_template, f_target);

    fill_huffman_encode(root, arr, top, huffman_encode);

    for(int i = '#'; i <= '#'; i++)
    {   
        printf("%c: ", i);
        for(int n = 0; n < 2; n++)
        {
            printf("%d,",huffman_encode[i].key[n]);
        }
        printf("\n");
    }

    fclose(f_template);
    fclose(f_target);
    fclose(f_write);
}