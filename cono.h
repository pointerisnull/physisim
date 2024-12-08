#ifndef CONO_H
#define CONO_H
/*
#define ERR          -1
#define NOOP          0
#define NEWLN         1
#define STARTDEF      2
#define ENDDEF        3
#define INPUT         4
#define PRINT         5
#define FUNCDEF       6
#define PARAM         7
#define ENDPAREN      8
#define STARTPROG     9
#define RETURN        10
*/
#define ERR      -1
#define NOOP      0
#define INIT      1
#define EVENT     2
#define APPLY     3
#define DEFINE    4
#define PARAM     5

#include "table.h"

int **init_cono(dictionary_t *dict);
char *getop_str(int **ctable, int co, int no);
void print_cono(int **ctable, int size);

#endif
