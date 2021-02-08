#include<wiringPi.h>

#define LED_RED_1 6
#define LED_YELLO_2 13
#define LED_GREEN_3 19

int main(void)
{

	if(wiringPiSetupGpio() == -1)
		return 1;

	pinMode(LED_RED_1,OUTPUT);
	digitalWrite(LED_RED_1,LOW);
	pinMode(LED_YELLO_2,OUTPUT);
	digitalWrite(LED_YELLO_2,LOW);
	pinMode(LED_GREEN_3,OUTPUT);
	digitalWrite(LED_GREEN_3,LOW);
	while(1)
	{
	digitalWrite(LED_RED_1,HIGH);
	delay(500);
	digitalWrite(LED_RED_1,LOW);
	delay(500);

	digitalWrite(LED_YELLO_2,HIGH);
	delay(500);
	digitalWrite(LED_YELLO_2,LOW);
	delay(500);
	
	digitalWrite(LED_GREEN_3,HIGH);
	delay(500);
	digitalWrite(LED_GREEN_3,LOW);
	delay(500);

	}

#include<wiringPi.h>

#define LED_RED_1 6
#define LED_YELLO_2 13
#define LED_GREEN_3 19

int main(void)
{

        if(wiringPiSetupGpio() == -1)
                return 1;

        pinMode(LED_RED_1,OUTPUT);
        digitalWrite(LED_RED_1,LOW);
        pinMode(LED_YELLO_2,OUTPUT);
        digitalWrite(LED_YELLO_2,LOW);
        pinMode(LED_GREEN_3,OUTPUT);
        digitalWrite(LED_GREEN_3,LOW);
        while(1)
        {
        digitalWrite(LED_RED_1,HIGH);
        delay(500);
        digitalWrite(LED_RED_1,LOW);
        delay(500);

        digitalWrite(LED_YELLO_2,HIGH);
        delay(500);
        digitalWrite(LED_YELLO_2,LOW);
        delay(500);

        digitalWrite(LED_GREEN_3,HIGH);
        delay(500);
        digitalWrite(LED_GREEN_3,LOW);
        delay(500);

        }
return 0;
}

#include<wiringPi.h>

#define LED_RED_1 6
#define LED_YELLO_2 13
#define LED_GREEN_3 19

int main(void)
{

        if(wiringPiSetupGpio() == -1)
                return 1;

        pinMode(LED_RED_1,OUTPUT);
        digitalWrite(LED_RED_1,LOW);
        pinMode(LED_YELLO_2,OUTPUT);
        digitalWrite(LED_YELLO_2,LOW);
        pinMode(LED_GREEN_3,OUTPUT);
        digitalWrite(LED_GREEN_3,LOW);
        while(1)
        {
        digitalWrite(LED_RED_1,HIGH);
        delay(500);
        digitalWrite(LED_RED_1,LOW);
        delay(500);

        digitalWrite(LED_YELLO_2,HIGH);
        delay(500);
        digitalWrite(LED_YELLO_2,LOW);
        delay(500);

        digitalWrite(LED_GREEN_3,HIGH);
        delay(500);
        digitalWrite(LED_GREEN_3,LOW);
        delay(500);

        }
return 0;
}

#include<wiringPi.h>

#define LED_RED_1 6
#define LED_YELLO_2 13
#define LED_GREEN_3 19

int main(void)
{

        if(wiringPiSetupGpio() == -1)
                return 1;

        pinMode(LED_RED_1,OUTPUT);
        digitalWrite(LED_RED_1,LOW);
        pinMode(LED_YELLO_2,OUTPUT);
        digitalWrite(LED_YELLO_2,LOW);
        pinMode(LED_GREEN_3,OUTPUT);
        digitalWrite(LED_GREEN_3,LOW);
        while(1)
        {
        digitalWrite(LED_RED_1,HIGH);
        delay(500);
        digitalWrite(LED_RED_1,LOW);
        delay(500);

        digitalWrite(LED_YELLO_2,HIGH);
        delay(500);
        digitalWrite(LED_YELLO_2,LOW);
        delay(500);

        digitalWrite(LED_GREEN_3,HIGH);
        delay(500);
        digitalWrite(LED_GREEN_3,LOW);
        delay(500);

        }
return 0;
}

