#include <stdlib.h>
#include "memoria.h"

static char memoria[1*1024*1024];
static size_t index = 0;

void *aloca(size_t nbytes)
{
    void *mem;

    if(sizeof memoria - index < nbytes){
      return NULL;
    }
    
    mem = &memoria[index];
    index += nbytes;
    return mem;
}

void libera(void *mem){
}
