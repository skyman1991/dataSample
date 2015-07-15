#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

int main()
{
	int i;
	int speed = 5 * 1000000;
	uint8_t data = 0x0c;

//	wiringPiSetup();
	
	if(wiringPiSPISetup(0,speed) == -1) {
		printf("erro\n");
		return -1;
	}

	for(; ; ) {
		printf("%d\n",data);
		wiringPiSPIDataRW(0,&data,1);
		delay(500);
		printf("%d\n\n",data);
	}
return 0;
}
