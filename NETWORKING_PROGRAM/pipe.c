
/********** DATE - 05/01/2017 ***************************
Creating pipe and writting and reading from the pipe */
#include<stdio.h>
#include<unistd.h>
#include<string.h>
main()
{
	char buf[20];
	int fd[2];
	if(pipe(fd)<0)
	{
		perror("pipe");
		return;
	}
	if(fork()==0)
	{
		int i;
		char b[10];
		read(fd[0],&b,sizeof(b));
		printf("%s\n",b);
		for(i=0;b[i];i++)
			b[i]=b[i]-32;
		write(fd[1],&b,strlen(b)+1);
		printf("in child process..\n");

	}
	else
	{
		char a[10]="ritesh";
		write(fd[1],&a,strlen(a)+1);
		sleep(1);
		read(fd[0],&a,sizeof(a));
		printf("%s\n",a);
		printf("parent process..\n");
	}
	close(fd[0]);
	close(fd[1]);

}

