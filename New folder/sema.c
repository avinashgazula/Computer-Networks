#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
sem_t s1,s2; 
int x=0, y=0;
void* p1(void* f){
	while(1){
		sem_wait(&s2);
		int temp = y;
		temp++;
		x=temp;
		printf("x is %d\n",x );
		sem_post(&s1);
	}
}
void* p2(void* f){
	while(1){
		sem_wait(&s1);
		int temp = x;
		temp++;
		y=temp;
		printf("y is %d\n",y );
		sem_post(&s2);
	}
}
int main(){
	sem_init(&s1,0,1);
	sem_init(&s2,1,1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,p1,NULL);
	pthread_create(&t2,NULL,p2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}