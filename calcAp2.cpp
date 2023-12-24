#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include <cmath>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

struct section{
    double start;
    double end;
};

struct timeval t0;

double sum = 0;

double f(double x){
    return log(x);
}

void count(void *p){
    struct section *sec = (struct section *)p;
    
    double x = sec->start;
    double end = sec->end;
    double h = 0.00000001;
    double d;

    while(x<end){
        d = f(x+h/2)*h;
        sum += d;
        x += h;
    }
}

int main(){
    gettimeofday(&t0, NULL);
    struct section sec0 = {0, 2};

    int ps = 2;
    int pp[ps][2];
    char buf[32];
    pid_t pid[ps];

    for(int i=0; i<ps; i++){
        pipe(pp[i]);
        pid[i] = fork();
        if(pid[i] == 0){
            close(pp[i][0]);
            count((void *)&sec0);
            sprintf(buf, "%10.8f", sum);
            write(pp[i][1], buf, strlen(buf) + 1);
            close(pp[i][1]);
            exit(0);
        }
        sec0.start += 2;
        sec0.end += 2;
    }

    for(int i=0; i<ps; i++){
        double dsum;
        FILE *str = fdopen(pp[i][0], "r");
        close(pp[i][1]);

        waitpid(pid[i], NULL, 0);

        fgets(buf, 32, str);
        sscanf(buf, "%lf", &dsum);
        sum += dsum;
        fclose(str);
        close(pp[i][0]);
    }

    struct timeval t1;
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);

    printf("%.6f time:%d.%06d\n", sum, t1.tv_sec, t1.tv_usec);
    return 0;
}