#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

constexpr size_t buffer_size = 4096;

int main(int argc, char** argv){
        if(argc != 3){
                perror("arguments");
                exit(errno);
        }

        int copy_from_fd = open(argv[1], O_RDONLY);
        if(copy_from_fd == -1){
                perror("open");
                exit(errno);
        }

	int copy_to_fd = open(argv[2], O_WRONLY | O_CREAT, 0600);
	if(copy_to_fd == -1){
                perror("open");
                exit(errno);
        }


        std::string buff;

        while(true){
                char buff_read[4096];
                int bytes_read = read(copy_from_fd, buff_read, buffer_size);
                if(bytes_read == 0){
                        break;
                }
                else if(bytes_read < 0){
                        perror("read");
                        exit(errno);
                }
              	int bytes_written = write(copy_to_fd, buff_read, bytes_read);
		if(bytes_written < 0){
			perror("write");
			exit(errno);
		}
 	}

        close(copy_to_fd);
	close(copy_from_fd);

        return 0;
}

