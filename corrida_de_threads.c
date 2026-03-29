#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "corrida_de_threads.h"

void* race(void* arg) {
    ThreadData *data = (ThreadData *)arg;
    int id = data->id;

    // LARGADA DOS THREADS!!!!!!!!
    pthread_barrier_wait(&barrier); 
    // faz com que todas as threads parem aqui até que todas estejam prontas, e só depois disso elas vão continuar a corrida
    //isso garante que a corrida seja justa, porque todas as threads começam ao mesmo tempo

    // corrida maluca
    for (int i = 0; i < 100; i++) {
        printf("Thread %d: %d\n", id, i);
    }

    // LINHA DE CHEGADA!!!!!!!!
    // protege variaveis que varias threads tentam mudar ao mesmo tempo
    pthread_mutex_lock(&winner_mutex);
    if (winner_id == -1) { // se ainda não tem vencedor
        winner_id = id; // essa thread é a vencedora
    }
    pthread_mutex_unlock(&winner_mutex);
    return NULL;
}