#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CS_MCP3208	8			//GPIO 8 (SPI_CE0_N)
#define SPI_CHANNEL	0			//SPI Channel
#define SPI_SPEED	1000000		//spi speed


int ReadMcp3208ADC(unsigned char adcChannel)
{
	unsigned char buff[3];
	int nAdcValue = 0;
	
	buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
	buff[1] = ((adcChannel & 0x07)<<6);
	buff[2] = 0x00;
	
	digitalWrite(CS_MCP3208,0);		//low cs Active
	
	wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
	
	//8bit data
	buff[1] = 0x0F & buff[1];
	nAdcValue = (buff[1]<<8) | buff[2];
	
	//spi chip Select command
	digitalWrite(CS_MCP3208, 1);
	
	return nAdcValue;
}

int main(){
	int nAdcChannel=0;
	int nAdcValue = 0;
	
	if(wiringPiSetupGpio() == -1) {
		fprintf(stdout,"NOT start wiringPi %s\n",strerror(errno));
		return 1;
	}
	if(wiringPiSPISetup(SPI_CHANNEL,SPI_SPEED)==-1){
		fprintf(stdout,"wiringPiSPISetup Failed\n");
		strerror(errno);
	return 1;
	}
	pinMode(CS_MCP3208,OUTPUT);
	while(1){
		nAdcValue = ReadMcp3208ADC(nAdcChannel);
		printf("Smoe Sensor Value = %u\n",nAdcValue);
		delay(1000);
	}
	return 0;
}

