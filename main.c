#include <stdio.h>
#include "bank.c"
typedef struct {
    int bank ;
    char type ;

}s1;


int main(){
 
s1 news1  ; 
   
    news1.bank = 2; 
    printf("%d" , news1.bank )

    return 0;
}
