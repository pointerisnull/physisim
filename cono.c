#include <stdlib.h>
#include <stdio.h>
#include "cono.h"
#include "token.h"
#include "table.h"
#include "config.h"

/*KEYWORDS -> THEN SYMBOLS*/
char *getop_str(int **ctable, int co, int no) {
  int code = ctable[co][no];
  switch(code) {
    case ERR:
      return (char*)"ERR";
      break;
    case NOOP:
      return (char*)"NOOP";
      break;
    case INIT:
      return (char*)"INIT";
      break;
    case EVENT:
      return (char*)"EVENTS";
      break;
    case APPLY:
      return (char*)"APPLY";
      break;
    case DEFINE:
      return (char*)"DEFINE";
      break;
    case PARAM:
      return (char*)"PARAM";
      break;
   };
  return (char*)"ERR";
}
/********************************
*FUNCTION: cono_combo           *
*PARAMETERS: ctable (cono table)*
*(dictionary pointer) *dict     *
*RETURNS: VOID                  *
*                               *
* This function initiates cono- *
*pairs inside of a 2d array     *
*ctable using dictionary symbols*
*and keywords.                  *
********************************/
void cono_combo(int **ctable, dictionary_t *dict) {
  int size = dict->keywordmax + dict->symbolmax;
  for (int i = 0; i < size; i++) {
    ctable[dict_push(dict, SYMBOL_T, (char *) SYM_NL)][i] = NOOP;

  }
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_INIT       )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = INIT;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_EVENT      )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = EVENT;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_APPLY      )][dict_push(dict, SYMBOL_T, (char *) SYM_AT  )] = APPLY;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_PTCL       )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = DEFINE;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_FORCE      )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = DEFINE;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_MASS       )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_VEL        )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_POS        )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_MAG        )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_DENS       )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_ELAS       )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_RAD        )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_WIDTH      )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
  ctable[dict_push(dict, KEYWORD_T, (char *) KEY_HEIGHT     )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;

  ctable[dict_push(dict, SYMBOL_T, (char *) SYM_AT     )][dict_push(dict, SYMBOL_T, (char *) SYM_NL )] = PARAM;
}

int **init_cono(dictionary_t *dict) {
  int **ctable;
  int size = dict->keywordmax + dict->symbolmax;
  ctable = (int **) malloc(sizeof(int *)*size);
  for (int i = 0; i < size; i++)
    ctable[i] = (int *) malloc(sizeof(int)*size);
  /*initialize all vales to ERROR*/
  for (int i = 0; i < size; i++) 
    for (int j = 0; j < size; j++) 
      ctable[i][j] = ERR;

  cono_combo(ctable, dict);
  

  return ctable;
}

void print_cono(int **ctable, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (ctable[i][j] == -1)
        printf("_ ");
      else if (ctable[i][j] < 10)
        printf("%d ", ctable[i][j]);
      else
        printf("%d", ctable[i][j]);
    }
   printf("\n");
  }
}
