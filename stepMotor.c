#include<stdio.h>
#include<wiringPi.h>

#define OUT1 4
#define OUT2 18
#define OUT3 22
#define OUT4 24
#define KEY_1	6
#define KEY_2	12
#define KEY_3	13
#define MAX_KEY_BT_NUM 3


const int KEYPadTable[3] = {KEY_1,KEY_2,KEY_3};
float a=0;


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

void setsteps(int w1, int w2, int w3, int w4){
	
	pinMode(OUT1,OUTPUT);
	digitalWrite(OUT1,w1);
	pinMode(OUT2,OUTPUT);
	digitalWrite(OUT2,w2);
	pinMode(OUT3,OUTPUT);
	digitalWrite(OUT3,w3);
	pinMode(OUT4,OUTPUT);
	digitalWrite(OUT4,w4);	
	
}

void forward(int del, int steps){
	int i;
	for(i=0;i<steps; i++){
		setsteps(1,1,0,0);
		delay(del);
		setsteps(0,1,0,0);
		delay(del);
		setsteps(0,1,1,0);
		delay(del);
		setsteps(0,0,1,0);
		delay(del);
		setsteps(0,0,1,1);
		delay(del);
		setsteps(0,0,0,1);
		delay(del);
		setsteps(1,0,0,1);
		delay(del);
		setsteps(1,0,0,0);
		delay(del);
	}
		a+=0.703;
		if(a>360)
			a-=360;
	printf("Right  %f\n",a);
}



void backward(int del, int steps){
	int k;
	for(k=0;k<steps; k++){
		setsteps(1,0,0,0);
		delay(del);
		setsteps(1,0,0,1);
		delay(del);
		setsteps(0,0,0,1);
		delay(del);
		setsteps(0,0,1,1);
		delay(del);
		setsteps(0,0,1,0);
		delay(del);
		setsteps(0,1,1,0);
		delay(del);
		setsteps(0,1,0,0);
		delay(del);
		setsteps(1,1,0,0);
		delay(del);
	}
	a-=0.703;
	if(a<0)
		a=360-(a*-1);
	printf("Left  %f \n",a);
}

int main(void){
	
	int nKeypadstate,i,j=512;
	int past_key;
	int ck=0;
	
	if(wiringPiSetupGpio() == -1)
	return 1;
	
	while(1)
	{
	nKeypadstate = KeypadRead();
		for(i=0;i<MAX_KEY_BT_NUM;i++){
			if((nKeypadstate & (1<<i))){
				
					
				if(nKeypadstate == 2){
				
					if(ck==0){
						ck=1;
						printf("@ \n");
						delay(1000);
					}
					else{
						delay(1000);
						
						printf("! \n");
						ck=0;
					}
				
				}
				
				else if(nKeypadstate == 1){
					
						if(ck==0){
						j--;
						forward(1,511%j);
						delay(1000);
						if(j==0)
							j=511;
					}
					else{
						j--;
						backward(1,511%j);
						delay(1000);
						if(j==0)
							j=511;
					}
				}
						
			}
				
			
		}
	}
	
	return 0;
}
	
	

