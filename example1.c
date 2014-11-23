//// to compile this example fron linux use this command "gcc example1.c -o example1 -lpthread" //// 
////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
////////////////////////
char string[100];
pthread_t thr_id_1;
pthread_t thr_id_2;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond, cond1;
int read = 0;
////////////////////////
void *thread_1()
{
    pthread_mutex_lock(&lock);
    while (1) {
        pthread_cond_wait(&cond, &lock);
        printf("thread 1");
        pthread_cond_signal(&cond1);
    }
    pthread_mutex_unlock(&lock);
}
////////////////////////
void *thread_2()
{
    pthread_mutex_lock(&lock);
    while (1) {
        printf("thread 2");
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond1, &lock);
    }
    pthread_mutex_unlock(&lock);
}
////////////////////////
int main(int argc, char *argv[])
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init (&cond, NULL);
    pthread_cond_init (&cond1, NULL);
    pthread_create(&thr_id_1, NULL, thread_1, NULL);
    pthread_create(&thr_id_2, NULL, thread_2, NULL);
    pthread_join(thr_id_1, NULL);
    pthread_join(thr_id_2, NULL);
    return 0;
}
////////////////////////
