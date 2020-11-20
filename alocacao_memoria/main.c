#include <stdio.h>
#include "memoria.h"

int main(){

  int *p = (int *) aloca(4*sizeof(int));
  *p = 100;
  libera(p);

}
