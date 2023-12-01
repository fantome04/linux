#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    const char *name = "/my_shared_memory";
    const int size = 1000;

    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    if(shm_fd < 0){
        std::cerr << "open";
        exit(errno);
    }

    if(ftruncate(shm_fd, size * sizeof(int)) < 0){
        std::cerr << "ftruncate";
        exit(errno);
    }

    int *arr = static_cast<int*>(mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    if(arr == MAP_FAILED){
        std::cerr << "map";
        exit(errno);
    }

    for(int i = 0; i < size; ++i){
        arr[i] = 0;
    }

    if(munmap(arr, size) == -1){
        std::cerr << "unmap";
        exit(errno);
    }

    if(close(shm_fd) == -1){
        std::cerr << "close";
        exit(errno);
    }

    std::cout << "done initializing" << std::endl;
    return 0;
}