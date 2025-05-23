#include <stdio.h>
#include <string.h>  
#include <mpi.h>     

const int MAX_STRING = 100;

int pow_int(int value, int expoente){
   int result =1;
   for(int i =0; i<expoente;i++){
      result *= value;
   }
   return result;
}

int main(void) {
   char       message[MAX_STRING];  
   int        comm_size;               
   int        my_rank;               

   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_size); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   int numero = 0;
   int valor = 0;
   int soma = 0;
//   if (my_rank != 0) { 
      /* Criação da mensagem */
      

      
    if (my_rank == 0) {
        // Apenas o processo 0 define o valor
        numero = 3;
        printf("Processo %d definiu o número %d para ser enviado aos demais.\n", my_rank, numero);
    }

    // Broadcast: todos os processos recebem o valor de "numero" vindo do processo 0
    MPI_Bcast(&numero, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
//   } else {  
      /* Impressão da mensagem do processo centralizador */
    
      for (int q = 1; q < comm_size; q++) {
          
        if(q == 1)
        {
            valor = numero + numero;
            printf("%d", valor);
        }
        else if(q == 2)
        {
            valor = numero * numero;
        }
        else if(q == 3)
        {
            valor = pow_int(numero, numero);
        }
        else
        {
            valor = numero;
        }
         /* Recepção da mensagem do processo q */
        //  MPI_Recv(&valor, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         soma += valor;
         /* Impressão da mensagem do processo q */
        //  printf("O processo %d recebeu a seguinte soma parcial: %d\n", my_rank, soma);
      }
      
      printf("===============================================================\n");
      printf("O processo %d recebeu a seguinte soma total: %d\n", my_rank, soma);
//   }

   /* Finaliza MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
