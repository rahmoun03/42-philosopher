#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	ft_atoi(const char *str);
pthread_mutex_t mutex; // Declare a mutex variable

void* threadFunction(void* arg)
{
    // Acquire the mutex lock
    pthread_mutex_lock(&mutex);

    // Critical section
    printf("Thread %d entered the critical section.\n", *(int*)arg);
    // Simulate some work being done by the thread
    for (int i = 0; i < 5; i++) {
        printf("Thread %d is working...\n", *(int*)arg);
    }
    printf("Thread %d exited the critical section.\n", *(int*)arg);

    // Release the mutex lock
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int ac, char **av) 
{
    (void)ac;
    int philo = ft_atoi(av[1]);
    pthread_t threads[philo];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create three threads
    for (int i = 0; i < philo; i++) {
        pthread_create(&threads[i], NULL, threadFunction, &i);
        usleep(45);
    }

    // Wait for all threads to complete
    for (int i = 0; i < philo; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}