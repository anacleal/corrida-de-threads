#include <stdio.h>
#include <stdlib.h>
#include "corrida_de_threads.h"

// variaveis globais pra sincronizar tudo
pthread_barrier_t barrier; // para que nenhuma thread comece a correr antes de todas estarem prontas
pthread_mutex_t winner_mutex = PTHREAD_MUTEX_INITIALIZER; // para proteger o acesso à variável do vencedor
int winner_id = -1; // id do vencedor, -1 significa que ainda não tem vencedor

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Uso: %s <numero_de_threads>\n", argv[0]);
        return 1;
    }

    int X = atoi(argv[1]);
    pthread_t threads[X];
    ThreadData thread_args[X];

    // inicializa a barreira para X threads
    pthread_barrier_init(&barrier, NULL, X);

    //cria as threads
    for (int i = 0; i < X; i++){
        thread_args[i].id = i + 1;
        if(pthread_create(&threads[i], NULL, race, &thread_args[i]) != 0){ 
            //cria uma nova linha de execução. passa pra ela a funcao que a thread deve executar e os argumentos pra essa função
            perror("Erro ao criar thread");
            return 1;
        }
    }

    // espera as threads terminarem
    for (int i = 0; i < X; i++){
        pthread_join(threads[i], NULL);
        // espera a thread i terminar. o segundo argumento é pra pegar o valor de retorno da thread, mas como nossa função de corrida não retorna nada, passamos NULL
        // se nao usar o pthread_join, a main pode acabar e matar as threads antes delas terminarem a corrida
    }

    printf("\nResultado final!!!\n");
    printf("O vencedor é a Thread %d\n", winner_id);

    //limpeza
    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&winner_mutex);

    return 0;
}