


#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

void Eratosthenes(int *arr, int n)
{
    arr[0] = arr[1] = 1;

    for (int i = 2; i < n; ++i) {
        if (arr[i] == 0) {
            for (int j = i * i; j < n; j += i) {
                arr[j] = 1;
            }
        }
    }
}


int main(){
    const char *name = "/my_shared_memory";
    const int size = 1000;

    int shm_fd = shm_open(name, O_RDWR, 0666);

    if(shm_fd < 0){
        std::cerr << "open";
        exit(errno);
    }

    int *arr = static_cast<int*>(mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    if(arr == MAP_FAILED){
        std::cerr << "map";
        exit(errno);
    }

    Eratosthenes(arr, size);

    if(munmap(arr, size) == -1){
        std::cerr << "unmap";
        exit(errno);
    }

    if(close(shm_fd) == -1){
        std::cerr << "close";
        exit(errno);
    }

    std::cout << "done setting" << std::endl;

    return 0;
}
