
#define _GNU_SOURCE
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sched.h>
//#include<sys/time>
#include<time.h>

struct Image_data
{
int width;
int height;
char *buffer;

}image;

void * cpu0()
{
	printf("HI RITU....\n");
}
void * cpu1()
{

}
void * cpu2()
{

}

void * cpu3()
{

}
void print_time ()
{
  struct timeval tv;
  struct tm* ptm;
  char time_string[40];
  long milliseconds;

  /* Obtain the time of day, and convert it to a tm struct.  */
  gettimeofday (&tv, NULL);
  ptm = localtime (&tv.tv_sec);
  /* Format the date and time, down to a single second.  */
  strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
  /* Compute milliseconds from microseconds.  */
  milliseconds = tv.tv_usec / 1000;
  /* Print the formatted time, in seconds, followed by a decimal point
     and the milliseconds.  */
  printf ("%s.%03ld\n", time_string, milliseconds);
}


void main(char argc , char **argv )
{

	int ret ;
	cpu_set_t mask1,mask2,mask3,mask4;
	pthread_t First_thread;
	pthread_t Second_thread;
	pthread_t Third_thread;
	pthread_t Forth_thread;

	print_time();

	CPU_ZERO(&mask1);  /* Clears set, so that it contains no CPUs.*/
	CPU_ZERO(&mask2);
	CPU_ZERO(&mask3);
	CPU_ZERO(&mask4);

	/* Setting Perticular cpus */
	CPU_SET(0,&mask1);
	CPU_SET(1,&mask2);
	CPU_SET(2,&mask3);
	CPU_SET(3,&mask4);

	ret=pthread_create(&First_thread ,NULL,cpu0 ,NULL);
	if(ret)
		perror("pthread_create");
	ret=pthread_create(&Second_thread ,NULL,cpu1 ,NULL);
	if(ret)
		perror("pthread_create");
	ret=pthread_create(&Third_thread ,NULL,cpu2 ,NULL);
	if(ret)
		perror("pthread_create");
	ret=pthread_create(&Forth_thread ,NULL,cpu3 ,NULL);
	if(ret)
		perror("pthread_create");

	ret=pthread_setaffinity_np(First_thread ,sizeof(cpu_set_t) , &mask1); 
	if(ret)
		perror("pthread_setaffinity_np");

	ret=pthread_setaffinity_np(Second_thread ,sizeof(cpu_set_t) , &mask2);
	if(ret)
		perror("pthread_setaffinity_np");
	ret=pthread_setaffinity_np(Third_thread ,sizeof(cpu_set_t) , &mask3);
	if(ret)
		perror("pthread_setaffinity_np");
	ret=pthread_setaffinity_np(Forth_thread ,sizeof(cpu_set_t) , &mask4);
	if(ret)
		perror("pthread_setaffinity_np");

//while(1);
sleep(5);
print_time();

}


