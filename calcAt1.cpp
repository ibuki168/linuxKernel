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

pthread_mutex_t m;
double sum = 0;

double f(double x){
    return log(x);
}

void *count(void *p){
    struct section *sec = (struct section *)p;
    
    double x = sec->start;
    double end = sec->end;
    double h = 0.00000001;
    double d;

    while(x<end){
        d = f(x+h/2)*h;
        pthread_mutex_lock(&m);
        sum += d;
        pthread_mutex_unlock(&m);
        x += h;
    }
    return NULL;
}

int main(){
    gettimeofday(&t0, NULL);
    pthread_t th0, th1;

    struct section sec0 = {0, 4};

    pthread_create(&th0, NULL, count, (void *)&sec0);
    pthread_join(th0, NULL);

    struct timeval t1;
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);

    printf("%.6f time:%d.%06d\n", sum, t1.tv_sec, t1.tv_usec);
    return 0;
}