#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

int main(){
	std::string input_file;
	std::cin >> input_file;
	
	int input_fd = open(input_file.c_str(), O_RDONLY, 0666);
	
	if(input_fd == -1){
		std::perror("open input");
                exit(EXIT_FAILURE);
        }		

	int output_fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

        if(output_fd == -1){
                std::perror("open output");
                exit(EXIT_FAILURE);
        }
	
	std::vector<std::string> lines;
	std::vector<char> buff(255, '\0');
	std::string current_line;
    
	while (true) {
		int bytes_read = read(input_fd, buff.data() , buff.size());
		
		if(bytes_read == -1){
			std::perror("read");
			exit(EXIT_FAILURE);
		}

		if(bytes_read == 0){
			break;
		}

	        for (int i = 0; i < bytes_read; i++) {	
		    	if (buff[i] == '\n') {
				lines.push_back(current_line);
				current_line.clear();
			}
			else {
                		current_line += buff[i];
            		}	
       		}	
   	}
    	if (!current_line.empty()) {
        	lines.push_back(current_line);
    	}
	
	std::cout << "The number of lines is " << lines.size() << "\n";

	for (int i = lines.size() - 1; i >= 0; i--) {
        	const std::string& line = lines[i];
        	int bytes_written = write(output_fd, line.c_str(), line.length());
        	if(bytes_written == -1){
			std::perror("write");
                        exit(EXIT_FAILURE);
                }

		bytes_written = write(output_fd, "\n", 1);
		if(bytes_written == -1){
			std::perror("write");
                        exit(EXIT_FAILURE);
                }
    	}

	if(close(input_fd) == -1){
                std::perror("close source");
                exit(EXIT_FAILURE);
        }

        if(close(output_fd) == -1){
                std::perror("close dest");
                exit(EXIT_FAILURE);
        }

}
