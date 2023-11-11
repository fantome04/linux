#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <algorithm>
#include <fcntl.h>
#include <cstdlib>

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

	std::string args;

	while(true){
		if(args.empty()){
    			if (getcwd(cwd, sizeof(cwd)) == NULL){
				std::cerr << "getcwd";
				exit(errno);

			}
    			else{	
				std::cout << green << username << "@" << hostname << def << ":" << blue << "~" << cwd << def << "$ ";
			}
	
			std::getline(std::cin, args);
		}

		if(args == "exit"){
			std::cout << "exit" << std::endl;
			break;
		}

		std::vector<char*> coms;
		char* str = strtok(const_cast<char*>(args.c_str()), " ");

		std::string b = " ";
        	while (str != nullptr)
        	{
            		coms.push_back(str);
            		if(!(strcmp(coms.back(), "&&")))
            		{
                		coms.pop_back();
                		b = "&&";
                		break;
            		}
            		else if(!(strcmp(coms.back(), "||")))
            		{
                		coms.pop_back();
                		b = "||";
                		break;
            		}

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

		std::vector<char*> temp = coms;

		temp.pop_back();

		auto arrow = std::find_if(temp.begin(), temp.end(), [](const char* str){return strcmp(str, ">") == 0;});

		auto double_arrow = std::find_if(temp.begin(), temp.end(), [](const char* str){return strcmp(str, ">>") == 0;});

		if(pid == 0){
			int fd = 0;

			if(temp.size() > 2 && (arrow != temp.end() || double_arrow != temp.end())){
				if(arrow != temp.end()){
					fd = open(*(arrow + 1), O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    			temp.erase(arrow, temp.end());
				}		
				else{
					fd = open(*(double_arrow + 1), O_WRONLY | O_CREAT | O_APPEND, 0666);
                    			temp.erase(double_arrow, temp.end());
				}
			}

			if (fd == -1){
                		std::cerr << "open" << std::endl;
                		exit(errno);
            		}

            		int copied = dup(1);

            		if (copied == -1){
                		std::cerr << "dup" << std::endl;
                		exit(errno);
            		}

            		if (dup2(fd, 1) == -1){
                		std::cerr << "dup2" << std::endl;
                		exit(errno);
            		}
            		close(fd);
			

            		temp.push_back(nullptr);

			if(execvp(temp[0], temp.data()) < 0){
				std::cout << temp[0] << ": command not found" << std::endl;
				exit(EXIT_FAILURE);
			}
			
			if (dup2(copied, 1) == -1)
            		{
               	 		std::cerr << "dup2" << std::endl;
                		exit(errno);
            		}
            		close(copied);
		
		}
		
		else{
			int status;
		
			if(wait(&status) < 0){
				std::cerr << "wait" << std::endl;
				exit(errno);
			}

			if(WIFEXITED(status)){
				std::cout << "exit code: " << WEXITSTATUS(status) << std::endl;
			

				if(WEXITSTATUS(status) != 0)
                		{	
                    			if(!strcmp(b.c_str(), "&&"))
                        			args.clear();
                		}
                		else
               	 		{
                    			if(!strcmp(b.c_str(), "||"))
                        			args.clear();
                		}
			}
		}
		if(!strcmp(b.c_str(), " ")){
            		args.clear();
		}
        	else
        	{
            		auto a = args.find_first_of(b);
            		std::string tmp = "";
            		for (int i = a + 3; i < args.size(); ++i) {
                		tmp += args[i];
            		}
            		args = tmp;
        	}
	}

	return 0;
}
