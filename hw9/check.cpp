

#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

bool isPrime(int n, int* arr){
    return arr[n] == 0;
}

int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "args";
        exit(1);
    }

    const char *name = "/my_shared_memory";
    const int size = 1000;

    int n = std::stoi(argv[1]);

    int shm_fd = shm_open(name,  O_RDWR, 0666);

    if(shm_fd < 0){
        std::cerr << "open";
        exit(errno);
    }

    int *arr = static_cast<int*>(mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    if(arr == MAP_FAILED){
        std::cerr << "map";
        exit(errno);
    }

    if(isPrime(n, arr) == 0){
        std::cout << "No" << std::endl;
    }
    else{
        std::cout << "Yes" << std::endl;
    }

    if(munmap(arr, size) == -1){
        std::cerr << "unmap";
        exit(errno);
    }

    if(close(shm_fd) == -1){
        std::cerr << "close";
        exit(errno);
    }

    std::cout << "done checking" << std::endl;

    return 0;
}
