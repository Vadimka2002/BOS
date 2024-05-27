#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t mutex;
pthread_cond_t condition;
bool eventFlag = false;
bool threadsCompleted = false;

void* threadFunction(void* arg) {
    int threadId = *((int*)arg) + 1;

    while(!eventFlag) {
        pthread_mutex_lock(&mutex);
		printf("Thread %d is running\n", threadId);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 5 + 1);
    }
	
    threadsCompleted = true;
    pthread_cond_signal(&condition);
    
    pthread_exit(NULL);
	return 0;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);

    printf("Enter the number of threads: ");
    int N;
    scanf("%d", &N);
    pthread_t threads[N];
    int threadIds[N];
    
    for (int i = 0; i < N; ++i) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, &threadIds[i]);
	}

    printf("Threads created\n");
    sleep(200);
	
	eventFlag = true; 

    pthread_mutex_lock(&mutex);
    while (!threadsCompleted) {
        pthread_cond_wait(&condition, &mutex);
    }
	
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    return 0;
}