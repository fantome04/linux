#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int child_to_parent[2];
	int parent_to_child[2];

	if (pipe(child_to_parent) == -1 || pipe(parent_to_child) == -1) {
        	std::cerr << "pipe";
        	exit(errno);
    	}

	pid_t first_pid = fork();

	if(first_pid < 0){
		std::cerr << "first fork";
                exit(errno);
	}

	else if(first_pid == 0){
		if(close(child_to_parent[0]) < 0){
			std::cerr << "first child to parent close 1";
			exit(errno);
		}

		if(close(parent_to_child[1]) < 0){
			std::cerr << "parent to first child close 1";
                        exit(errno);
		}

		pid_t first_child_pid = getpid();

                if(write(child_to_parent[1], &first_child_pid, sizeof(first_child_pid)) < 0){
                         std::cerr << "first child write";
                         exit(errno);
                }

		pid_t rec_pid;

		if(read(parent_to_child[0], &rec_pid, sizeof(rec_pid)) < 0){
			std::cerr << "first child read";
			exit(errno);
		}

		std::cout << "recived PID " << rec_pid << "\nmy PID " << getpid() << std::endl;
		
		if(close(child_to_parent[1]) < 0){
                        std::cerr << "first child to parent close 2";
                        exit(errno);
                }

                if(close(parent_to_child[0]) < 0){
                        std::cerr << "parent to first child close 2";
                        exit(errno);
                }

		exit(0);

	}

	else{
		pid_t second_pid = fork();
		
		if(second_pid < 0){
                	std::cerr << "second fork";
                	exit(errno);
       	 	}

        	else if(second_pid == 0){
                	if(close(child_to_parent[1]) < 0){
                        	std::cerr << "second child to parent close 1";
                        	exit(errno);
                	}

                	if(close(parent_to_child[0]) < 0){
                        	std::cerr << "parent to second child close 1";
                        	exit(errno);
                	}

                	pid_t rec_pid;

                	if(read(child_to_parent[0], &rec_pid, sizeof(rec_pid)) < 0){
                        	std::cerr << "second child read";
                        	exit(errno);
                	}
                	std::cout << "recived PID " << rec_pid << "\nmy PID " << getpid() << std::endl;

                	pid_t second_child_pid = getpid();

                	if(write(parent_to_child[1], &second_child_pid, sizeof(second_child_pid)) < 0){
                        	std::cerr << "second child write";
                         	exit(errno);
               	 	}

                	if(close(child_to_parent[0]) < 0){
                        	std::cerr << "second child to parent close 2";
                        	exit(errno);
                	}

                	if(close(parent_to_child[1]) < 0){
                        	std::cerr << "parent to second child close 2";
                        	exit(errno);
                	}

			exit(0);

        	}

		else{
			if(close(child_to_parent[1]) < 0){
                                std::cerr << "child to parent close 1";
                                exit(errno);
                        }

                        if(close(parent_to_child[0]) < 0){
                                std::cerr << "parent to child close 1";
                                exit(errno);
                        }

 			if(close(child_to_parent[0]) < 0){
                                std::cerr << "child to parent close 2";
                                exit(errno);
                        }

                        if(close(parent_to_child[1]) < 0){
                                std::cerr << "parent to child close 2";
                                exit(errno);
                        }
			
			int stat1, stat2;
			if(waitpid(first_pid, &stat1, 0) < 0){
				std::cerr << "wait";
                                exit(errno);
                        }
			waitpid(second_pid, &stat2, 0){
                                std::cerr << "wait";
                                exit(errno);
                        }
		}	


   

	}

	return 0;
}

