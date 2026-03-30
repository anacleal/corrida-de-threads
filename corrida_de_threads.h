#define _POSIX_C_SOURCE 200112L
#ifndef CORRIDA_H
#define CORRIDA_H
#include <pthread.h>

typedef struct{
    int id;
} ThreadData;

void *race(void *arg);

extern pthread_barrier_t barrier;
extern pthread_mutex_t winner_mutex;
extern int winner_id;

#endif /* CORRIDA_H */