#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>
#include<stdlib.h>
#define SERVO 4


#define BUZZER_PIN 25
#define DO_L 523
#define RE 587
#define MI 659
#define FA 698
#define SOL 784
#define RA 880
#define SI 987
#define DO_H 1046

//#define KEY_1	6
#define KEY_1   12
#define KEY_2	13
#define KEY_3	16

#define KEY_4	20
#define KEY_5	26
#define KEY_6	21

#define KEY_7	9
#define KEY_8	10
#define KEY_9	7

#define KEY_0	17
#define KEY_s	18
#define KEY_j	27


#define MAX_KEY_BT_NUM 12
#define MAX_KEY_BT_NUM1 4
#define MAX_KEY_BT_NUM2 4

void MotorControl (unsigned char speed, unsigned char rotate);

const int KEYPadTable[4][4] = {{KEY_1,KEY_2,KEY_3,KEY_4}, {KEY_5,KEY_6,KEY_7,KEY_8}, {KEY_9,KEY_0,KEY_s,KEY_j}};

        
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

int KeypadRead(void)
{
	int i,nKeypadstate,j=0;
	nKeypadstate = 0;
    
	for(i = 0 ; i<4;i++){
        for(j=0; j<4;j++){
            if(!digitalRead(KEYPadTable[i][j])){
            nKeypadstate |= (1<<(i*4)+j);
            }
        }
    }         
	return nKeypadstate;
}
int TimeDelay(int time){
    int i;
    if(time != 0){
    delay(1000);
    printf("%d",time);
    time -=1;
    }
    return time;
    }
    

int main(){
	char str;
	 int password[4]={2,5,7,8}, check[4] ;
    int i,j=0,k,correct=0,k1,q;  
    int ck=2, count =0;
	int nKeypadstate;
	int past_key; 
    
    for(i = 0; i<4; i++){
        printf("password [ %d ] = %d\n",i,password[i]);
    }
   
	if(wiringPiSetupGpio() == -1)return 1;
	softPwmCreate(SERVO,0,200);
	
	while(1)
	{
        int a = 256;
	nKeypadstate = KeypadRead();
                            
		for(i=0;i<12;i++){
            //printf(". \n");
			if((nKeypadstate & (1<<i))){
                
				if(nKeypadstate == 1){
					check[j]=1;
                    printf("1 ");
                    j+=1;
                    delay(100);
                      //      BUZZER_Init();
                            
                      //      Change_FREQ(SevenScale(2));
                       //     delay(500);
					}
					
				else if(nKeypadstate == 2){
					check[j]=2;
                    printf("2 ");
                    j+=1;
					delay(100);
				}
				
				else if(nKeypadstate == 4){
					check[j]=3;
                    printf("3 ");
                    j+=1;
					delay(100);
				}
                else if(nKeypadstate == 8){
                    printf("4 ");
					check[j]=4;
                    j+=1;
					delay(100);
				}
                else if(nKeypadstate == 16){
                    printf("5 ");
					check[j]=5;
                    j+=1;
					delay(100);
				}
                else if(nKeypadstate == 32){
                    printf("6 ");
					check[j]=6;
                    j+=1;
					delay(100);
				}
                else if(nKeypadstate == 64){
                    printf("7 ");
					check[j]=7;
                    j+=1;
					delay(100);
				}
                else if(nKeypadstate == 128){
                    printf("8 ");
					check[j]=8;
                    j+=1;
					delay(100);
				}
                else if(nKeypadstate == 256){   
                    printf("9 " );
					check[j]=9;
                    j+=1;
					delay(100);
				}
                
                else if(nKeypadstate == 512){   //*
                    for(k1=0;k1<4;k1++){
                        printf("\n check[%d] = %d  || password[%d] = %d ",i,check[i],i,password[i]);
                        if(check[k1] == password[k1])
                            correct += 1;
                         
                        else
                            correct = 0;
                    }
                    
                    printf("* ");
                    delay(100);
				}
                
                else if(nKeypadstate == 1024){  //0
					check[j]=0;
                    j+=1;
                    printf("0 ");
                    delay(100);
					
				}
                
                else if(nKeypadstate == 2048){  //#
                    
                    for(k1=0;k1<4;k1++){
                        
                        if(check[k1] == password[k1]){
                            correct += 1;
                            printf("\n check[%d] = %d  || password[%d] = %d correct = %d ",k1,check[k1],k1,password[k1],correct);
                        }
                        else
                            correct = 0;
                    }
                       if(correct == 4){
                           
                            printf("Correct \n");    //DO_L MI SOL DO_H @@ OR @@ MI MI DO_L RAE SOL
                           
                            BUZZER_Init();
                            softPwmWrite(SERVO,5);
                            softPwmWrite(SERVO,5);
                            Change_FREQ(SevenScale(0));
                            delay(500);
                            Change_FREQ(SevenScale(2));
                            delay(500);
                            Change_FREQ(SevenScale(4));
                            delay(500);
                            Change_FREQ(SevenScale(6));
                            delay(500);
                            STOP_FREQ();
                            softPwmWrite(SERVO,25);
                             for(k1=0;k1<4;k1++){
                                check[k1] = 0;
                                correct =0;
                            }
                            }
   
                        else if(correct <4 || correct>0){
                            printf("Uncorrect \n");    //FA DO FA DO FA DO FA DO
                            
                            BUZZER_Init();
                            Change_FREQ(SevenScale(3));
                            delay(500);
                            Change_FREQ(SevenScale(0));
                            delay(500);
                            Change_FREQ(SevenScale(3));
                            delay(500);
                            Change_FREQ(SevenScale(0));
                            delay(500);
                            Change_FREQ(SevenScale(3));
                            delay(500);
                            Change_FREQ(SevenScale(0));
                            delay(500);
                            STOP_FREQ();
                            count+=1;
                    }
                    delay(100);
                }
            delay(150);
            if(count == 3){
            for(q=0;q<120;q++){
                delay(1000);
                }
            }
        }
        
        }
		
    }
	return 0;


}


