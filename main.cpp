#include<stdio.h>
#include<iostream>
#include<pthread.h>
using namespace std;

pthread_mutex_t m;

void *count(void *p){
    int *ap = (int *)p;
    for(int i=0; i<100000; i++){
        pthread_mutex_lock(&m);
        *ap += 1;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(){
    int a = 0;
    pthread_t th1, th2, th3, th4;

    pthread_create(&th1, NULL, count, (void *)&a);
    pthread_create(&th2, NULL, count, (void *)&a);
    pthread_create(&th3, NULL, count, (void *)&a);
    pthread_create(&th4, NULL, count, (void *)&a);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    cout << a << endl;
    return 0;
}