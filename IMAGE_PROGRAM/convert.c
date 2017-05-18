/*******************************************************************************************
 *
 *  CONVERTING RAW AND YUV TO JPEG ,BMP ,PNG ,TIFF Image format ....
 *  
 ********************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define BITSPERPIXEL 24
#define  BYTESPERPIXEL 3
#define SIZE 10
#define RAW 1
#define YUV 2
#define BMP 3
#define JPEG 4
#define PNG 5
#pragma pack(push,1)
/* Bmp header structure */
typedef struct
{
	unsigned short int 	type;                 			// Magic identifier            
	unsigned int 		filesize;                       	// File size in bytes          
	unsigned short int 	reserved1, reserved2;
	unsigned int 		offset;                     		// Offset to image data, bytes 
	unsigned int 		headersize;               		// Header size in bytes      
	int 			width,height;                		// Width and height of image 
	unsigned short int 	planes;       				// Number of colour planes   
	unsigned short int 	bits;         				// Bits per pixel            
	unsigned int 		compression;        			// Compression type          
	unsigned int 		imagesize;          			// Image size in bytes       
	int 			xresolution,yresolution;     	        // Pixels per meter          
	unsigned int 		no_of_colours;           		// Number of colours         
	unsigned int 		importantcolours;   			// Important colours         
}HEADER;
#pragma pack(pop)
unsigned char *buffer;

HEADER Bmp_header;

int Convert_to_BMP(char *filename ,unsigned long int imagesize ,int image_width ,int image_height )
{
	FILE *OUTPUT_file;
	char *bmp_buffer;
	int pixel;
	OUTPUT_file=fopen(filename,"wb");
	if(OUTPUT_file==NULL)
	{
		printf("file is not opened sucessfully\n");

		return -1;
	}

	/* 54 bytes of bmp header information */
	Bmp_header.type	 		= 0x4d42;
	Bmp_header.reserved1 		= 0;
	Bmp_header.reserved2 		= 0;
	Bmp_header.offset	 	= sizeof(HEADER);
	Bmp_header.headersize	 	= 40;
	Bmp_header.planes	 	= 1;
	Bmp_header.compression 		= 0;
	Bmp_header.no_of_colours	= 0;
	Bmp_header.importantcolours	= 0;
	Bmp_header.xresolution		= 0;
	Bmp_header.yresolution		= 0;
	Bmp_header.bits			= BITSPERPIXEL;
	Bmp_header.width		= image_width;
	Bmp_header.height		= image_height;
	Bmp_header.imagesize 		=  (image_width * image_height * BYTESPERPIXEL);
	Bmp_header.filesize		= Bmp_header.imagesize + sizeof(HEADER);

	bmp_buffer=(char *) malloc(imagesize *sizeof(char));
	if( bmp_buffer == NULL)
	{
		printf("sufficient memory not available\n");
		fclose(OUTPUT_file);
		return -1;
	}
	printf(" INPUT Image size %ld\n",imagesize);
	printf("BMP IMAGE size %d\n",Bmp_header.imagesize);
	printf("Bmp Filesize %d\n",Bmp_header.filesize);
	for(pixel=0 ;pixel < imagesize ;pixel=pixel+3)
	{
		bmp_buffer[pixel]=buffer[pixel+2];
		bmp_buffer[pixel+1]=buffer[pixel+1];
		bmp_buffer[pixel+2]=buffer[pixel];

	}	
	fwrite(&Bmp_header,sizeof(HEADER),sizeof(char),OUTPUT_file);
	fwrite(bmp_buffer, image_width * image_height * BYTESPERPIXEL, sizeof(char),OUTPUT_file);

	free(bmp_buffer);
	fclose(OUTPUT_file);
	return 1;
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


int main(char argc ,char *argv[] )
{

	unsigned long int width,height,size;
	int input_file_format,value,output_file_format;
	//	char *buffer;
	FILE *INPUT_file ;

	if(argc < 2)
	{
		printf("Usage: convert_RGB_2_BMP  [I/P RAW FILE]  [O/P BMP FILE] \n");
		return 1;
	}
	

	INPUT_file=fopen(argv[1] ,"rb");
	if(INPUT_file==NULL)
	{
		printf("file is not opened sucessfully\n");
		return 1;
	}

	printf("Enter the width and height of input IMAGE :WIDTH X HEIGHT\n");
	scanf("%ld%ld",&width,&height);

	print_time();
	fseek(INPUT_file,0,SEEK_END);
	size=ftell(INPUT_file);
	rewind(INPUT_file);
	printf("size of RAW IMAGE %ld\n",size);

	buffer=(char *)malloc(sizeof(char)*(size));
	if(buffer==NULL)
	{
		printf("Sufficient memory not available\n");
		fclose(INPUT_file);
		return -1;
	}

	/* Reading data of input file */
	fread(buffer,size,sizeof(char),INPUT_file);

	/* For converting Input file to the bmp file format */
	if(output_file_format == BMP )
		value = Convert_to_BMP( argv[2] , size , width , height );


	fclose(INPUT_file);
	free(buffer);
print_time();

}
