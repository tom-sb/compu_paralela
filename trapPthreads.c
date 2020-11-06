#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "timer.h"

const int MAX_THREADS = 1024;

long thread_count;
long long n;
int flag;
double sum;

void* Thread_sum(void* rank);


void Get_input(int my_rank, int comm_sz, double* a_p, double* b_p, int* n_p);
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len);    
double f(double x); 

int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;

   Get_args(argc, argv);

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
   sum = 0.0;
   flag = 0;
   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          trap, (void*)thread);
   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

   
   free(thread_handles);
   return 0;
} 

void* trap(void* rank) {
   long my_rank = (long) rank;
   double start, finish, elapsed;
   int my_rank, comm_sz, n, local_n;   
   double a, b, h, local_a, local_b;
   double local_int, total_int;

   
   while (flag != my_rank);
   h = (b-a)/n;          
   local_n = n/comm_sz;  
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;
   local_int = Trap(local_a, local_b, local_n, h);
   flag = (flag+1) % thread_count;

   return NULL;
}

double Trap(
      double left_endpt  /* in */, 
      double right_endpt /* in */, 
      int    trap_count  /* in */, 
      double base_len    /* in */) {
   double estimate, x; 
   int i;

   estimate = (f(left_endpt) + f(right_endpt))/2.0;
   for (i = 1; i <= trap_count-1; i++) {
      x = left_endpt + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;

   return estimate;
}
double f(double x) {
   return x*x;
}
