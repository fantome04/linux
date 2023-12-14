#include <iostream>
#include <vector>
#include <pthread.h>
#include <chrono>

class Number {
public:
    pthread_mutex_t* mutex;
    int x = 0;

    Number() {
        mutex = new pthread_mutex_t();
        pthread_mutex_init(mutex, nullptr);
    }

    ~Number() {
        pthread_mutex_destroy(mutex);
        delete mutex;
    }
};

void* example(void* arg) {
    Number* num = (Number*)arg;
    pthread_mutex_lock(num->mutex);

    for (int i = 0; i < 10000; ++i) {
        num->x++;
    }

    pthread_mutex_unlock(num->mutex);
    return nullptr;
}

int main(int argc, char** argv) {
    Number* num = new Number();
    num->x = 2;

    std::vector<pthread_t> tids(20);

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 20; ++i) {
        pthread_create(&tids[i], NULL, example, (void*)num);
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

//average duration is 5 milliseconds
