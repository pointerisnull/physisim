#include <stdlib.h>
#include <stdio.h>
#include "cono.h"
#include "token.h"
#include "table.h"
#include "config.h"

/*KEYWORDS -> THEN SYMBOLS*/
char *getop_str(int **ctable, int co, int no) {
  int code = ctable[co][no];
  /*switch(code) {
    case ERR:
      return (char*)"ERR";
      break;
    case NOOP:
      return (char*)"NOOP";
      break;
    case NEWLN:
      return (char*)"NEWLN";
      break;
    case STARTDEF:
      return (char*)"STARTDEF";
      break;
    case ENDDEF:
      return (char*)"ENDDEF";
      break;
    case INPUT:
      return (char*)"INPUT";
      break;
    case PRINT:
      return (char*)"PRINT";
      break;
    case FUNCDEF:
      return (char*)"FUNCDEF";
      break;
    case PARAM:
      return (char*)"PARAM";
      break;
    case ENDPAREN:
      return (char*)"ENDPAREN";
      break;
    case STARTPROG:
      return (char*)"STARTPROG";
      break;
    case RETURN:
      return (char*)"RETURN";
      break;
  }*/
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
  /*
  for (int i = 0; i < size; i++) {
    ctable[dict_push(dict, SYMBOL_T, (char *) SYM_NEWLINE)][i] = NOOP; 
    ctable[dict_push(dict, KEYWORD_T, (char *) KEYWORD_RETURN)][i] = RETURN; 
    ctable[dict_push(dict, KEYWORD_T, (char *) KEYWORD_PRINT)][i] = PRINT; 
  }
  ctable[dict_push(dict, KEYWORD_T, (char *) KEYWORD_i8)][dict_push(dict, SYMBOL_T, (char *) SYM_EQUALS)] = STARTDEF; 
  ctable[dict_push(dict, KEYWORD_T, (char *) KEYWORD_i8)][dict_push(dict, SYMBOL_T, (char *) SYM_NEWLINE)] = STARTDEF; 
  ctable[dict_push(dict, KEYWORD_T, (char *) KEYWORD_i8)][dict_push(dict, SYMBOL_T, (char *) SYM_COMMA)] = STARTDEF; 
  ctable[dict_push(dict, KEYWORD_T, (char *) KEYWORD_i8)][dict_push(dict, SYMBOL_T, (char *) SYM_RPAREN)] = STARTDEF; 
  ctable[dict_push(dict, SYMBOL_T, (char *) SYM_EQUALS)][dict_push(dict, SYMBOL_T, (char *) SYM_NEWLINE)] = ENDDEF; 
  ctable[dict_push(dict, KEYWORD_T, (char *) KEYWORD_i8)][dict_push(dict, SYMBOL_T, (char *) SYM_LPAREN)] = FUNCDEF; 
  ctable[dict_push(dict, SYMBOL_T, (char *) SYM_LPAREN)][dict_push(dict, SYMBOL_T, (char *) SYM_COMMA)] = PARAM; 
  ctable[dict_push(dict, SYMBOL_T, (char *) SYM_LPAREN)][dict_push(dict, KEYWORD_T, (char *) KEYWORD_i8)] = PARAM; 
  ctable[dict_push(dict, SYMBOL_T, (char *) SYM_COMMA)][dict_push(dict, KEYWORD_T, (char *) KEYWORD_i8)] = PARAM; 
  ctable[dict_push(dict, SYMBOL_T, (char *) SYM_COMMA)][dict_push(dict, SYMBOL_T, (char *) SYM_RPAREN)] = PARAM; 
  ctable[dict_push(dict, SYMBOL_T, (char *) SYM_LPAREN)][dict_push(dict, SYMBOL_T, (char *) SYM_RPAREN)] = PARAM; 
  ctable[dict_push(dict, SYMBOL_T, (char *) SYM_RPAREN)][dict_push(dict, SYMBOL_T, (char *) SYM_NEWLINE)] = ENDPAREN; 
  ctable[dict_push(dict, KEYWORD_T, (char *) KEYWORD_BEGIN)][dict_push(dict, SYMBOL_T, (char *) SYM_NEWLINE)] = STARTPROG; */
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
