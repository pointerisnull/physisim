#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#include "pscript.h"
#include "config.h"
#include "lexer.h"
#include "token.h"
#include "table.h"
#include "cono.h"

int march_ops(dictionary_t *dict, int *codes, int size, int current) {
  if (current >= size-1) return size;
  for (int i = current+1; i < size; i++) {
    int cls = classify_code(codes[i], dict);
    if (cls == KEYWORD_T || cls == SYMBOL_T)
      return i;
  }
  return size;
}
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

void Interpreter::fillmap() {
  for (int i = 0; i < KEYWORD_COUNT; i++) {
    if (KEYWORDS[i] != NULL)
      kmap[(std::string)KEYWORDS[i]] = i;
  }
  for (int i = 0; i < SYMBOL_COUNT; i++) {
    if (SYMBOLS[i] != NULL)
      kmap[(std::string)SYMBOLS[i]] = i;
  }
}

void Interpreter::execute(int co, int no, int last) { 
  int op = cono[codes[co]][codes[no]]; 
  int index; 
  int li; 
  int c = 0; 
  char *str;
  char **vecstr; 
  const char *vecdelims = ","; 
  float temp = (float)codes[co+1]; 
  event ev;
  switch(op) { 
    /*
    case INIT:
      printf("initializing program...\n\n");
      break;
    case EVENT: 
      printf("\nmoving to events...\n\n");
      break;
    */
    case APPLY:
      printf("Applying force...\n");
      
      ev = { 
        table_get_i(vectbl, codes[co+1]),
        table_get_i(objtbl, codes[co+2]),
        (int) dict_get_f(dict, codes[co+4]),
        false
      };
      printf("ind: %d\n", ev.fi);
      events.push_back(ev);
      eventc++;
      break;
    case DEFINE:
      index = codes[co]; 
      if (index == 3) { //particle
        Object particle({100,100,0}, 15.0, 0.01, 0.1, 1.8, false);
        objs.push_back(particle);

        table_push(&objtbl, &temp);
        objc++;
      } else if (index == 4) { //force
        Vec force = {10, 10, 0};
        vecs.push_back(force);
        
        table_push(&vectbl, &temp);
        vecc++;
      }

      break;
    case PARAM:
      index = codes[co];
      if (index == kmap[(std::string)KEY_MASS]) {
        li = table_get_i(objtbl, codes[co-1]);
        objs.at(li).setmass( dict_get_f(dict, codes[co+1]) );//0.01); //codes[co+1]);
        break;
      }      
      if (index == kmap[(std::string)KEY_RAD]) {
        li = table_get_i(objtbl, codes[co-1]);
        objs.at(li).setradius( dict_get_f(dict, codes[co+1])); //codes[co+1]);
        break;
      }
      if (index == kmap[(std::string)KEY_WIDTH]) {
        li = table_get_i(objtbl, codes[co-1]);
        objs.at(li).setheight( dict_get_f(dict, codes[co+1])); //codes[co+1]);
        break;
      }
      if (index == kmap[(std::string)KEY_HEIGHT]) {
        li = table_get_i(objtbl, codes[co-1]);
        objs.at(li).setheight( dict_get_f(dict, codes[co+1])); //codes[co+1]);
        break;
      }
      if (index == kmap[(std::string)KEY_DENS]) {
        li = table_get_i(objtbl, codes[co-1]);
        objs.at(li).setdens( dict_get_f(dict, codes[co+1])); //codes[co+1]);
        break;
      }
      if (index == kmap[(std::string)KEY_ELAS]) {
        li = table_get_i(objtbl, codes[co-1]);
        objs.at(li).setelas( dict_get_f(dict, codes[co+1])); //codes[co+1]);
        break;
      }
      if (index == kmap[(std::string)KEY_POS]) {
        li = table_get_i(objtbl, codes[co-1]);
        str = dict_get_s(dict, codes[co+1]);
        str[0] = ' ';
        str[strlen(str)-1] = ' ';
        vecstr = split(str, vecdelims, &c);
        objs.at(li).setpos({(float)atof(vecstr[0]), (float)atof(vecstr[2]), 0});
        break;
      }
      if (index == kmap[(std::string)KEY_MAG]) {
        li = table_get_i(vectbl, codes[co-1]);
        str = dict_get_s(dict, codes[co+1]);
        str[0] = ' ';
        str[strlen(str)-1] = ' ';
        vecstr = split(str, vecdelims, &c);
        vecs.at(li) = {(float)atof(vecstr[0]), (float)atof(vecstr[2]), 0};
        break;
      }
      break;
  }
  
}

void Interpreter::run_code() {
  if (buffer == NULL)
    return;
  int count = 0;
  char *delims = DELIMITERS;
  char **lines = split(buffer, delims, &count);
  int codec = count;
  codes = encode(lines, &codec, &dict);
  //cono
  int lastop = 0;
  
  for (int i = 0; i < codec; i++) {
    int co = i;
    int no = march_ops(&dict, codes, codec, i);
    if (no < codec && cono[codes[co]][codes[no]] != ERR && cono[codes[co]][codes[no]] != NOOP) {
      execute(co, no, lastop);   
      lastop = co;
    }
    i = no-1;
  }

  free(codes);
  free_split_string(lines, count);

}

Interpreter::Interpreter() {
  objc = 0;
  vecc = 0;
  eventc = 0;
  objtbl = table_create(8, INT_TYPE);
  vectbl = table_create(8, INT_TYPE);
  
  fillmap();

  buffer = NULL; //read_file(filepath);
  dict = dict_create();
  cono = init_cono(&dict);
  tokens = NULL; //split(buffer, DELIMITERS, &count);
  codes = NULL; // encode(tokens, &count, dict);

}
