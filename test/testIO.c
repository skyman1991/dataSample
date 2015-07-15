#include <stdio.h> 
#include <stdlib.h>
#include <wiringPi.h>

#define LED 0

int main()
{
	int i;

	if(wiringPiSetup() == -1)
		exit(-1);
	pinMode(LED,OUTPUT);
	for(i = 0; i < 10; i++) {
		digitalWrite(LED,1);
		delay(500);
		digitalWrite(LED,0);
		delay(500);
}
return 0;
}
