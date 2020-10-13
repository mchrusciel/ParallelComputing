#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>



void multiples(long int *array, int size, int prime){

    int x = 2;
    while((x*prime)<=(size-1)){
        array[x*prime] = 0;
        x++;

    }

}

int main(int argc, const char *argv[]){


    long int size = atol(argv[1]);
    long int numbers[size];
    
    FILE * file;
    char filename[20];
    sprintf(filename, "%s.txt", argv[1]);
    file = fopen(filename, "w");

     for(int i = 0; i < size+1; i++){
        numbers[i] = 1;
    }


    //From i all the way to about halfway, mark the multiples
    for(int i = 2; i < floor((size+1)/2); i++){

        multiples(numbers, size, i);
       
    }

int len = 0;
numbers[0] = '-';
numbers[1] = '-';

 for (int i = 0; i < size; i++){
     if(numbers[i] == 1){
     len++;
     numbers[i] = i;
     fprintf(file, "%d ", i);
     }
 }



    return 0;




}
