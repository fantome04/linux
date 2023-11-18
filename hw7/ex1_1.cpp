#include <iostream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>

void sendSignal(int sigNum, int pid) {
    if (kill(pid, sigNum) == 0) {
        std::cout << "Signal: " << sigNum << "\nPID: " << pid << std::endl;
    }

    else{
        std::cerr << "unable to send signal";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Args";
        exit(errno);
    }

    int signalNumber = std::stoi(argv[1]);
    int pid = std::stoi(argv[2]);

    sendSignal(signalNumber, pid);

    return 0;
}

