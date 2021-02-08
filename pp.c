
#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>
#include<stdlib.h>
#define TP 18
#define EP 27

#define SERVO 4

int main(void){
	
	int distance = 0;
	int pulse = 0;
	
	long startTime;
	long travelTime;
	
	if(wiringPiSetupGpio() == -1) return 1;
	
	pinMode(TP,OUTPUT);
	pinMode(EP,INPUT);
	
	for(;;)
	{
		
		digitalWrite(TP,LOW);
		delay(2);
		digitalWrite(TP,HIGH);
		delay(20);
		digitalWrite(TP,LOW);
		
		while(digitalRead(EP)==LOW);
		startTime=micros();
		
		while(digitalRead(EP) == HIGH);
		travelTime = micros() - startTime;
		
		int distance = travelTime /58;
		printf("distance = %dcm\n",distance);
		softPwmCreate(SERVO,0,200);
	
		if(distance >10){
			softPwmWrite(SERVO,25);
			delay(2000);
			softPwmWrite(SERVO,5);
			exit(0);
		}
		delay(200);
	}
		
	
	return 0;
}
