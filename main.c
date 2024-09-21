#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_N 50

typedef struct {
  int n;
  int *result;
} ThreadArgs;

int fib_trad (int n) {
  if (n <= 1) {
    return n;
  }
  return fib_trad(n-1) + fib_trad(n-2);
}

void *fib_thread (void *args) {
  ThreadArgs *thread_args = (ThreadArgs *)args;
  int n = thread_args->n;
  int *result = thread_args->result;
  *result = fib_trad(n);
  pthread_exit(NULL);
}

 int fib(int n)                             
 {                                          
   pthread_t threads[2];
   ThreadArgs args[2];
   int results[2];

   int i;
   for (i = 0; i < 2; i++) {
     args[i].n = n - i - 1;
     args[i].result = &results[i];
     pthread_create(&threads[i], NULL, fib_thread, (void *)&args[i]);
   }

   for (i = 0; i < 2; i++) {
     pthread_join(threads[i], NULL);
   }

   return results[0] + results[1];
 }                                          

int main(void)
{
  struct timeval start, end;
  int result;
  int n = MAX_N;

  gettimeofday(&start, NULL);
  result = fib_trad(n);
  gettimeofday(&end, NULL);
  printf("Fibinacci tradicional (n = %d): %lld\n", n, result);
  printf("Tempo tradicional: %ld microssegundos\n\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

  gettimeofday(&start, NULL);
  result = fib(n);
  gettimeofday(&end, NULL);
  printf("Fibinacci com threads (n = %d): %lld\n", n, result);
  printf("Tempo com threads: %ld microssegundos\n\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

  return 0;
}
