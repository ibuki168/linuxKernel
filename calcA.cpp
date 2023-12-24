#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include <cmath>
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

    count((void *)&sec0);

    struct timeval t1;
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);

    printf("%.6f time:%d.%06d\n", sum, t1.tv_sec, t1.tv_usec);
    return 0;
}