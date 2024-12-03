#include "pscript.h"
#include <stdlib.h>
#include <stdio.h>

/*reads a file from disk and returns it as a string buff*/
void Interpreter::read_file(char *path) {
  FILE *file;
  char *buff;
  size_t file_size;
  size_t result;

  file = fopen(path, "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  rewind(file);

  buff = (char *)malloc(file_size + 1);
  if (buff == NULL) {
    perror("Memory allocation failed");
    fclose(file);
    return;
  }

  result = fread(buff, 1, file_size, file);
  if (result != file_size) {
    perror("Reading error");
    free(buff);
    fclose(file);
    return;
  }

  buff[file_size] = '\0';

  fclose(file);
  buffer = buff;

}

void Interpreter::run_code() {
  if (buffer == NULL)
    return;
  int count = 0;
  char **lines = split(buffer, DELIMITERS, &count);
  codes = encode(lines, &count, &dict);
  
  free(codes);
  free_split_string(lines, count);
}

Interpreter::Interpreter() {
  
  buffer = NULL; //read_file(filepath);
  dict = dict_create();
  cono = init_cono(&dict);
  table_t memtbl = table_create(dict.identifiermax, INT_TYPE);
  tokens = NULL; //split(buffer, DELIMITERS, &count);
  codes = NULL; // encode(tokens, &count, dict);

}
  /*debugging code
  printf("%s\n", buff);
  debug_print(lines, count);

  printf("Codes: ");
  for (int i = 0; i < count; i++) {
    printf("%d ", codes[i]);
  }
  printf("\n");
  */
