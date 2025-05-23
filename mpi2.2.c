#include <stdio.h>
#include <string.h>  
#include <mpi.h>     

const int MAX_STRING = 100;

int main(void) {
   char       message[MAX_STRING];  
   int        comm_size;               
   int        my_rank;               

   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_size); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   int valor = 0;
   int soma = 0;
   if (my_rank != 0) { 
      /* Criação da mensagem */
      
      if(my_rank == 1)
      {
         valor = 1 + 1;
      }
      else if(my_rank == 2)
      {
         valor = 2 * 2;
      }
      else if(my_rank == 3)
      {
         valor = 3*3*3;
      }
      else
      {
         valor = my_rank;
      }
      
      /* Envio da mensagem para o processo 0 */
      MPI_Send(&valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
   } else {  
      /* Impressão da mensagem do processo centralizador */
      printf("Processo centralizador em execução: %d of %d!\n", my_rank, comm_size);
      
      for (int q = 1; q < comm_size; q++) {
         /* Recepção da mensagem do processo q */
         // MPI_Recv(&valor, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         soma += valor;
         /* Impressão da mensagem do processo q */
         printf("O processo %d recebeu a seguinte soma parcial: %d\n", my_rank, soma);
      } 
      printf("===============================================================\n");
      printf("O processo %d recebeu a seguinte soma total: %d\n", my_rank, soma);
   }

   /* Finaliza MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
