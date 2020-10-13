#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <omp.h>

int fileLength;

//Contains method ot see if a certain value is located in an array - to help facilitate backtracking
bool contains(int val, int *array, int size){
    int i;
    for(i = 0; i < size; i++){
        if(array[i] == val){
            return true;
        }
    }
    return false;

}

void choosePoint(int currPath, int arr[fileLength][fileLength], int size, int * prior, int pri, int count, int * shortest, int * bestPath, int numCities, int thread_count){

   
    int newCurr; 
    prior[count] = pri; 
    count++; 

    //If you reach the end of the path - check to see if it is a better option
    if(count == numCities){
         if(currPath < (*shortest)){
                        *shortest = currPath;
                        memcpy(bestPath, prior, size * sizeof(int));
                    }
        prior[count-1] = -1;
        return;
    }


    //Computation of each of the subtrees - successive recursion calls
     for (int j = 0; j < fileLength; j++) {
         if(!contains(j, prior, size) && currPath + arr[pri][j] < (*shortest)){
                    newCurr = currPath + arr[pri][j];

                choosePoint(newCurr, arr, size, prior, j, count, shortest, bestPath, numCities, thread_count);
                    
         }
     }

        prior[count-1] = -1;
     return;


  
}



int main(int argc, const char *argv[]){


//Pretty costly way of getting how many lines in the file, but it works
FILE* file;
file = fopen(argv[3], "r");
int filelocal = 0;
int thread_count;
thread_count = strtol(argv[1], NULL, 10);


int c = 0;
while((c = fgetc(file)) != EOF){
    if(c == '\n'){
        filelocal++;
    }
}
fclose(file);

fileLength = filelocal;

int numCities = strtol(argv[2], NULL, 10);

//Generating second file pointer to parse through again
FILE* file2;
file2 = fopen(argv[3], "r");
int arr[fileLength][fileLength];
int i = 0;
int j;

for(i=0; i<fileLength; i++){
    for(j = 0; j<fileLength; j++){
        if(fscanf(file2, "%d", &arr[i][j]) != 1){}

        
    }
}






int shortestPath = 10000;
i = 0;
int * shortest;
shortest = &shortestPath;
int * bestPath = malloc(sizeof(int) * fileLength);

    
   

    
    //Begin parallelization here - parallel for  - for each of the threads
    # pragma omp parallel for num_threads(thread_count)
    for (int j = 0; j < fileLength; j++) {
            int newCurr;
            int count = 0; 
            int * prior = malloc(sizeof(int) * fileLength);
            newCurr = arr[0][j];
            //Begin Recursion Call
            choosePoint(newCurr, arr, fileLength, prior, j, count, shortest, bestPath, numCities, thread_count);    

    }






//Printing Best Path
printf("\nBest Path: ");
for(i=0; i <numCities; i++){
    printf(" %d",bestPath[i]);
}

//Printing Shortest Distance
printf("\nShortest Distance %d", *shortest);

return 0;
}



