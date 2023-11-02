#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <cstring>

namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

using namespace Color;

int main(){
	char buf[1000];
	char cwd[256];
	char* gdir;
	char* dir;
	char* to;
	char hostname[1024];

	if(getlogin() == NULL){
		std::cerr << "login";
                exit(errno);
	}
	std::string username = getlogin();

       	if(gethostname(hostname, sizeof(hostname)) < 0){
		std::cerr << "host";
		exit(errno);
	}
	
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);
    	Color::Modifier def(Color::FG_DEFAULT);
	
	while(true){
    		if (getcwd(cwd, sizeof(cwd)) == NULL){
			std::cerr << "getcwd";
			exit(errno);

		}
    		else{	
			std::cout << green << username << "@" << hostname << def << ":" << blue << "~" << cwd << def << "$ ";
		}
	
		
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
