#include<wiringPi.h>

#define LED_1	6
#define LED_2	13
#define LED_3	19

#define KEY_1	11
#define KEY_2	9
#define KEY_3	10

#define LED_ON 1
#define LED_OFF 0

#define MAX_LED_NUM 3
#define MAX_KEY_BT_NUM 3

const int LEDPinTable[3] ={LED_1,LED_2,LED_3};
const int KEYPadTable[3] = {KEY_1,KEY_2,KEY_3};

int KeypadRead(void)
{
	int i,nKeypadstate;
	nKeypadstate = 0;
	for(i = 0 ; i<MAX_KEY_BT_NUM;i++){
		if(!digitalRead(KEYPadTable[i])){
		nKeypadstate |= (1<<i);
		}
	}
	return nKeypadstate;
}

void LedControl(int LedNum, int Cmd){
int i;

for(i=0;i<MAX_LED_NUM;i++){
	if(i==LedNum){
		if(Cmd == LED_ON){
			digitalWrite(LEDPinTable[i],HIGH);
				}
		else{
			digitalWrite(LEDPinTable[i],LOW);
			}

		}
	}
}
int main(void)
{
	if(wiringPiSetupGpio()== -1)
	return 1;
int i;
int nKeypadstate;
	for(i=0;i<MAX_LED_NUM;i++){
	pinMode(LEDPinTable[i],OUTPUT);	
	}

	while(1)
	{
	nKeypadstate = KeypadRead();
		for(i=0;i<MAX_KEY_BT_NUM;i++){
			if((nKeypadstate & (1<<i))){
				LedControl(i,LED_ON);
			}
			else{
				LedControl(i,LED_OFF);
			}
		}
	}
}
