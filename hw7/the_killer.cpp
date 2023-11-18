#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <sys/wait.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        std::cerr << "fork" << std::endl;
        exit(errno);
    }

    if (child_pid == 0) {
        sleep(2);

        if (kill(getppid(), SIGKILL) == 0) {
            std::cout << "Child has killed its parent." << std::endl;
        }

        else {
                std::cerr << "kill";
        }

        std::cout << "Child is alive" << std::endl;

        exit(0);
    }

    else {
         int status;

         std::cout << "Parent is still alive." << std::endl;

         if(wait(&status) < 0){
                 std::cerr << "wait" << std::endl;
                 exit(errno);
         }

         std::cout << "Parent is still alive." << std::endl;
    }

    return 0;
}
//the parent can be killed, child prosses continues running
