

#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){
    const char *name = "/my_shared_memory";
    const int size = 1000;

    int shm_fd = shm_open(name, O_RDWR, 0666);

    if(shm_fd < 0){
        std::cerr << "open";
        exit(errno);
    }

    if(shm_unlink(name) == -1){
        std::cerr << "unlink";
        exit(errno);
    }

    if(close(shm_fd) == -1){
        std::cerr << "close";
        exit(errno);
    }

    std::cout << "done destroying" << std::endl;

    return 0;
}
