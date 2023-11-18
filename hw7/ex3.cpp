#include <iostream>
#include <csignal>
#include <unistd.h>
#include <ucontext.h>

void sigusr1_handler(int signo, siginfo_t *info, void *vcontext) {
    std::cout << "Received SIGUSR1 signal.\nSender's PID: " << info->si_pid << std::endl;

    auto *context = static_cast<ucontext_t *>(vcontext);
    auto mcontext = context->uc_mcontext;
    std::cout << "RIP register : " << mcontext.gregs[REG_RIP] << std::endl;
    std::cout << "RAX register : " << mcontext.gregs[REG_RAX] << std::endl;
    std::cout << "RBX register : " << mcontext.gregs[REG_RBX] << std::endl;
}

int main() {
    std::cout << "My PID: " << getpid() << std::endl;

    struct sigaction sa = {};
    sa.sa_sigaction = sigusr1_handler;

    if(sigaction(SIGUSR1, &sa, nullptr) == -1){
        std::cerr << "sigaction";
        exit(errno);
    }


    while (true) {
        std::cout << "sleeping";
        sleep(10);
    }


    return 0;
}
