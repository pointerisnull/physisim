#ifndef PSCRIPT_CLASS
#define PSCRIPT_CLASS

#define MAX_EVENTS

#include <vector>
#include <map>
#include <string>

#include "table.h"
#include "pmath.h"
#include "object.h"

typedef struct {
  int fi;
  int oi;
  int time;
  bool done;
} event;

class Interpreter {
  private:
    void fillmap();
    void execute(int co, int no, int last);

    char *buffer;
    dictionary_t dict;
    char **tokens;
    int *codes; 
    int **cono;
    std::map<std::string, int> kmap;
    std::map<std::string, int> smap;
    
  public:
    void read_file(char *filepath);
    void run_code();

    Interpreter();
    
    int objc;
    int vecc;
    int eventc;
    table_t objtbl;
    table_t vectbl;
    std::vector<Object> objs;
    std::vector<Vec>    vecs;
    std::vector<event>  events;

};

#endif
