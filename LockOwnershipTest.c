#include <stdio.h>
#include <pthread.h>

pthread_mutex_t Lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Lock2 = PTHREAD_MUTEX_INITIALIZER;

// void doLock() {
//   pthread_mutex_lock(&Lock1);
// }
//
// void doUnlock() {
//   pthread_mutex_unlock(&Lock1);
// }

int x = 0;

// int foo() {
//   pthread_mutex_lock(&Lock2);
//   doLock();
//   x++;
//   doUnlock();
//   pthread_mutex_unlock(&Lock2);
//   return x;
// }

int simple() {
  x++;
  return x;
}

void simple_caller2() {
  pthread_mutex_lock(&Lock2);
  simple();
  pthread_mutex_unlock(&Lock2);
}

// void bar(int x) {
//   pthread_mutex_lock(&Lock1);
//   if (x > 0)
//     pthread_mutex_lock(&Lock2);
//
//   pthread_mutex_unlock(&Lock1);
//
//   if (x > 0)
//     pthread_mutex_unlock(&Lock2);
// }

// int main(void) {
//     printf("Hello, World!\n");
//     return 0;
// }