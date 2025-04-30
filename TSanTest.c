#include <stdio.h>
#include <pthread.h>

pthread_mutex_t Lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Lock2 = PTHREAD_MUTEX_INITIALIZER;

int GV = 0;

int simple() {
  pthread_mutex_lock(&Lock2);
  GV++;
  pthread_mutex_unlock(&Lock2);
  return GV;
}

void lockWrapper() {
  pthread_mutex_lock(&Lock1);
}

void unlockWrapper() {
  pthread_mutex_unlock(&Lock1);
}

int wrapping() {
  lockWrapper();
  GV++;
  unlockWrapper();
  return GV;
}
