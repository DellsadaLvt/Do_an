#include<wiringPi.h>
#include<stdio.h>
#include <wiringSerial.h>
#include <string.h>


void getData(int *fd, float *dis);
void pushData(int *fd, char *str, char content[5]);



int main( void ){
	
	int fd,input;
	float dis;
	fd = serialOpen("/dev/ttyAMA0", 9600);
	char str[5];
	char temp;
	
	/* SETUP WIRINGPI LIB */
	wiringPiSetupPhys();
	
	printf("serial begin \n");
	
	
	while(1){
		
		
		
		pushData(&fd, str, "on");
		delay(100);
		getData(&fd, &dis);
		//pushData(&fd, str, "off");
		delay(1000);
		
		
	}
	
	serialClose(fd);
	
	
	return 0;
}

void getData(int *fd, float *dis){
	int i=0, result, data[5]={0,0,0,0,0};
	float dist;
	while( serialDataAvail(*fd)){
		data[i] = serialGetchar(*fd) - 48;
		//printf("%d\n", data[i]);
		//printf("Successful %d \n\n", i);
		i++;
	}
	printf("the value i: %d\n", i);
	if(i==3)
		result = data[0]*100 + data[1]*10 + data[2];
	if(i==4)
		result = data[0]*1000 + data[1]*100 + data[2]*10 + data[3];
	printf("the result is: %d\n", result);
	dist = result/100.0;
	printf("the result is: %f\n", dist);
	printf("\n\n\n");
	
	
}

void pushData(int *fd, char *str, char content[5]){
	strcpy(str, content);
	serialPuts(*fd, str);
}