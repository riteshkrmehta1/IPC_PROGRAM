/*******************************************************************************************
 *
 *  CONVERTING RAW AND YUV TO JPEG ,BMP ,PNG ,TIFF Image format ....
 *  
 ********************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<jpeglib.h>
#include<png.h>
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
/* Checking the input and output file format */
int check_file_format(char *filename)
{
	int i,j,k=0;
	char file_type[SIZE];
	for(i=0;filename[i];i++)
	{
		if(filename[i]=='.')
			break;
	}
	for(j=i+1;filename[j];j++)
		file_type[k++]=filename[j];
	file_type[k]='\0';
	//printf("%s\n",file);
	if(strcmp(file_type,"raw")==0)
		return RAW ;
	else if(strcmp(file_type,"yuv")==0)
		return YUV ;
	else if(strcmp(file_type,"bmp")==0)
		return BMP ;
	else if(strcmp(file_type,"jpg")==0)
		return JPEG ;
	else if(strcmp(file_type,"png")==0)
		return PNG ;
	else 
		return -1 ;
}
/* Converting YUV444 to the RGB24 image format */
unsigned char * yuv444_to_rgb24(int width ,int height , int size )
{
	int y,u,v,r,g,b;
	int c,pixel,gr=2;
	unsigned char *outputbuf= (char *)malloc(height*width*3*sizeof(char));
	for(pixel=0,c=0 ; pixel < size ; pixel=pixel+3 , c+=3)
	{
		//y = (int)buffer[pixel];
		y  = (int)buffer[pixel+0];
		u = (int)buffer[pixel+1];
		v  = (int)buffer[pixel+2];
		u -= 128;
		v -= 128;
		if(gr==2)
		{
			r  = y + 1.370705 * v;
			g  = y - 0.698001 * v - 0.337633 * u;
			b  = y + 1.732446 * u;
		}
		else if(gr==1)
		{
			r  = y; 
			g  = y;
			b  = y;
		}
		else
		{
			printf("invalidoption\n");
			return;
		}
		if(r<0)      r 	= 0;
		if(g<0)      g 	= 0;
		if(b<0)      b 	= 0;
		if(r>255)    r 	= 255;
		if(g>255)    g 	= 255;
		if(b>255)    b 	= 255;
		outputbuf[c+0] 	= (unsigned char)b;
		outputbuf[c+1] 	= (unsigned char)g;
		outputbuf[c+2] 	= (unsigned char)r;
	}
	return outputbuf;
}
/* Converting YUV422 to RGB24 format */
unsigned char * yuv422_to_rgb24(int width ,int height , int size )
{
	int y0,y1,u,v,r,g,b;
	int c,pixel,gr=2;
	unsigned char *outputbuf= (char *)malloc(height*width*3*sizeof(char));
	for(pixel=0,c=0 ; pixel < size ; pixel=pixel+4 , c+=6)
	{
		y0 = (int)buffer[pixel];
		u  = (int)buffer[pixel+1];
		y1 = (int)buffer[pixel+2];
		v  = (int)buffer[pixel+3];
		u -= 128;
		v -= 128;
		if(gr==2)
		{
			r  = y0 + 1.370705 * v;
			g  = y0 - 0.698001 * v - 0.337633 * u;
			b  = y0 + 1.732446 * u;
		}
		else if(gr==1)
		{
			r  = y0; 
			g  = y0;
			b  = y0;
		}
		else
		{
			printf("invalidoption\n");
			return;
		}
		if(r<0)      r 	= 0;
		if(g<0)      g 	= 0;
		if(b<0)      b 	= 0;
		if(r>255)    r 	= 255;
		if(g>255)    g 	= 255;
		if(b>255)    b 	= 255;
		outputbuf[c+0] 	= (unsigned char)b;
		outputbuf[c+1] 	= (unsigned char)g;
		outputbuf[c+2] 	= (unsigned char)r;
		if(gr==2)
		{
			r = y1 + 1.370705 * v;
			g = y1 - 0.698001 * v - 0.337633 * u;
			b = y1 + 1.732446 * u;
		}
		else if(gr==1)
		{
			r = y1; 
			g = y1;
			b = y1;
		}
		else
		{
			printf("invalidoption\n");
			return;
		}
		if(r<0)      r 	= 0;
		if(g<0)      g 	= 0;
		if(b<0)      b 	= 0;
		if(r>255)    r 	= 255;
		if(g>255)    g 	= 255;
		if(b>255)    b 	= 255;
		outputbuf[c+3] 	= (unsigned char)b;
		outputbuf[c+4] 	= (unsigned char)g;
		outputbuf[c+5] 	= (unsigned char)r;
	}
	return outputbuf;

}

/* Writting png file formate in the output file */
void write_png_file(char *filename , int image_width , int image_height , int image_format)
{

	FILE *Output_file = fopen(filename, "wb");
	if(!Output_file) abort();
	png_byte color_type;
	png_byte bit_depth;
	png_bytep *row_pointers;
	int y,x,i=0;

	color_type = BYTESPERPIXEL;
	bit_depth  = BITSPERPIXEL;

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) abort();

	png_infop info = png_create_info_struct(png);
	if (!info) abort();
	if (setjmp(png_jmpbuf(png))) abort();


	png_init_io(png, Output_file);

	// Output is 8bit depth, RGBA format.
	png_set_IHDR(
			png,
			info,
			image_width, image_height,
			8,
			PNG_COLOR_TYPE_RGB,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT
		    );

	if(bit_depth == 16)
		png_set_strip_16(png);

	if(color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if(png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	// These color_type don't have an alpha channel then fill it with 0xff.
	if(color_type == PNG_COLOR_TYPE_RGB ||
			color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if(color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);


	png_write_info(png, info);

	row_pointers = ( png_bytep* ) malloc( sizeof(png_bytep) * image_height);
	//printf("Png_get_rowbytes %d\n",png_get_rowbytes(png,info));

	for( y = 0; y < image_height; y++) {
		row_pointers[y] = ( png_byte* ) malloc( sizeof(png_byte) * image_width * color_type );
	}

	for(y=0;y< image_height ;y++)
	{
		for( x=0 ; x<(image_width*color_type) ; x++)
			row_pointers[y][x]=buffer[i++];
	}
	png_write_image(png, row_pointers);


	// To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
	// Use png_set_filler().
	//png_set_filler(png, 0, PNG_FILLER_AFTER);

	png_write_end(png, NULL);

	for(y = 0; y < image_height; y++) {
		free(row_pointers[y]);
	}
	free(row_pointers);

	if (png && info)
		png_destroy_write_struct(&png, &info);

	fclose(Output_file);
}

/* Writting the jpeg image in the output file */
int write_jpeg_file( char *filename, int image_width , int image_height ,int image_format )
{


	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	int bytes_per_pixel;
	int color_space ; //JCS_RGB;//JCS_UNKNOWN;//JCS_RGB; //JCS_RGB;*/   /*JCS_GRAYSCALE; for grayscale images */


	JSAMPROW row_pointer[1];
	bytes_per_pixel =BYTESPERPIXEL;
	color_space =JCS_RGB;


	FILE *outfile = fopen( filename, "wb" );
	if ( !outfile )
	{
		printf("Error opening output jpeg file %s\n!", filename );
		return -1;
	}
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);


	cinfo.image_width = image_width;
	cinfo.image_height = image_height;
	cinfo.input_components = bytes_per_pixel;
	cinfo.in_color_space = color_space;
	//      cinfo.data_precision = bits_per_pixel;
	cinfo.input_gamma = 1.00;
	jpeg_set_defaults( &cinfo );

	jpeg_start_compress( &cinfo, TRUE );

	while( cinfo.next_scanline < cinfo.image_height )
	{
		row_pointer[0] = &buffer[ cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
		jpeg_write_scanlines( &cinfo, row_pointer, 1 );
	}

	jpeg_finish_compress( &cinfo );
	jpeg_destroy_compress( &cinfo );
	fclose( outfile );

	return 1;
}


int Convert_to_BMP(char *filename ,unsigned long int imagesize ,int image_width ,int image_height ,int image_format)
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
	/* Checking input file  format means .raw or .yuv */
	input_file_format= check_file_format(argv[1]);
	printf("input_file_format %d\n",input_file_format);
	if(input_file_format < 1)
	{
		printf("Failed !!! Check Input file format\n");
		fclose(INPUT_file);
		free(buffer);
		return -1;
	}
	/* Checking output file format like jpg , bmp ,png ,tiff */ 
	output_file_format= check_file_format(argv[2]);
	printf("output_file_format %d\n",output_file_format);
	if(input_file_format < 1)
	{
		printf("Failed !!! Check Input file format\n");
		fclose(INPUT_file);
		free(buffer);
		return -1;
	}
	/* Reading data of input file */
	fread(buffer,size,sizeof(char),INPUT_file);
	/*If input  file is yuv422 format then converted to RGB24 format */
	if(input_file_format == YUV)
		buffer=yuv422_to_rgb24( width , height, size );
	/* For converting Input file to the bmp file format */
	if(output_file_format == BMP )
		value = Convert_to_BMP( argv[2] , size , width , height , input_file_format );

	/* For converting Input file to the jpeg file format */
	if(output_file_format == JPEG)
		write_jpeg_file( argv[2] ,width , height ,input_file_format );
	/* For converting Input file to the png file format */
	if(output_file_format == PNG)
		write_png_file(argv[2] ,width , height , input_file_format);

	fclose(INPUT_file);
	free(buffer);
print_time();

}
