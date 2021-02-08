#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CS_MCP3208 8
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000
#define TP 26
#define EP 21
#define LED 17

int ReadMcp3208ADC(unsigned char adcChannel)
{
unsigned char buff[3];
int nAdcValue = 0;
buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
buff[1] = ((adcChannel & 0x07)<<6);
buff[2] = 0x00;
digitalWrite(CS_MCP3208,0);
wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
buff[1] = 0x0F & buff[1];
nAdcValue = (buff[1]<<8) | buff[2];
digitalWrite(CS_MCP3208, 1);
return nAdcValue;
}
int main(void)
{
	int distance = 0;
	int pulse = 0;
	
	long startTime;
	long travelTime;
	
	if(wiringPiSetupGpio() == -1) return 1;
	
	pinMode(TP,OUTPUT);
	pinMode(EP,INPUT);
	pinMode(LED,OUTPUT);
int nCdsChannel = 0;
int nPhotoCellChannel = 1;
int nCdsValue = 0;
int nPhotoCellValue = 0;

if(wiringPiSetupGpio() == -1) {
	fprintf(stdout,"Not start wiringPi: %s\n",strerror(errno));
	return 1;
}
if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
fprintf(stdout, "wiringPiSPISetup Failed: %s\n", strerror(errno));
return 1;
}
pinMode(CS_MCP3208, OUTPUT);

for(;;)
	{
		digitalWrite(LED,LOW);
		nCdsValue = ReadMcp3208ADC(nCdsChannel);
	nPhotoCellValue = ReadMcp3208ADC(nPhotoCellChannel);
	printf("Cds Sensor Value = %u\n",nCdsValue);
	printf("Phocell Sensor Value = %u\n", nPhotoCellValue);

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
	
	if(distance < 10 && nPhotoCellValue <=100){
		
			digitalWrite(LED,HIGH);
	}
		else
		{
			digitalWrite(LED,LOW);
		}
		
	}
		
	
	return 0;

}
