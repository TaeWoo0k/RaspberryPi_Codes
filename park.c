#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>
#include<stdlib.h>
#define TP 18
#define EP 27

#define LED 11
#define BUZZER_PIN 12
#define DO_L 523

#define RE 587
#define MI 659
#define FA 698
#define SOL 784
#define RA 880
#define SI 987
#define DO_H 1046

unsigned int SevenScale(unsigned char scale)
{
	unsigned int _ret = 0;
	switch(scale){
		case 0:
			_ret=DO_L;
			break;
		case 1:
			_ret=RE;
			break;
		case 2:
			_ret=MI;
			break;
		case 3:
			_ret=FA;
			break;
		case 4:
			_ret=SOL;
			break;
		case 5:
			_ret=RA;
			break;
		case 6:
			_ret=SI;
			break;
		case 7:
			_ret=DO_H;
			break;
		
		
	}
	return _ret;
}

void Change_FREQ(unsigned int freq)
{
	softToneWrite(BUZZER_PIN,freq);
}

void STOP_FREQ()
{
	softToneWrite(BUZZER_PIN,0);
}
	

void BUZZER_Init()
{
	softToneCreate(BUZZER_PIN);
	STOP_FREQ;
}	

int main(void){
	
	int distance = 0;
	int pulse = 0;
	
	long startTime;
	long travelTime;
	
	if(wiringPiSetupGpio() == -1) return 1;
	
	pinMode(TP,OUTPUT);
	pinMode(EP,INPUT);
	pinMode(LED,OUTPUT);
	digitalWrite(LED,LOW);
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
		//softPwmCreate(SERVO,0,200);
	BUZZER_Init();
		
		if(distance < 5){		
			digitalWrite(LED,HIGH);
			Change_FREQ(SevenScale(5));
			sleep(1);
		}
		else if(distance < 8 && distance >=5){
			Change_FREQ(SevenScale(5));
			delay(30);
			STOP_FREQ();
		}	
		else if(distance < 10 && distance >=8){
			Change_FREQ(SevenScale(5));
			delay(80);
			STOP_FREQ();
		}
		else if(distance < 100){
			digitalWrite(LED,LOW);
		}
		else
		{
			STOP_FREQ();
		}
	}

	return 0;
}



