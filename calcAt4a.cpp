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
    double h = 0.000000002;
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
    pthread_t th0, th1, th2, th3;

    struct section sec0 = {0, 1};
    struct section sec1 = {1, 2};
    struct section sec2 = {2, 3};
    struct section sec3 = {3, 4};

    pthread_create(&th0, NULL, count, (void *)&sec0);
    pthread_create(&th1, NULL, count, (void *)&sec1);
    pthread_create(&th2, NULL, count, (void *)&sec2);
    pthread_create(&th3, NULL, count, (void *)&sec3);
    pthread_join(th0, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    struct timeval t1;
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);

    printf("%.6f time:%d.%06d\n", sum, t1.tv_sec, t1.tv_usec);
    return 0;
}
