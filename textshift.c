#include<stdio.h>
#include<wiringPi.h>
#include<lcd.h>

int main(void){
	int disp1,i,j;
	char wd[14] = "Sungkyul UNIV.";
	char tmp;
	if(wiringPiSetupGpio()==-1) return 1;
	disp1 = lcdInit(2,16,4,17,4,6,13,19,26,0,0,0,0);
	
	
	
	lcdPosition(disp1,0,0);
while(1){
	for(i=0;i<14;i++){
	
	if(i==0){
		tmp = wd[0];
		wd[i] = wd[i+1];
	}

	if (i==13)
		wd[13] = tmp;
		
	else
		wd[i] = wd[i+1];
}
	lcdPosition(disp1,0,1);
	lcdPuts(disp1, wd);
	lcdPosition(disp1,0,0);
	lcdPuts(disp1, wd+1);
	delay(1000);

}
lcdClear(disp1);

	return 0;
}
