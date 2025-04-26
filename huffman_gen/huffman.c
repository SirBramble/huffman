// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>

#include <huffman.h>

huffman_encode_t huffman_encode[256];

/**
 * @brief A Huffman tree node
 * 
 */
struct MinHeapNode {

    /** One of the input characters */
    char data;

    /** Frequency of the character */
    unsigned freq;

    /** Left and right child of this node */
    struct MinHeapNode *left, *right;
};

/**
 * @brief A Min Heap: Collection of min-heap (or Huffman tree) nodes
 * 
 */
struct MinHeap {

    /** Current size of min heap */
    unsigned size;

    /** capacity of min heap */
    unsigned capacity;

    /** Array of minheap node pointers */
    struct MinHeapNode** array;
};

/**
 * @brief A utility function allocate a new min heap node with given character and frequency of the character
 * 
 * @param data The character assigned to the node
 * @param freq The frequency of the character
 * @return struct MinHeapNode* 
 */
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
        sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

/**
 * @brief A utility function to createa min heap of given capacity
 * 
 * @param capacity Capacity of the Heap
 * @return Pointer to the heap (struct MinHeap*) 
 */
struct MinHeap* createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

/**
 * @brief A utility function to swap two min heap nodes
 * 
 * @param a Node a
 * @param b Node b
 */
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

/**
 * @brief The standard minHeapify function
 * 
 * @param minHeap Heap pointer
 * @param idx 
 */
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

/**
 * @brief A utility function to check if size of heap is 1 or not
 * 
 * @param minHeap Heap pointer
 * @return int 
 */
int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

/**
 * @brief A standard function to extract minimum value node from heap
 * 
 * @param minHeap Heap pointer
 * @return Pointer to node with smallest value (struct MinHeapNode*) 
 */
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

/**
 * @brief A utility function to insert a new node to Min Heap
 * 
 * @param minHeap Heap Pointer
 * @param minHeapNode Pointer to node to be inserted
 */
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

/**
 * @brief A standard function to build min heap
 * 
 * @param minHeap Heap pointer
 */
void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

/**
 * @brief A utility function to print an array of size n
 * 
 * @param arr Array to print
 * @param n Number of elements to print
 */
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

/**
 * @brief Utility function to check if this node is leaf
 * 
 * @param root Pointer to Node to be checked
 * @return is leaf? (int) 
 */
int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

/**
 * @brief Creates a min heap of capacity equal to size and inserts all character of data[] in min heap. Initially size of min heap is equal to capacity
 * 
 * @param data Array of found characters
 * @param freq Frequency of found character
 * @param size Size of the Heap
 * @return struct MinHeap* 
 */
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

/**
 * @brief The main function that builds Huffman tree
 * 
 * @param data Array of found characters
 * @param freq Frequency of found character
 * @param size Size of the Heap 
 * @return Root node (struct MinHeapNode*) 
 */
struct MinHeapNode* buildHuffmanTree(char data[],
                                     int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {

        left = extractMin(minHeap);
        right = extractMin(minHeap);
        
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

/**
 * @brief Prints huffman codes from the root of Huffman Tree. It uses arr[] to store codes
 * 
 * @param root Pointer to Root node
 * @param arr Array to save code
 * @param top Current tree level
 */
void printCodes(struct MinHeapNode* root, int arr[],
                int top)

{

    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {

        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

/**
 * @brief Helper function to print cirtain characters to file
 * 
 * @param f_target Target file to be written to
 * @param c Character to be written
 */
void fprintc_cstyle(FILE* f_target, char c)
{
    if(c == '\n') fprintf(f_target, "\\n");
    else fprintf(f_target, "%c", c);
}

/**
 * @brief Writes huffman decoder state maschine to a file. It uses arr[] to store codes
 * 
 * @param root Pointer to the Root of the tree
 * @param arr Array to store codes
 * @param top Current level in Tree
 * @param f_target_c Target source file
 * @param f_target_h Target header file
 */
void write_tree(struct MinHeapNode* root, int arr[],
                int top, FILE* f_target_c, FILE* f_target_h)

{
    if(top == 0)
    {
        fprintf(f_target_c, "\t\tcase E0:\n");
    }
    else if(!isLeaf(root))
    {
        fprintf(f_target_c, "\t\tcase E%u:\n", (unsigned long)root);
        fprintf(f_target_h, "\tE%u,\n", (unsigned long)root);
    }

  int switch_set = 0;

  if (root->left)
  {
    switch_set = 1;
    fprintf(f_target_c, "\t\t\tif(input == 0)");
    fprintf(f_target_c, "\n\t\t\t{");
    if(isLeaf(root->left))
    {
        fprintf(f_target_c, "\n\t\t\tstate = E0;");
        fprintf(f_target_c, "\n\t\t\t\t*ch = '");
        fprintc_cstyle(f_target_c, root->left->data);
        fprintf(f_target_c, "';\n");
        fprintf(f_target_c, "\n\t\t\tsent_char = 1;");
    }
    else
    {
        
        //fprintf(f_target_c, "\n\t\t\t\tputchar('0');");
        fprintf(f_target_c, "\n\t\t\t\tstate = E%u;", (unsigned long)root->left);
        fprintf(f_target_c, "\n\t\t\t\tsent_char = 0;");
    }
    fprintf(f_target_c, "\n\t\t\t\tbreak;");
    fprintf(f_target_c, "\n\t\t\t}\n");
  }
  if (root->right)
  {
    switch_set = 1;
    fprintf(f_target_c, "\t\t\tif(input != 0)");
    fprintf(f_target_c, "\n\t\t\t{");
    if(isLeaf(root->right))
    {
        fprintf(f_target_c, "\n\t\t\t\tstate = E0;");
        fprintf(f_target_c, "\n\t\t\t\t*ch = '");
        fprintc_cstyle(f_target_c, root->right->data);
        fprintf(f_target_c, "';\n");
        fprintf(f_target_c, "\t\t\t\tsent_char = 1;\n");
    }
    else
    {
        //fprintf(f_target_c, "\n\t\t\t\tputchar('1');");
        fprintf(f_target_c, "\n\t\t\t\tstate = E%u;", (unsigned long)root->right);
        fprintf(f_target_c, "\n\t\t\t\tsent_char = 0;");
    }
    fprintf(f_target_c, "\n\t\t\t\tbreak;");
    fprintf(f_target_c, "\n\t\t\t}\n");
    
  }

  if (root->left) {
    arr[top] = 0;
    write_tree(root->left, arr, top + 1, f_target_c, f_target_h);
  }

  if (root->right) {
    arr[top] = 1;
    write_tree(root->right, arr, top + 1, f_target_c, f_target_h);
  }
  
  if (isLeaf(root)) {
    printf("%c: ", root->data);
    printArr(arr, top);
  }
  
}

/**
 * @brief Writes the decoder based on the template to a provided file.
 * 
 * @param root Pointer to the root of the tree
 * @param arr Array to store codes
 * @param top Curent level in the tree
 * @param f_template_c File pointer to the template source
 * @param f_target_c File pointer to the template header
 * @param f_template_h File pointer to the target source
 * @param f_target_h File pointer to the target header
 */
void write_decoder(struct MinHeapNode* root, int arr[], int top, FILE* f_template_c, FILE* f_target_c, FILE* f_template_h, FILE* f_target_h)
{
  char c;

  while((c = fgetc(f_template_c)) != EOF)
  {
    if(c == '?') break;
    fprintf(f_target_c, "%c", c);
  }

  while((c = fgetc(f_template_h)) != EOF)
  {
    if(c == '?') break;
    fprintf(f_target_h, "%c", c);
  }
  

  write_tree(root, arr, top, f_target_c, f_target_h);


  while((c = fgetc(f_template_c)) != EOF)
  {
    fprintf(f_target_c, "%c", c);
  }

  fseek(f_target_h, -2, SEEK_CUR);

  while((c = fgetc(f_template_h)) != EOF)
  {
    fprintf(f_target_h, "%c", c);
  }
}

/**
 * @brief Writes the huffman encoded text to the target file 
 * 
 * @param root Pointer to the root of th tree
 * @param arr Array to strore code
 * @param top Current level in tree
 * @param huffman_encode Huffman code storage array
 */
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


/**
 * @brief The main function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
 * 
 * @param data Array of found characters
 * @param freq Frequency of found character
 * @param size Size of the Heap
 */
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

    FILE *f_target_c = fopen("../decoder/lib/source/decoder.c", "w");
    if (f_target_c == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *f_target_h = fopen("../decoder/lib/include/decoder.h", "w");
    if (f_target_h == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *f_template_c = fopen("../decoder/decoder_template.c", "r");
    if (f_template_c == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *f_template_h = fopen("../decoder/decoder_template.h", "r");
    if (f_template_h == NULL) {
        perror("Error opening file");
        return;
    }

    write_decoder(root, arr, top, f_template_c, f_target_c, f_template_h, f_target_h);

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

    fclose(f_template_c);
    fclose(f_target_c);
    fclose(f_template_h);
    fclose(f_target_h);
    fclose(f_write);
}