#include<wiringPi.h>
#include<softPwm.h>

#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4
#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2
#define KEY_1	6
#define KEY_2	12
#define KEY_3	13
#define MAX_KEY_BT_NUM 3

unsigned char past_key ;
void MotorStop (void);
void MotorControl (unsigned char speed, unsigned char rotate);

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


int main(void){
	if(wiringPiSetupGpio() == -1)
		return 1;
		
int ck=2, spd =0;
	int nKeypadstate,i;
	int past_key;
	pinMode(MOTOR_MT_N_PIN,OUTPUT);
	pinMode(MOTOR_MT_P_PIN,OUTPUT);
	softPwmCreate(MOTOR_MT_N_PIN,0,100);
	softPwmCreate(MOTOR_MT_P_PIN,0,100);
	
	while(1)
	{
	nKeypadstate = KeypadRead();
		for(i=0;i<MAX_KEY_BT_NUM;i++){
			if((nKeypadstate & (1<<i))){
				
				if(nKeypadstate == 1){
					spd+=20;
					delay(500);
					if(spd >100 )
						spd=0;
						
				MotorControl(spd,ck);
					}
					
				else if(nKeypadstate == 2){
					int a = spd;
					MotorStop();
					delay(100);
					if(ck == 1){
					ck=2;
					MotorControl(a,ck);
					}
					
					else {
					ck=1;
					MotorControl(a,ck);
					}
				}
				
				else if(nKeypadstate == 4){
					spd=0;
					MotorControl(spd,ck);
					break;
				}
			
			}
	}
	}	
	return 0;
}
void MotorStop(){
		
	softPwmWrite(MOTOR_MT_N_PIN,0);
	softPwmWrite(MOTOR_MT_P_PIN,0);
	
}

void MotorControl(unsigned char speed, unsigned char rotate){
	
	if(rotate == LEFT_ROTATE){
		digitalWrite(MOTOR_MT_P_PIN,LOW);
		softPwmWrite(MOTOR_MT_N_PIN,speed);
	}
	
	else if(rotate == RIGHT_ROTATE){
		digitalWrite(MOTOR_MT_N_PIN,LOW);
		softPwmWrite(MOTOR_MT_P_PIN,speed);
	}
}
