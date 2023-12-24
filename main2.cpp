#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include <cmath>
using namespace std;

pthread_mutex_t m;
double a = 0;
double d = 1;

double f(double x){
    return exp(x);
}

void *count(void *p){
    int max = 100000;
    double *dp = (double *)p;
    double h = d/max;
    int x;

    for(int i=0; i<max; i++){
        x = *dp;
        pthread_mutex_lock(&m);
        a += (f(x) + f(x+h))*h/2;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(){
    pthread_t th1, th2, th3, th4;
    double d1 = 0, d2 = d, d3 = d*2, d4 = d*3;

    pthread_create(&th1, NULL, count, (void *)&d1);
    pthread_create(&th2, NULL, count, (void *)&d2);
    pthread_create(&th3, NULL, count, (void *)&d3);
    pthread_create(&th4, NULL, count, (void *)&d4);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    cout << a << endl;
    return 0;
}