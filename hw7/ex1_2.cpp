#include <iostream>
#include <csignal>
#include <unistd.h>

int count = 0;

void signalHandler(int signum) {
    if(signum == SIGUSR1){}

    else if(signum == SIGINT){
        std::cout << "Received SIGINT. Total SIGUSR2 signals: " << count << std::endl;
        exit(0);
    }
}

int main() {
    std::cout << getpid();

    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, [](int signum) { count++; });
    signal(SIGINT, signalHandler);

    while (true){
        std::cout << "I am still alive!!" << std::endl;
        sleep(5);
    }

    return 0;
}
 
