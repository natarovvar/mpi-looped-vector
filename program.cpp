#include <iostream>
#include "mpi.h"
#include <math.h>

using namespace std;

int RandomNumber(int min, int max){
	return min + rand() % (max - min);
}



int main(int argc, char** argv)
{

    int RANK, SIZE;
    int N = 100;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &SIZE);
    MPI_Comm_rank(MPI_COMM_WORLD, &RANK);
    srand(time(NULL));
    
    int vec_send[N];
    int vec_recv[N];

    int next_rank = RANK+1;
    int after_rank = RANK-1; 
    int result[N];
    int number_of_even_numbers = 0;

  	// RING RECV

	if (RANK == SIZE-1) next_rank = 0;
 
          
    	if(RANK == 0) {

		for (int i = 0 ; i < N; i++){
			result[i] = 0;
		}

        	for (int i = 0; i < N; i++){
			vec_send[i] = RandomNumber(1,10);
		}

		MPI_Send(&vec_send, N, MPI_INT, next_rank, 100, MPI_COMM_WORLD);
		MPI_Recv(&vec_recv, N, MPI_INT, SIZE-1 , 100, MPI_COMM_WORLD, &status);
		
		for (int i = 1; i < SIZE - 1; i++){
			MPI_Recv(&number_of_even_numbers, 1, MPI_INT, i, 100, MPI_COMM_WORLD, &status);
			result[i] = number_of_even_numbers;
			cout << "number of even numbers: " << result[i] << " "<< endl;
		}

		 
   	 } 
    	 else {

		MPI_Recv(&vec_recv, N, MPI_INT, after_rank , 100, MPI_COMM_WORLD, &status);
		for (int i = 0; i < N; i++){
			if ((vec_recv[i] % RANK == 0) && (vec_recv[i] % 2 == 0)){
				number_of_even_numbers++;
			}
		}

		 MPI_Send(&vec_recv, N, MPI_INT, next_rank, 100, MPI_COMM_WORLD);
		 MPI_Send(&number_of_even_numbers, 1, MPI_INT, 0, 100, MPI_COMM_WORLD);
		
	}
	
           
        MPI_Finalize();
    return 0;
}
