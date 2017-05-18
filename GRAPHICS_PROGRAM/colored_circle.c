#include<stdio.h>
#include<graphics.h> 
int main()
{
	int gd = DETECT,gm,i= 50,j=50,radius=50,color=1;
	int gdriver,gmode;
//	int dppoints[14] = {200, 150, 300, 250, 400, 150, 425, 350, 300, 275, 150, 350, 200, 150};
//	int fppoints[14] = {500, 150, 600, 250, 700, 150, 725, 350, 600, 275, 450, 350, 500, 150};

	gdriver = VGA;gmode=VGAMAX;
	initgraph(&gdriver,&gmode,"");
	int sa=0,se=45,start=1;
  printf("libgraph shapes and colors demo\n");
	while(1)
	{

		for ( i=0 ; i<8 ; i++)
		{
			pieslice( 300 , 300 , sa, se ,200);
			sa=se+1;
			se=se+45;
			setcolor(color++);

		}
		sa=0;
		se=45;
		if(start<=8)
			color=start;	
		else
		{
			start=1;
			color=1;
		}
		start++;
		delay(100);
		cleardevice();


	}
	closegraph();
	return 0;
}
