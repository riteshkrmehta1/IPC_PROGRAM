#include<graphics.h> 
int main()
{
	int gd = DETECT,gm,i= 50,j=50,radius=50,k=50;
int gdriver,gmode;
  int dppoints[14] = {200, 150, 300, 250, 400, 150, 425, 350, 300, 275, 150, 350, 200, 150};
  int fppoints[14] = {500, 150, 600, 250, 700, 150, 725, 350, 600, 275, 450, 350, 500, 150};
	
  gdriver = VGA;gmode=VGAMAX;
  initgraph(&gdriver,&gmode,"");
	for ( i=50,j=50,k=50 ; i<750 ;i++,j++,k++)
	{
		pieslice(i, 50, 0, 360, 50);
		arc(i,50,0,360,50);
		setcolor(BLUE);
		pieslice(j, 150, 0, 360, 50);
		arc(j,50,0,360,50);
		setcolor(WHITE);
		pieslice(k, 250, 0, 360, 50);
		arc(k,50,0,360,50);
		setcolor(RED);
		delay(5);
		cleardevice();



	}
	/*bar(left + 300, top, right + 300, bottom);
	line(left - 10, top + 150, left + 410, top + 150);
	ellipse(x, y + 200, 0, 360, 100, 50);
	outtextxy(left + 100, top + 325, "C Graphics Program");
	setfontcolor(RED);
	delay(1000);
	initgraph(&gd,&gm,NULL);
	//cleardevice();
*/
	closegraph();
	return 0;
}
