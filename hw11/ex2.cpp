#include <iostream>
#include <vector>
#include <pthread.h>

class BankAccount {
private:
    int balance;
    pthread_mutex_t* mutex;

public:
    BankAccount(int balance_)
        : balance(balance_){
        mutex = new pthread_mutex_t();
        pthread_mutex_init(mutex, nullptr);
    }

    void debit(int amount) {
        pthread_mutex_lock(mutex);
        balance -= amount;
        pthread_mutex_unlock(mutex);
    }

    void credit(int amount) {
        pthread_mutex_lock(mutex);
        balance += amount;
        pthread_mutex_unlock(mutex);
    }

    int getBalance() const {
        pthread_mutex_lock(mutex);
        int curr = balance;
        pthread_mutex_unlock(mutex);
        return curr;
    }

    ~BankAccount() {
        pthread_mutex_destroy(mutex);
        delete mutex;
    }
};

void* performOperations(void* arg) {
    BankAccount* account = static_cast<BankAccount*>(arg);

    for (int i = 0; i < 1000; ++i) {
        account->debit(4);
        account->credit(5);
    }

    return nullptr;
}

int main() {
    BankAccount account(1000);

    std::vector<pthread_t> threads(20);

    for (int i = 0; i < 20; ++i) {
        if(pthread_create(&threads[i], nullptr, performOperations, &account) != 0){
            std::cerr << "create";
            exit(errno);
        }
    }

    for (int i = 0; i < 20; ++i) {
        if(pthread_join(threads[i], nullptr) != 0){
            std::cerr << "join";
            exit(errno);
        }
    }

    std::cout << "Final balance: " << account.getBalance() << std::endl;

    return 0;
}
