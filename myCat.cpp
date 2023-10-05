#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

constexpr size_t buffer_size = 4096;

int main(int argc, char** argv){
	if(argc != 2){
		perror("arguments");
		exit(errno);
	}
	
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("open");
		exit(errno);
	}

	std::string buff;
	
	while(true){
		char buff_read[4096];
		int bytes_read = read(fd, buff_read, buffer_size);
		if(bytes_read == 0){
			break;
		}
		else if(bytes_read < 0){
			perror("read");
			exit(errno);
		}
		else{
			buff.append(buff_read);
		}
	
	}

	std::cout << buff;
	close(fd);


	return 0;
}


