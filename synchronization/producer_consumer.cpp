#include <iostream>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <unistd.h>

const int BUFFER_SIZE = 5;

int buffer[BUFFER_SIZE];
int in = 0;     
int out = 0;  

sem_t emptySlots;
sem_t fullSlots;
std::mutex mtx;

void producer() {
    for (int i = 1; i <= 10; i++) {

        sem_wait(&emptySlots);  // wait if buffer full

        mtx.lock();

        buffer[in] = i;
        std::cout << "Produced: " << i << " at index " << in << std::endl;
        in = (in + 1) % BUFFER_SIZE;   // circular increment

        mtx.unlock();

        sem_post(&fullSlots);   // signal item available

        usleep(100000);
    }
}

void consumer() {
    for (int i = 1; i <= 10; i++) {

        sem_wait(&fullSlots);   // wait if buffer empty

        mtx.lock();

        int item = buffer[out];
        std::cout << "Consumed: " << item << " from index " << out << std::endl;
        out = (out + 1) % BUFFER_SIZE; // circular increment

        mtx.unlock();

        sem_post(&emptySlots);  // signal space available

        usleep(150000);
    }
}

int main() {

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);

    std::thread p(producer);
    std::thread c(consumer);

    p.join();
    c.join();

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);

    return 0;
}
