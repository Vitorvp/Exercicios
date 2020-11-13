#include <stdio.h>
#include <unistd.h>

int main(){
  fork();
  while(1){
    puts("*");
  }
}
