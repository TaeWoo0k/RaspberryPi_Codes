#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>

#define SERVO 6

int main(){
	char str;
	
	if(wiringPiSetupGpio() == -1)return 1;
	
	softPwmCreate(SERVO,0,200);
	
	while(1){
		printf("\n Center(c),Left(l), Right(r),Quit(q) :");
		str=getchar();
		while(getchar() != '\n');
		
		if(str=='c')softPwmWrite(SERVO,15);
		else if(str=='l')softPwmWrite(SERVO,25);
		else if(str=='r')softPwmWrite(SERVO,5);
		else if(str=='q')return 0; 
	}
	return 0;
	
}
