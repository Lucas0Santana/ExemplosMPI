#include <stdio.h>
#include <string.h>  
#include <mpi.h>     

int main(void) {
   int        comm_sz;               /* Número de processos    */
   int        my_rank;               /* Rank   do processo     */

   /* Inicia MPI */
   MPI_Init(NULL, NULL); 

   /* Obter número de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* Obter rank (id) do processo */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
   
   char *nome;
   if(my_rank == 0)
   {
      nome = "João";
   }
   else if (my_rank == 1)
   {
      nome ="Maria";
   }
   else if (my_rank == 2)
   {
      nome = "Pedro";
   }
   else if (my_rank == 3)
   {
      nome = "Marta";
   }
   else if (my_rank > 3)
   {
      nome = "Outro";
   }

   printf("Número de processos: %d Rank do processos corrente: %d Nome: %s \n", comm_sz, my_rank, nome);

   /* Encerra MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
