#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* Shared resource for synchronization demonstration */
static int shared_counter = 0;

/* Mutex protects the shared counter */
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Monitor thread */
void *monitor(void *arg)
{
    (void)arg;

    while (1)
    {
        sleep(10);

        printf("\n[Monitor] ShellForge Running...\n");
        fflush(stdout);
    }

    return NULL;
}

/* Worker thread used to demonstrate mutex synchronization */
void *counter_worker(void *arg)
{
    (void)arg;

    for (int i = 0; i < 1000; i++)
    {
        pthread_mutex_lock(&counter_mutex);

        /* Critical section */
        shared_counter++;

        pthread_mutex_unlock(&counter_mutex);
    }

    return NULL;
}

/* Demonstrates pthread_create, mutex synchronization and pthread_join */
void run_thread_demo(void)
{
    pthread_t thread1;
    pthread_t thread2;

    shared_counter = 0;

    pthread_create(&thread1, NULL, counter_worker, NULL);
    pthread_create(&thread2, NULL, counter_worker, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("[Thread Demo] Final counter: %d\n", shared_counter);
}

/* Start background monitor */
void start_monitor_thread(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, monitor, NULL);
    pthread_detach(tid);
}
