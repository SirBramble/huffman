#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

#include <huffman.h>
#include <config.h>

typedef struct
{
  int frequency;
  char character;
} huffman_t;

huffman_t huffman[265];

huffman_t* huffman_start;

void sort(huffman_t* huffman)
{
  // Buble sort. Bad, but me tired...
  for(int i = 0; i < 265; i++)
  {
    for(int n = 1; n < 256; n++)
    {
      if(huffman[n-1].frequency > huffman[n].frequency)
      {
        huffman_t temp = huffman[n-1];
        huffman[n-1] = huffman[n];
        huffman[n] = temp;
      }
    }
  }
}

void print_huffman(huffman_t* huffman)
{
  for(int i = 0; i < 256; i++)
  {
    printf("%c, %d\n", huffman[i].character, huffman[i].frequency);
  }
}

int main(int argc, char *argv[]) {

  if(argc <= 1)
  {
    perror("Please provide the target text file as a argument!");
    return 1;
  }

  if(argv[1] == NULL)
  {
    perror("Please provide the target text file as a argument!");
    return 1;
  }
  else
  {
    printf("Parsing: %s", argv[0]);
  }

  for(int i = 0; i < 256; i++)
  {
    huffman[i].frequency = 0;
    huffman[i].character = i;
  }

  huffman_start = malloc(sizeof(huffman_t));

  FILE *f_vanilla = fopen(argv[1], "r");
  if (f_vanilla == NULL) {
      perror("Error opening text file");
      return 1;
  }

  char ch;
  while ((ch = fgetc(f_vanilla)) != EOF) {
    putchar(ch);
    huffman[ch].frequency++;
  }
  putchar('\n');

  sort(huffman);

  int start_index = 0;

  for(int i = 0; i < 256; i++)
  {
    if(huffman[i].frequency == 0) continue;
    start_index = i;
    break;
  }

  char *arr = malloc(256-start_index);
  int *freq = malloc((256-start_index)*sizeof(int));

  for(int i = 0; i < (256-start_index); i++)
  {
    arr[i] = huffman[start_index+i].character;
    freq[i] = huffman[start_index+i].frequency;
  }

  int size = 256-start_index;

  HuffmanCodes(arr, freq, size);

  rewind(f_vanilla);

  FILE *f_encoded = fopen("../lib/include/encoded_text.h", "w+");
  if (f_encoded == NULL) {
      perror("Error opening file");
      return 1;
  }
  FILE *f_encoded_template = fopen("template/encoded_template.h", "r");
  if (f_encoded_template == NULL) {
      perror("Error opening file");
      return 1;
  }

  FILE *f_encoded_c = fopen("../lib/source/encoded_text.c", "w+");
  if (f_encoded_c == NULL) {
      perror("Error opening file");
      return 1;
  }
  FILE *f_encoded_template_c = fopen("template/encoded_template.c", "r");
  if (f_encoded_template_c == NULL) {
      perror("Error opening file");
      return 1;
  }

  while ((ch = fgetc(f_encoded_template_c)) != EOF) {
    if(ch == '?') break;
    fprintf(f_encoded_c,"%c",ch);
  }

  int index_byte = 0;
  int index_huffman = 0;
  int size_array = 0;
  int size_huffmann = 0;
#if (ENCODE_UINT8 != 0)
  uint8_t temp_storage = 0;
#endif
#if (ENCODE_UINT16 != 0)
  uint16_t temp_storage = 0;
#endif
#if (ENCODE_UINT32 != 0)
  uint32_t temp_storage = 0;
#endif

  ch = fgetc(f_vanilla);

  while (ch != EOF) {
    if(index_byte < ENCODED_BIT_LIMIT)
    {
      temp_storage += (ENCODE_TYPE) huffman_encode[ch].key[index_huffman] << index_byte;
      index_byte++;
    }
    else
    {
      fprintf(f_encoded_c,"\t%u,\n", temp_storage);
      size_array++;
      index_byte = 0;
      temp_storage = 0;
      temp_storage += huffman_encode[ch].key[index_huffman] << index_byte;
      index_byte++;
    }

    

    index_huffman++;
    size_huffmann++;
    if(index_huffman >= huffman_encode[ch].size)
    {
      index_huffman = 0;
      ch = fgetc(f_vanilla);
    }
  }
  
  if(index_byte > 0)
  {
    fprintf(f_encoded_c,"\t%u,\n", temp_storage);
    size_array++;
  }

  fseek(f_encoded_c, -1, SEEK_CUR);

  while ((ch = fgetc(f_encoded_template_c)) != EOF) {
    fprintf(f_encoded_c,"%c",ch);
  }

  rewind(f_encoded);

  while ((ch = fgetc(f_encoded_template)) != EOF) {
    if(ch == '?') break;
    fprintf(f_encoded,"%c",ch);
  }
#if (ENCODE_UINT8 != 0)
  fprintf(f_encoded, "#define ENCODE_TYPE uint8_t");
#endif
#if (ENCODE_UINT16 != 0)
  fprintf(f_encoded, "#define ENCODE_TYPE uint16_t");
#endif
#if (ENCODE_UINT32 != 0)
  fprintf(f_encoded, "#define ENCODE_TYPE uint32_t");
#endif

  while ((ch = fgetc(f_encoded_template)) != EOF) {
    if(ch == '=') break;
    fprintf(f_encoded,"%c",ch);
  }
  fprintf(f_encoded, "%u", size_array);

  while ((ch = fgetc(f_encoded_template)) != EOF) {
    if(ch == '=') break;
    fprintf(f_encoded,"%c",ch);
  }
  fprintf(f_encoded, "%u", size_huffmann);

  while ((ch = fgetc(f_encoded_template)) != EOF) {
    fprintf(f_encoded,"%c",ch);
  }

  free(arr);
  free(freq);
  fclose(f_vanilla);
  fclose(f_encoded);
  fclose(f_encoded_template);
  return 0;
}