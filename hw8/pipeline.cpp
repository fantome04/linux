#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

int main(int argc, char** argv){
	if(argc < 4){
		std::cerr<< "args";
		exit(1);
	}

	std::vector<char*> left_args;
	std::vector<char*> right_args;

	bool seen = false;

	for(int i = 1; i < argc; ++i){
		if(!strcmp(argv[i],"?")){
		       seen = true;
		       continue;
		}

		if(seen){
			right_args.push_back(argv[i]);
		}

		else{
			 left_args.push_back(argv[i]);
		}
	}

	if(right_args.empty() || left_args.empty()){
		std::cerr << "args 1";
                exit(1);
        }

	left_args.push_back(nullptr);
	right_args.push_back(nullptr);

	int pipe_fd[2];

	if(pipe(pipe_fd) < 0){
		std::cerr << "pipe";
		exit(errno);
	}

	pid_t pid1 = fork();

	if(pid1 < 0){
		std::cerr << "fork 1";
                exit(errno);
        }

	if(pid1 == 0){
		if(close(pipe_fd[0]) < 0){
			std::cerr << "close";
                	exit(errno);
        	}

		if(dup2(pipe_fd[1], STDOUT_FILENO) < 0){
			std::cerr << "dup";
                        exit(errno);
                }

		if(close(pipe_fd[1]) < 0){
                        std::cerr << "close";
			exit(errno);
		}

		if(execvp(left_args[0], left_args.data()) < 0){
			std::cerr << "command not found";
                        exit(errno);
                }

	}

	else{
		int status;
		if(waitpid(pid1, &status, 0) < 0){
			std::cerr << "close";
                        exit(errno);
                }

		pid_t pid2 = fork();

		if(pid2 < 0){
			std::cerr << "fork 2";
                	exit(errno);
        	}

		if(pid2 == 0){
			if(close(pipe_fd[1]) < 0){
                 	       std::cerr << "close";
                        	exit(errno);
               	 	}

                	if(dup2(pipe_fd[0], STDIN_FILENO) < 0){
                        	std::cerr << "dup";
                        	exit(errno);
                	}

                	if(close(pipe_fd[0]) < 0){
                        	std::cerr << "close";
                        	exit(errno);
                	}

			if(execvp(right_args[0], right_args.data()) < 0){
                        	std::cerr << "command not found";
                        	exit(errno);
                	}
		}

		else{
			if(close(pipe_fd[0]) < 0){
                                std::cerr << "close";
                                exit(errno);
                        }

			if(close(pipe_fd[1]) < 0){
                                std::cerr << "close";
                                exit(errno);
                        }
		}
	
		int status1;
                if(waitpid(pid2, &status1, 0) < 0){
                        std::cerr << "wait";
                        exit(errno);
                }
	}


	return 0;
}


