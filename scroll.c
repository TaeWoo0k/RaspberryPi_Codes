#include<stdio.h>
#include<wiringPi.h>
#include<lcd.h>


int main(void)
{
	int disp1,count=0;
	char a[16]="Onion $2x2=$4";
	char a1[16]="Beef $10x1=$10";
	char a2[16]="Pizza $5x1=$5";
	char a3[16]="Coke $2x3=$6";
	char a4[16]="Photato $3x1=$3";
	char a5[16]="TotalPurchased =$28";
	
	if(wiringPiSetupGpio()==-1) return 1;
	
	disp1 = lcdInit(2,16,4,17,4,6,13,19,26,0,0,0,0);

	lcdPosition(disp1,0,0);
	lcdPuts(disp1, a);
	lcdPosition(disp1,0,1);
	lcdPuts(disp1, a1);
	
	delay(1000);
	
	
	while(1){
		printf("\n Up(u),Down(d),Quit(q) :");
		str=getchar();
		while(getchar() != '\n');
		
		if(str=='u'){
			count +=1;
			count
			
			
		}
		else if(str=='d'){
			count -=1;
			
			}
					
		else if(str=='q')return 0; 
	}
	
				
	return 0;
}
