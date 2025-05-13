#include <stdio.h>
#include <pthread.h>

#define LOOP
// #define SIMPLE

#ifdef LOOP
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
    a++;
    pthread_mutex_unlock( &l1 );

    pthread_mutex_lock( &l2 );
    for ( int j = 0; j < 20; j++ )
      b += 12345;
    pthread_mutex_unlock( &l2 );
  }

  return NULL;
}


int main( void ) {
  pthread_t tarr[ NUM_THREADS ];

  pthread_mutex_init( &l1, NULL );
  pthread_mutex_init( &l2, NULL );

  pthread_mutex_lock( &l1 );
  a = 0;
  b = 0;
  pthread_mutex_unlock( &l1 );

  for ( int i = 0; i < NUM_THREADS; i++ )
    pthread_create( &tarr[ i ], NULL, ownershipThread, NULL );

  for ( int i = 0; i < NUM_THREADS; i++ )
    pthread_join( tarr[ i ], NULL );

  pthread_mutex_lock( &l1 );
  printf( "a = %i, b = %lli\n", a, b );
  pthread_mutex_unlock( &l1 );

  return 0;
}

#elifdef SIMPLE
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