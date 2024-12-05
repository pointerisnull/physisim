#ifndef COLLS_CLASS
#define COLLS_CLASS

#include "pmath.h"
#include "object.h"

class Collision {
  private:
    void resolve(Object *a, Object *b);

  public:
    Vec normal;
    float depth;
    bool circle_int(Object a, Object b);
    void handle(Object *a, Object *b);

    Collision();
};

#endif
