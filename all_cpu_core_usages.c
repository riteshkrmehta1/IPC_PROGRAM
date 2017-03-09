#define _GNU_SOURCE
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sched.h>

pthread_t pthread_self()
{
	printf("HI RITU....\n");
}

void main(char argc , char **argv )
{

	int ret ;
	cpu_set_t mask;
	pthread_t First_thread=pthread_self();
//pthread_t Second_thread=Second_core_function();
//pthread_t Third_thread=Third_core_function();
//pthread_t Forth_thread=Forth_core_function();

	CPU_ZERO(&mask);  /* Clears set, so that it contains no CPUs.*/

	CPU_SET(0,&mask);

	ret=pthread_setaffinity_np(First_thread ,sizeof(cpu_set_t) , &mask); 

	if(!ret)
		perror("pthread_setaffinity_np");

while(1);
}


