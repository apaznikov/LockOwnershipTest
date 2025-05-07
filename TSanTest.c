#include <stdio.h>
#include <pthread.h>

pthread_mutex_t Lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Lock2 = PTHREAD_MUTEX_INITIALIZER;

int GV1 = 0;

int simple() {
  pthread_mutex_lock(&Lock2);
  GV1++;
  pthread_mutex_unlock(&Lock2);
  return GV1;
}

void lockWrapper() {
  pthread_mutex_lock(&Lock1);
}

void unlockWrapper() {
  pthread_mutex_unlock(&Lock1);
}

int wrapping() {
  lockWrapper();
  GV1++;
  unlockWrapper();
  return GV1;
}

int main(void) {
    wrapping();
    simple();
    printf("Hello, World!\n");
    return 0;
}
