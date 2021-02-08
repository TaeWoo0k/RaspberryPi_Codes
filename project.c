#include<wiringPi.h>
#include<stdio.h>
#include<errno.h>
#include<wiringPiSPI.h>


#define CS_MCP3208	8
#define SPI_CHANNEL	0
#define SPI_SPEED 1000000
#define TP 26
#define EP 21
#define LED 17

int ReadMcp3208ADC(unsigned char adcChannel)
{
	unsigned char buff[3];
	int nAdcValue = 0;
	buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
	buff[1] = ((adcChannel & 0x07) << 6);
	buff[2] = 0x00;
	
	digitalWrite(CS_MCP3208,0);
	wiringPiSPIDataRW(SPI_CHANNEL,buff,3);
	buff[1] = 0x0F & buff[1];
	nAdcValue = (buff[1]<<8) | buff[2];
	digitalWrite(CS_MCP3208,1);
	return nAdcValue;
}

float getDistance(void)

{
	float fDistance;
	int nStartTime,nEndTime;
	
		
	digitalWrite(TP,LOW);
	delayMicroseconds(2);
	digitalWrite(TP,HIGH);
	delayMicroseconds(10);
	digitalWrite(TP,LOW);
	while(digitalRead(EP) == LOW);
	nStartTime = micros();
	while(digitalRead(EP) == HIGH);
	nEndTime = micros();
	fDistance = (nEndTime - nStartTime) * 0.034 /2;
	return fDistance;
}

int main(void)
{
	
	int nCdsChannel =0;
	int nPhotoCellChannel =1;
	int nCdsValue = 0;
	int nPhotoCellValue =0;
	

	if(wiringPiSetupGpio() == -1){
		//fprintf(stdout,"Not start wiringPi : %s \n",strerror(errno));
		 return 1;
	 }
	 
	 if(wiringPiSPISetup(SPI_CHANNEL,SPI_SPEED)==-1){
		// fprintf(stdout,"wiringPiSPISetup Failed : %s \n",strerror(errno));
		 return 1;
	 }
	 
	int count =0;
	pinMode(CS_MCP3208,OUTPUT);
	pinMode(TP,OUTPUT);
	pinMode(EP,INPUT);
	pinMode(LED,OUTPUT);

	while(1){
		float fDistance = getDistance();
		printf("Distance : %2fcm \n",fDistance);
			
		nCdsValue = ReadMcp3208ADC(nCdsChannel);
		nPhotoCellValue = ReadMcp3208ADC(nPhotoCellValue);
		printf("Cds Sensor Value = %u\n",nCdsValue);
		printf("Phocell Sensor Calue = %u \n",nPhotoCellValue);
		
		if(fDistance < 10 && nCdsValue <=200){
		
			digitalWrite(LED,HIGH);
	}
		else
		{
			digitalWrite(LED,LOW);
		}
		
	delay(100);
	}
	return 0;
}
