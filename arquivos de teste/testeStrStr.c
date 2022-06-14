#include <stdio.h>
#include <string.h>

int main (){

  char* teste[3] = {"sant", "alysson", "lucas"};
  char *pch;


  for (int i = 0; i < 3; i++){
      pch = strstr (teste[i],"san");
        if (pch != NULL){
            printf("tem");
        }
  } 
  
  
  return 0;
}