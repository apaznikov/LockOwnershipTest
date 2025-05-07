#include <stdio.h>
#include <pthread.h>

#define SIMPLE

#ifdef SIMPLE
pthread_mutex_t Lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Lock2 = PTHREAD_MUTEX_INITIALIZER;

// void doLock() {
//   pthread_mutex_lock(&Lock1);
// }
//
// void doUnlock() {
//   pthread_mutex_unlock(&Lock1);
// }

int GV1, GV2;

// int foo() {
//   pthread_mutex_lock(&Lock2);
//   doLock();
//   x++;
//   doUnlock();
//   pthread_mutex_unlock(&Lock2);
//   return x;
// }

void CS1() {
  pthread_mutex_lock(&Lock2);
  GV1++;
  pthread_mutex_unlock(&Lock2);
  // GV1++;
}

// void CS2() {
//   pthread_mutex_lock(&Lock2);
//   pthread_mutex_lock(&Lock1);
//   GV1++;
//   GV2++;
//   pthread_mutex_unlock(&Lock1);
//   pthread_mutex_unlock(&Lock2);
// }

//void simple_caller2() {
//  pthread_mutex_lock(&Lock2);
//  simple();
//  pthread_mutex_unlock(&Lock2);
//}

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

int main(void) {
  GV1++;
  printf("Hello, World!\n");
  return 0;
}
#endif