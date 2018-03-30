#include <stdio.h>
#include <graphics.h>

int main() {
	int gd = DETECT, gm;
	int i, maxx, midy,j,x,y,car_color=3;

	/* initialize graphic mode */
	initgraph(&gd, &gm, "X:\\TC\\BGI");
	/* maximum pixel in horizontal axis */
	maxx = getmaxx();
	/* mid pixel in vertical axis */
	midy = getmaxy()/2;
	while(1)
	{
		for (i=0; i < maxx-150; i=i+5) {
			/* clears screen */
			cleardevice();

			/* draw a white road */
			setcolor(WHITE);
			line(0, midy + 37, maxx, midy + 37);

			/* Draw Car */
			setcolor(car_color);
			//setfillstyle(SOLID_FILL, RED);

			line(i, midy + 23, i, midy);
			line(i, midy, 40 + i, midy - 20);
			line(40 + i, midy - 20, 80 + i, midy - 20);
			line(80 + i, midy - 20, 100 + i, midy);
			line(100 + i, midy, 120 + i, midy);
			line(120 + i, midy, 120 + i, midy + 23);
			line(0 + i, midy + 23, 18 + i, midy + 23);
			arc(30 + i, midy + 23, 0, 180, 12);
			line(42 + i, midy + 23, 78 + i, midy + 23);
			arc(90 + i, midy + 23, 0, 180, 12);
			line(102 + i, midy + 23, 120 + i, midy + 23);
			line(28 + i, midy, 43 + i, midy - 15);
			line(43 + i, midy - 15, 57 + i, midy - 15);
			line(57 + i, midy - 15, 57 + i, midy);
			line(57 + i, midy, 28 + i, midy);
			line(62 + i, midy - 15, 77 + i, midy - 15);
			line(77 + i, midy - 15, 92 + i, midy);
			line(92 + i, midy, 62 + i, midy);
			line(62 + i, midy, 62 + i, midy - 15);
			floodfill(5 + i, midy + 22, YELLOW);
			setcolor(BLUE);
			//setfillstyle(SOLID_FILL, DARKGRAY);
			/*  Draw Wheels */
			circle(30 + i, midy + 25, 9);
			circle(90 + i, midy + 25, 9);
			floodfill(30 + i, midy + 25, BLUE);
			floodfill(90 + i, midy + 25, BLUE);
			/* Add delay of 0.1 milli seconds */

//			for(j=0; j<=500; j++) {
//				x=rand()%getmaxx();
//				y=rand()%getmaxy();
//				putpixel(x,y,15);



//			}

			delay(75);
		}
		car_color++;
		if(car_color==8)
			car_color=3;
	}
	//   getch();
	closegraph();
	return 0;
}
