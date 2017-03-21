
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sched.h>
#include<time.h>

#define BITSPERPIXEL 24
#define  BYTESPERPIXEL 3
#pragma pack(push,1)

/* Bmp header structure */
typedef struct
{
	unsigned short int      type;                                   // Magic identifier            
	unsigned int            filesize;                               // File size in bytes          
	unsigned short int      reserved1, reserved2;
	unsigned int            offset;                                 // Offset to image data, bytes 
	unsigned int            headersize;                             // Header size in bytes      
	int                     width,height;                           // Width and height of image 
	unsigned short int      planes;                                 // Number of colour planes   
	unsigned short int      bits;                                   // Bits per pixel            
	unsigned int            compression;                            // Compression type          
	unsigned int            imagesize;                              // Image size in bytes       
	int                     xresolution,yresolution;                // Pixels per meter          
	unsigned int            no_of_colours;                          // Number of colours         
	unsigned int            importantcolours;                       // Important colours         
}HEADER;
#pragma pack(pop)
unsigned char *input_buffer ,*bmp_buffer;
int q ,r,i,j,k,l;

HEADER Bmp_header;

void * cpu0()
{

	int pixel ;

	for(pixel=0 ;pixel < i ;pixel=pixel+3)
	{
		bmp_buffer[pixel]=input_buffer[pixel+2];
		bmp_buffer[pixel+1]=input_buffer[pixel+1];
		bmp_buffer[pixel+2]=input_buffer[pixel];

	}
}
void * cpu1()
{
	int pixel ;

	for(pixel=i ;pixel < j ;pixel=pixel+3)
	{
		bmp_buffer[pixel]=input_buffer[pixel+2];
		bmp_buffer[pixel+1]=input_buffer[pixel+1];
		bmp_buffer[pixel+2]=input_buffer[pixel];

	}
}
void * cpu2()
{
	int pixel ;

	for(pixel=j ;pixel < k ;pixel=pixel+3)
	{
		bmp_buffer[pixel]=input_buffer[pixel+2];
		bmp_buffer[pixel+1]=input_buffer[pixel+1];
		bmp_buffer[pixel+2]=input_buffer[pixel];

	}
}

void * cpu3()
{
	int pixel ;

	for(pixel=k ;pixel < l ;pixel=pixel+3)
	{
		bmp_buffer[pixel]=input_buffer[pixel+2];
		bmp_buffer[pixel+1]=input_buffer[pixel+1];
		bmp_buffer[pixel+2]=input_buffer[pixel];

	}
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


int main(char argc , char **argv )
{

	int ret ,width , height , size  ;
	cpu_set_t mask1,mask2,mask3,mask4;
	pthread_t First_thread , Second_thread , Third_thread , Forth_thread;
        FILE *input ,*output ;
	 
	if(argc < 2)
        {
                printf("Usage: convert_RGB_2_BMP  [I/P RAW FILE]  [O/P BMP FILE] \n");
                return -1;
        }
	
	input=fopen(argv[1] ,"rb");
        if(input==NULL)
        {
                printf("file is not opened sucessfully\n");
                return -1;
        }
	
	printf("Enter the width and height of input IMAGE :WIDTH X HEIGHT\n");
        scanf("%d%d",&width,&height);

	/* Printing the current time */
	print_time();

	fseek(input,0,SEEK_END);
        size=ftell(input);
        rewind(input);
        printf("size of RAW IMAGE %d\n",size);
	
	input_buffer=(char *)malloc(sizeof(char)*(size));
        if(input_buffer==NULL)
        {
		perror("malloc");
                printf("Sufficient memory not available\n");
                fclose(input);
                return -1;
        }
	
	/* Reading data of input file */
        fread(input_buffer,size,sizeof(char),input);

	output=fopen(argv[2],"wb");
        if(output==NULL)
        {
		perror("fopen");
                printf("file is not opened sucessfully\n");
		fclose(input);
		free(input_buffer);
                return -1;
        }
	
	 /* 54 bytes of bmp header information */
        Bmp_header.type                 = 0x4d42;
        Bmp_header.reserved1            = 0;
        Bmp_header.reserved2            = 0;
        Bmp_header.offset               = sizeof(HEADER);
        Bmp_header.headersize           = 40;
        Bmp_header.planes               = 1;
        Bmp_header.compression          = 0;
        Bmp_header.no_of_colours        = 0;
        Bmp_header.importantcolours     = 0;
        Bmp_header.xresolution          = 0;
        Bmp_header.yresolution          = 0;
        Bmp_header.bits                 = BITSPERPIXEL;
        Bmp_header.width                = width;
        Bmp_header.height               = height;
        Bmp_header.imagesize            =  (width * height * BYTESPERPIXEL);
        Bmp_header.filesize             = Bmp_header.imagesize + sizeof(HEADER);

	bmp_buffer=(char *) malloc( size *sizeof(char));
        if( bmp_buffer == NULL)
        {
                printf("sufficient memory not available\n");
                fclose(input);
		fclose(output);
		free(input_buffer);
                return -1;
        }
       
	printf("BMP IMAGE size %d\n",Bmp_header.imagesize);
        printf("Bmp Filesize %d\n",Bmp_header.filesize);

	q=size/4;
	r=size%4;
	i=q;
	j=q+i;
	k=q+j;
 	l=q+k+r;

	CPU_ZERO(&mask1);  /* Clears set, so that it contains no CPUs.*/
	CPU_ZERO(&mask2);
	CPU_ZERO(&mask3);
	CPU_ZERO(&mask4);

	/* Setting Perticular cpus */
	CPU_SET(0,&mask1);
	CPU_SET(1,&mask2);
	CPU_SET(2,&mask3);
	CPU_SET(3,&mask4);

  
	/* four Thread creation */ 
	if( (pthread_create(&First_thread ,NULL,cpu0 ,NULL))  ||
			(pthread_create(&Second_thread ,NULL,cpu1 ,NULL)) ||
			(pthread_create(&Third_thread ,NULL,cpu2 ,NULL))  ||
			(pthread_create(&Forth_thread ,NULL,cpu3 ,NULL))  )
	{
		perror("pthread_create");
		printf("Unable to Create threads \n");
		return -1 ;
	}
	/* setting cpu for each thread */

	if ( (pthread_setaffinity_np(First_thread ,sizeof(cpu_set_t) , &mask1))   ||
			(pthread_setaffinity_np(Second_thread ,sizeof(cpu_set_t) , &mask2)) ||
			(pthread_setaffinity_np(Third_thread ,sizeof(cpu_set_t) , &mask3))  ||
			(pthread_setaffinity_np(Forth_thread ,sizeof(cpu_set_t) , &mask4)) )
	{
		perror("pthread_setaffinity_np");
		printf("Unable to provided separate cpus for separate threads \n");
		return -1;
	}

//	if(
 (pthread_tryjoin_np(First_thread, NULL))  ;// ||
			(pthread_tryjoin_np(Second_thread, NULL)) ;//||
			(pthread_tryjoin_np(Third_thread, NULL)) ;// ||
			(pthread_tryjoin_np(Forth_thread, NULL)); // )
/*	{
		perror("pthread_tryjoin_np");
		printf("Unable to join to the threads \n");
		return -1;
	}
*/
/*
	if( (pthread_join(First_thread, NULL))  ||
			(pthread_join(Second_thread, NULL)) ||
			(pthread_join(Third_thread, NULL)) ||
			(pthread_join(Forth_thread, NULL))  )
	{
		perror("pthread_tryjoin_np");
		printf("Unable to join to the threads \n");
		return -1;
	}
*/	
	fwrite(&Bmp_header,sizeof(HEADER),sizeof(char),output);
        fwrite(bmp_buffer, width * height * BYTESPERPIXEL, sizeof(char),output);



	free(bmp_buffer);
	free(input_buffer);
        fclose(input);
	fclose(output);
	print_time();

}


