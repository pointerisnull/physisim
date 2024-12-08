#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "table.h"
#include "pmath.h"

float to_float(char *str);

table_t table_create(int size, int type) {
  table_t ret;
  ret.type = type;
  ret.size = size;
  ret.tokc = 0;
  if (type == STRING_TYPE)
    ret.content_s = (char **) malloc(sizeof(char *) * size);
  else if (type == FLOAT_TYPE)
    ret.content_f = (float *) malloc(sizeof(float *) * size);
  else if (type == INT_TYPE)
    ret.content_i = (int *) malloc(sizeof(int *) * size);
  return ret;
}

int table_insert(table_t *table, int index, void *content) {
  if (index > table->tokc)
    return -1;
  float num = to_float((char*)content);
  switch (table->type) {
    case INT_TYPE:
      //int num = to_float((char*)content);
      table->content_i[index] = (int)num;
      break;
    case STRING_TYPE:
      table->content_s[table->tokc] = (char *)content;
      break;
    case FLOAT_TYPE:
      table->content_f[index] = num;
      break;
  }
  return 0;
}

void table_push(table_t *table, void *content) {
  float num = to_float((char*)content);
  int numi = (int)(*(float *)content);

  switch (table->type) {
    case INT_TYPE:
      if (table->tokc >= table->size) {
        table->size *= 2;
        table->content_i = (int *) realloc(table->content_i, table->size * sizeof(int *));
      }
      table->content_i[table->tokc] = (int)numi;
      table->tokc ++;

      break;
    case STRING_TYPE:
      if (table->tokc >= table->size) {
        table->size *= 2;
        table->content_s = (char **) realloc(table->content_s, table->size * sizeof(char **));
      }
      table->content_s[table->tokc] = (char *)content;
      table->tokc ++;
      //printf("table content: %s\n", (char *)table->content[table->tokc-1]);
      break;
    case FLOAT_TYPE:
      if (table->tokc >= table->size) {
        table->size *= 2;
        table->content_f = (float *) realloc(table->content_f, table->size * sizeof(float *));
      }
      table->content_f[table->tokc] = num;
      table->tokc ++;

      break;
  }
}

void table_fill(table_t *table, int size, char *val) {
  for (int i = 0; i < size; i++)
    table_push(table, val);
}

void table_free(table_t *table) {
  if (table->type == STRING_TYPE) 
    free(table->content_s);
  else if (table->type == INT_TYPE)
    free(table->content_f);
  else if (table->type == FLOAT_TYPE)
    free(table->content_i);
}

int table_get_i(table_t table, int content) {
  if (table.type == INT_TYPE) {
    for (int i = 0; i < table.tokc; i++) {
      if (table.content_i[i] == content)
        return i;
    }
  }
  return -1;
}

void table_print(table_t table) {
  for (int i = 0; i < table.tokc; i++) {
    if (table.type == STRING_TYPE)
      printf("index %d: %s\n", i, table.content_s[i]);
    else if (table.type == FLOAT_TYPE)
      printf("index %d: %f\n", i, table.content_f[i]);
    else if (table.type == INT_TYPE)
      printf("index %d: %d\n", i, table.content_i[i]);
  }
}

void dict_print(dictionary_t dict);

dictionary_t dict_create() {
  dictionary_t ret;
  ret.keywordc =    0;
  ret.symbolc =     0;
  ret.identifierc = 0;
  ret.constantc =   0;
  ret.literalc =    0;
  
  ret.keywordmax = KEYWORD_COUNT; 
  ret.symbolmax = SYMBOL_COUNT;
  ret.identifiermax = IDENTIFIER_COUNT;
  ret.constantmax = CONSTANT_COUNT;
  ret.literalmax = LITERAL_COUNT;
  ret.keyword_table = table_create(ret.keywordmax, STRING_TYPE);
  ret.symbol_table = table_create(ret.symbolmax, STRING_TYPE);
  ret.constant_table = table_create(ret.constantmax, FLOAT_TYPE);
  ret.literal_table = table_create(ret.literalmax, STRING_TYPE);
  ret.identifier_table = table_create(ret.identifiermax, STRING_TYPE);
  ret.identifier_val_table = table_create(ret.identifiermax, FLOAT_TYPE);
  ret.identifier_type_table = table_create(ret.identifiermax, INT_TYPE);

  return ret;
}
//returns the local index of item found. If not found, return -1
int dict_search(dictionary_t dict, int type, void *content) {

  switch (type) {
    case KEYWORD_T:
      for (int i = 0; i < dict.keyword_table.tokc; i++)
        if (strcmp ((char*)content, (char*)dict.keyword_table.content_s[i]) == 0 )
          return i;
    break;
    case SYMBOL_T:
      for (int i = 0; i < dict.symbol_table.tokc; i++)
        if (strcmp ((char*)content, (char*)dict.symbol_table.content_s[i]) == 0 )
          return i;
    break;
    case CONSTANT_T:
      for (int i = 0; i < dict.constant_table.tokc; i++) {
        float in = atof((char*)content);
        int equal = fcomp(in, dict.constant_table.content_f[i]);
        //if (*(float*)content == dict.constant_table.content_f[i])
        if (equal)
          return i;
      }
    break;
    case LITERAL_T:
      for (int i = 0; i < dict.literal_table.tokc; i++)
        if (strcmp ((char*)content, (char*)dict.literal_table.content_s[i]) == 0 )
          return i;
    break;
    case IDENTIFIER_T:
      for (int i = 0; i < dict.identifier_table.tokc; i++)
        if (strcmp ((char*)content, (char*)dict.identifier_table.content_s[i]) == 0 )
          return i;
    break;
    default:
      return -1;
    break;
  }
  return -1;
}

int dict_push(dictionary_t *dict, int type, void *content) {
  int li = dict_search(*dict, type, (void *)content);
  int code;
  //printf("DICTIONARY: (%s) type: %d\n", (char *)content, type);
  switch (type) {
    case KEYWORD_T:
      if (li >= 0) return li;
      table_push(&dict->keyword_table, content);
      code = dict->keywordc;
      dict->keywordc++;
      return code;
    break;
    case SYMBOL_T:
      if (li >= 0) return li+dict->keywordmax;
      table_push(&dict->symbol_table, content);
      code = dict->keywordmax + dict->symbolc;
      dict->symbolc++;
      return code;
    break;
    case CONSTANT_T:
      if (li >= 0) 
        return li+dict->keywordmax+dict->symbolmax;
      //printf("INCOMMING: %s\n", (char *)content);
      table_push(&dict->constant_table, content);
      code = dict->keywordmax+dict->symbolmax+dict->constantc;
      dict->constantc++;
      return code;
    break;
    case LITERAL_T:
      if (li >= 0) 
        return li+dict->keywordmax+dict->symbolmax+dict->constantmax;
      table_push(&dict->literal_table, content);
      code = dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalc;
      dict->literalc++;
      return code;
    break;
    case IDENTIFIER_T:
      if (li >= 0) 
        return li+dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax;
      table_push(&dict->identifier_table, content);
      code = dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax+dict->identifierc;
      dict->identifierc++;
      return code;
    break;

  }
  return -1;
}

float dict_get_f(dictionary_t dict, int index) {
  int li = local_index(&dict, index);
  //if (dict.constant_table.content_f[li] != NULL)
  return dict.constant_table.content_f[li];
  //return 0.0;
}

char *dict_get_s(dictionary_t dict, int index) {
  int li = local_index(&dict, index);
  if (dict.literal_table.content_s[li] != NULL)
    return dict.literal_table.content_s[li];
  return NULL;
}

int local_index(dictionary_t *dict, int code) {
  if (code < dict->keywordmax)
    return code;
  else if (code < dict->keywordmax+dict->symbolmax)
    return code - (dict->keywordmax);
  else if (code < dict->keywordmax+dict->symbolmax+dict->constantmax)
    return code - (dict->keywordmax+dict->symbolmax);
  else if (code < dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax)
    return code - (dict->keywordmax+dict->symbolmax+dict->constantmax);
  else if (code < dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax+dict->identifiermax)
    return code - (dict->keywordmax+dict->symbolmax+dict->constantmax+dict->literalmax);
  else return -1;
}

float to_float(char *str) {
  float test = atof(str);
  if (test != 0.0) 
    return test;
  else if (!strncmp(str, "0.0", 2))
      return test;
  return 0.0;
}
