#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <cstring>

int main(){
	char buf[1000];
	char cwd[256];
	char* gdir;
	char* dir;
	char* to;
	bool in = false;
	while(true){
    		if (getcwd(cwd, sizeof(cwd)) == NULL)
      			perror("getcwd() error");
    		else	
			std::cout << "myShell:" << cwd << "$ ";
		
		std::string args;
		std::getline(std::cin, args);

		if(args == "exit"){
			std::cout << "exit" << std::endl;
			break;
		}

		std::vector<char*> coms;
		char* str = strtok(const_cast<char*>(args.c_str()), " ");

		while(str != nullptr){
			coms.push_back(str);
			str = strtok(nullptr, " ");
		}

		coms.push_back(nullptr);
		
		
                if(!strcmp(coms[0], "cd")){
                        gdir = getcwd(buf, sizeof(buf));
			dir = strcat(gdir, "/");
			to = strcat(dir, coms[1]);

			chdir(to);
			continue;
                }

		pid_t pid = fork();

		if(pid < 0){
			std::cerr << "fork" << std::endl;
			exit(errno);
		}

		if(pid == 0){
			if(execvp(coms[0], coms.data()) < 0){
				std::cout << coms[0] << ": command not found" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		
		else{
			int status;
		
			if(wait(&status) < 0){
				std::cerr << "wait" << std::endl;
				exit(errno);
			}

			if(WIFEXITED(status)){
				std::cout << "exit code: " << WEXITSTATUS(status) << std::endl;
			}
		}
	
	
	}
}
