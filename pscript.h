#ifndef PSCRIPT_CLASS
#define PSCRIPT_CLASS

#include "config.h"
#include "lexer.h"
#include "token.h"
#include "table.h"
#include "cono.h"
#include "interp.h"


class Interpreter {
  private:
    char *buffer;
    dictionary_t dict;
    table_t memtbl;

    char **tokens;
    int *codes; 
    int **cono;

  public:
    void read_file(char *filepath);
    void run_code();

    Interpreter();

};

#endif
