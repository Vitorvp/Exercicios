#include <stdlib.h>
#include <stdio.h>

static char memoria[1024*1024]; //reserve 1 MB for malloc
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

int main(){

  int *p = (int *) aloca(4*sizeof(int));
  *p = 100;
  printf("%d", *p);
  libera(p);

}
