#include<stdio.h>
#include<graphics.h> 
int main()
{
	int gd = DETECT,gm,i= 50,j=50,radius=50,color=1;
	int gdriver,gmode;
	int dppoints[14] = {200, 150, 300, 250, 400, 150, 425, 350, 300, 275, 150, 350, 200, 150};
	int fppoints[14] = {500, 150, 600, 250, 700, 150, 725, 350, 600, 275, 450, 350, 500, 150};

	gdriver = VGA;gmode=VGAMAX;
	initgraph(&gdriver,&gmode,"");
	int sa=0,se=45,start=1,color_count=1;
	printf("libgraph shapes and colors demo\n");
	while(1)
	{
		if(color_count==9)
			color_count=1;
		color=color_count++;

		for ( i=0 ; i<4 ; i++)
		{
			pieslice( 300 , 300 , sa, se ,200);
			sa=se+1;
			se=se+90;
			setcolor(color++);
			if(color == 9)
				color=1;
		}
		sa=0;
		se=90;

		/*
		   if(start<=8)
		   color=start;	
		   else
		   {
		   start=0;
		   color=1;
		   }
		   start++;
		 */

		delay(10);
		cleardevice();
	}
	closegraph();
	return 0;
}
