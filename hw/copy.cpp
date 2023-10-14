#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>

int main(){
        std::cout << "Enter the name of the source file: " << std::endl;
	std::string fd_to_read, fd_to_copy;
        std::cin >> fd_to_read;
        std::cout << "Enter the name of the destination file: " << std::endl;
        std::cin >> fd_to_copy;
        int sf_offset, df_offset, bytes_to_cp;
        std::cout << "Enter the initial offset in the source file: " << std::endl;
        std::cin >> sf_offset;
        std::cout << "Enter the initial offset in the destination file: " << std::endl;
        std::cin >> df_offset;
        std::cout << "Enter the number of bytes to copy: " << std::endl;
        std::cin >> bytes_to_cp;

        int source_fd = open(fd_to_read.c_str(), O_RDONLY, 0666);
        if(source_fd == -1){
                std::perror("open source");
                exit(EXIT_FAILURE);
        }

        int dest_fd = open(fd_to_copy.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
        if(dest_fd == -1){
                std::perror("open dest");
                exit(EXIT_FAILURE);
        }

        if(lseek(source_fd, sf_offset, SEEK_CUR) == -1){
                std::perror("lseek source");
                exit(EXIT_FAILURE);
        }

        if(lseek(dest_fd, df_offset, SEEK_CUR) == -1){
                std::perror("lseek dest");
                exit(EXIT_FAILURE);
        }

        std::vector<char> buff(1);

	while(bytes_to_cp--){
		int bytes_read = read(source_fd, buff.data() , 1);
		if(bytes_read == -1){
			std::perror("read");
			exit(EXIT_FAILURE);
		}

		if(bytes_read == 0){
			break;
		}
	
		int bytes_written = write(dest_fd, buff.data(), bytes_read);
		if(bytes_written == -1){
			std::perror("write");
                        exit(EXIT_FAILURE);
                }
	}


        if(close(source_fd) == -1){
                std::perror("close source");
                exit(EXIT_FAILURE);
        }

        if(close(dest_fd) == -1){
                std::perror("close dest");
                exit(EXIT_FAILURE);
        }
}
