#include <iostream>
#include <vector>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>

struct t_data{
    int n1;
    int n2;
    std::string op;
    std::string f_out;
};

void* performOp(void* args) {
    t_data* t = static_cast<t_data*>(args);
    int result;
    if(t->op == "s") {
        result = t->n1 + t->n2;
    }

    else if(t->op == "m") {
        result = t->n1 * t->n2;
    }

    else if(t->op == "ss") {
        result = t->n1 * t->n1 + t->n2 * t->n2;
    }

    else {
        std::cerr << "wrong operation";
        exit(errno);
    }

    int fd = open(t->f_out.c_str(),O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if(fd < 0) {
        std::cerr << "open";
        exit(errno);
    }

    std::string output = std::to_string(t->n1) + " " + t->op + " " + std::to_string(t->n2) + " = " + std::to_string(result);
    if(write(fd, output.c_str(), output.length()) < 0) {
        std::cerr << "write";
        exit(errno);
    }

    if(close(fd) < 0){
        std::cerr << "close";
        exit(errno);
    }

    return nullptr;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<pthread_t> threads(n);
    std::vector<t_data> oper;

    for(int i = 0; i < n; ++i){
        t_data t;
        std::cin >> t.n1 >> t.n2 >> t.op;
        t.f_out = "out_" + std::to_string(i+1);
        oper.push_back(t);
    }

    for(int i = 0; i < n; ++i){
        if(pthread_create(&threads[i], nullptr, performOp, &oper[i]) != 0) {
            std::cerr<< "create";
            exit(errno);
        }
    }

    for (int i = 0; i < n; ++i){
        std::cout << oper[i].f_out << std::endl;
    }

    for (int i = 0; i < n; ++i) {
        if(pthread_join(threads[i], nullptr) != 0){
            std::cerr<< "join";
            exit(errno);
        }
    }
    return 0;
}



