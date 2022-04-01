#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int finished_threads=1;
int max_threads=24;
int thread_count,   end_entered,   start_entered;
int *prim_array=NULL;
int array_length = 0;

int* progress()
{
   
   int finished_thread_displayed = 0;
   while (finished_threads<max_threads)
   {
      if (finished_threads >= finished_thread_displayed) {
      printf("#");

      finished_thread_displayed++;
      }
     
   }
   
   
}
int* Prime_number_calc(int tread_intern_count) 
{
   int teiler_count,Prime_teiler,prime_number,end_intern,start_intern,ö;
   start_intern=((end_entered-start_entered)/max_threads*tread_intern_count)+start_entered;
   end_intern=((end_entered-start_entered)/max_threads*(tread_intern_count+1))+start_entered;
  
   for (prime_number = start_intern; prime_number < end_intern; prime_number++)
   {
      teiler_count=0;ö=prime_number/2;
      for (Prime_teiler = 1; Prime_teiler <= ö; Prime_teiler++)
      {
         if (prime_number%Prime_teiler==0)
         {
            teiler_count++;
         }
      }
      if (teiler_count==1)
      {                                        
         array_length++;
         prim_array = realloc(prim_array,array_length*sizeof(int));   prim_array[array_length-1] = prime_number;
      }
   
   }
   finished_threads++;
   return(0);
}
int cmpfunc (const void * a, const void * b)
 {
   return ( *(int*)a - *(int*)b );
 }
int main()
{  
   pthread_t progressbar;
   pthread_t thread[max_threads];
   prim_array = calloc(10000,sizeof(int));

   printf("start:");
   scanf("%d",&start_entered);
   printf("ende:");
   scanf("%d",&end_entered);

   printf("\n\nwait... \n\n");
   printf("Progress:\n");
   printf("0     25   50    75    100\n");
   printf("|_____|_____|_____|_____|\n");

   pthread_create(&progressbar, NULL,*progress,NULL);
   for ( thread_count = 0; thread_count < max_threads; thread_count++)
   {
      pthread_create(&thread[thread_count], NULL,*Prime_number_calc,thread_count);
   
   }
   pthread_join(progressbar,NULL);

   for ( thread_count = 0; thread_count < max_threads; thread_count++)
   {
     pthread_join(thread[thread_count],NULL);
   }    

   printf("\nfinished \n\nsorting...\n\n\n");
   qsort(prim_array,array_length,sizeof(int),cmpfunc);

   for (int i = 0; i < array_length ; i++)
   {
      if (prim_array[i]>0 && prim_array[i]<end_entered)
      {
         printf("%d,",prim_array[i]);
      }
   }

   free(prim_array);

   printf("\n\nAnzahl: %d\n\n",array_length);

   //char ch;scanf("%s",&ch);
   
   
}