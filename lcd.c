#include<stdio.h>
#include<wiringPi.h>
#include<lcd.h>

int main(void)
{
	int disp1;
	
	if(wiringPiSetupGpio()==-1) return 1;
	disp1 = lcdInit(2,16,4,17,4,6,13,19,26,0,0,0,0);
	
	lcdClear(disp1);
	
	lcdPosition(disp1,0,0);
	lcdPuts(disp1, "Hello World");
	
	lcdPosition(disp1,0,1);
	lcdPuts(disp1, "see you");
	
	delay(1000);
	
	return 0;
}
