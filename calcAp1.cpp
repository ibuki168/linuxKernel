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
    struct section sec0 = {0, 4};

    int pp[2];
    pipe(pp);
    char buf[32];

    pid_t pid = fork();

    if(pid == 0){
        close(pp[0]);
        count((void *)&sec0);
        sprintf(buf, "%10.8f", sum);
        write(pp[1], buf, strlen(buf) + 1);
        close(pp[1]);
        exit(0);
    }

    close(pp[1]);
    read(pp[0], buf, 32);
    close(pp[0]);
    double dsum;
    sscanf(buf, "%lf", &dsum);
    sum += dsum;

    struct timeval t1;
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);

    printf("%.6f time:%d.%06d\n", sum, t1.tv_sec, t1.tv_usec);
    return 0;
}