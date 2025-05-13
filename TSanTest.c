#include <stdio.h>
#include <pthread.h>

#define LOOP
// #define SIMPLE

#ifdef LOOP
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_ITERS 400000

//#define MANUAL_TSAN_EXCLUDE 1

#ifdef MANUAL_TSAN_EXCLUDE
#	include <sanitizers/tsan_interface.h>
#endif

pthread_mutex_t l1, l2;
int a = 0;
long long int b = 0;

void *ownershipThread( void *unused ) {
  for ( int i = 0; i < NUM_ITERS; i++ ) {
    int acur;

    pthread_mutex_lock( &l1 );
#ifdef MANUAL_TSAN_EXCLUDE
    __tsan_disable();
#endif
    a++;
    acur = a;
#ifdef MANUAL_TSAN_EXCLUDE
    __tsan_enable();
#endif
    pthread_mutex_unlock( &l1 );

    pthread_mutex_lock( &l2 );
#ifdef MANUAL_TSAN_EXCLUDE
    __tsan_disable();
#endif
    for ( int j = 0; j < 20; j++ )
      //b = ( ( b + acur ) * 12345 ) % 0xFFFFFFFF;
        b += 12345;

#ifdef MANUAL_TSAN_EXCLUDE
    __tsan_enable();
#endif
    pthread_mutex_unlock( &l2 );
  }

  return NULL;
}


int main( void ) {
  pthread_t tarr[ NUM_THREADS ];

  pthread_mutex_init( &l1, NULL );
  pthread_mutex_init( &l2, NULL );

  pthread_mutex_lock( &l1 );
#ifdef MANUAL_TSAN_EXCLUDE
  __tsan_disable();
#endif
  a = 0;
  b = 0;
#ifdef MANUAL_TSAN_EXCLUDE
  __tsan_enable();
#endif
  pthread_mutex_unlock( &l1 );

  for ( int i = 0; i < NUM_THREADS; i++ ) {
    pthread_create( &tarr[ i ], NULL, ownershipThread, NULL );
  }

  for ( int i = 0; i < NUM_THREADS; i++ ) {
    pthread_join( tarr[ i ], NULL );
  }

  pthread_mutex_lock( &l1 );
#ifdef MANUAL_TSAN_EXCLUDE
  __tsan_disable();
#endif
  printf( "a = %i, b = %lli\n", a, b );
#ifdef MANUAL_TSAN_EXCLUDE
  __tsan_enable();
#endif
  pthread_mutex_unlock( &l1 );

  return 0;
}

#endif

#ifdef SIMPLE
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

#endif