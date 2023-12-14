#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <chrono>

class Number {
public:
    sem_t* sem;
    int x = 0;

    Number() {
        sem = new sem_t();
        sem_init(sem, 0, 1);
    }

    ~Number() {
        sem_destroy(sem);
        delete sem;
    }
};

void* example(void* arg) {
    Number* num = (Number*)arg;
    sem_wait(num->sem);

    for (int i = 0; i < 10000; ++i) {
        num->x++;
    }
    sem_post(num->sem);

    return nullptr;
}

int main(int argc, char** argv) {
    Number *num = new Number();
    num->x = 2;
    std::vector<pthread_t> tids(20);

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 20; ++i) {
        pthread_create(&tids[i], NULL, example, (void *) num);
    }

    for (int i = 0; i < 20; ++i) {
        pthread_join(tids[i], NULL);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << duration << "\n" << num->x << std::endl;
    delete num;

    return 0;
}

//average duration is 6 milliseconds