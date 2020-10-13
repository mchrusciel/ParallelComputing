#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>



void handleInput(int * numbers, int size, int * copy, int * copy2){

    for(int i = 0; i < size; i++){
        numbers[i] = 1;
        copy[i] = 1;
        copy2[i] = 1;
    }

}



void multiples(int *array, int size, int prime){
    int x = 2;
    while((x*prime)<=(size-1)){
        array[x*prime] = 0;
        x++;

    }

}



int main(int argc, const char *argv[]){
    //FILE * file;
    int comm_sz, my_rank,  size = atoi(argv[1]);
    FILE * file;
    char filename[20];
    int local_start, local_end;
    
    int * numbers = malloc(size * sizeof(int));
    int * copyArray = malloc(size * sizeof(int));
    int * copy2 = malloc(size * sizeof(int));
    int source;

    
    
    
    

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    
    /* Code Here Handles if Rank is 0 i.e. Process 0 */
    
    if(my_rank == 0){


        
        handleInput(numbers, size, copyArray, copy2);

        
        for(int i = 1; i < comm_sz; i++){
         local_start = i * floor(floor((size+1)/2)/comm_sz + .5); //Finding the local starting point - product of the rank (which starts at 0) and up to the floor of the middle/comm_sz
         local_end = (i+1) * floor(floor((size+1)/2)/comm_sz +.5)-1; //Virtually same as locating the start, except now calculating the end


        MPI_Send(&local_start, 1, MPI_INT, i, 1, MPI_COMM_WORLD);

        MPI_Send(&local_end, 1, MPI_INT, i, 2, MPI_COMM_WORLD);

        MPI_Send(copyArray, size, MPI_INT, i, 3, MPI_COMM_WORLD );

        }

   

          
        for (source = 1; source <comm_sz; source++){

                MPI_Recv(copyArray, size, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int i = 0; i < size; i++){
                    if(copyArray[i] == 0){
                        
                        numbers[i] = 0;

                    }
                }

    
        }
    }

    else{  /* All the other processes*/
       
        MPI_Recv(&local_start, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&local_end, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(copyArray, size, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
     //Calculating multiples up to a point - utilizing local starting point and the local ending point
     for(int i = local_start; i < local_end; i++){


        multiples(copyArray, size, i);
       
    }   

     MPI_Send(copyArray, size ,MPI_INT, 0,4,MPI_COMM_WORLD);

    //At this point, the local copy of the numbers array for this process should be completed, now to send them back to process 0
         
    }




MPI_Finalize();

if(my_rank == 0){
   
    int lim = floor(floor((size+1)/2)/comm_sz +.5)-1;
   

    for(int i = 0; i < size; i ++){
        copy2[i] = numbers[i];
    }

        

    for(int i = 2; i < size; i ++){
        int x = 2;
    
    while((x*i)<=(size-1)){
        copy2[x*i] = 0;
        x++;
    }

    }



    for(int i = 0; i < size; i++){
                    if(copy2[i] == 0){
                        
                    numbers[i] = 0;

                    }
                }

    

        
        sprintf(filename, "%s.txt", argv[1]);
        file = fopen(filename, "w");

        numbers[0] = '-';
        numbers[1] = '-';

         for (int i = 0; i < size; i++){
         if(numbers[i] == 1){
            numbers[i] = i;

        fprintf(file, "%d ", i);
        }
       }
}
        return 0;

}

   


