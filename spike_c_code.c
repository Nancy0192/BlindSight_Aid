#include <stdio.h>
#include<stdlib.h>

int main() {
	int sensorValue;
	int reset;
	int watersensor;
	int buzzer = 0;
	int buzzer_2 = 0;
	int mask1 = 0xFFFFFFE7;
	int test,test1,test2,test3,test4;


	int buzzer_reg, buzzer_2_reg;
	buzzer_reg = buzzer*8;
        buzzer_2_reg = buzzer_2*16;
	asm volatile(
	"and x30, x30, %2\n\t"
	"or x30, x30, %0 \n\t"
	"or x30, x30, %1 \n\t"
	: 
	:"r"(buzzer_reg),"r"(buzzer_2_reg), "r"(mask1)
	:"x30"
	);
	
	 asm volatile(
    	"addi x30, x30, 0\n\t"
    	:"=r"(test)
    	:
    	:"x30"
    	);
    	printf("Test = %d\n",test);
	printf("IRSensorPin = %d, reset=%d, buzzer_object = %d, buzzer_water = %d, watersensorpin=%d\n", sensorValue, reset, buzzer_reg, buzzer_2_reg, watersensor);
    	int z;
	for(z=0;z<1;z++)
	
	
//	    while (1)
		 {
		printf("Entering While Loop\n");
	 	asm volatile(
		"andi %0, x30, 1\n\t"
		:"=r"(reset)
		:
		:
		);
		reset=0;
	    	if (reset)
	    	{
	    	buzzer =0;
		buzzer_2 =0;
		buzzer_reg = buzzer*8;
		buzzer_2_reg = buzzer_2*16;
		printf("Reseting the sensor values\n");
		asm volatile(
	    	"addi %0, x30, 0\n\t"
	    	:"=r"(test1)
	    	:
	    	:"x30"
	    	);
	    	printf("test1 = %d\n",test1);
		printf("Reset Button_val=%d\n",reset);
	    	}
	    	
	    	

		
		
		else  {
		
		asm volatile(
		"andi %0, x30, 0x0002\n\t"
		:"=r"(watersensor)
		:
		:
		);
		
		asm volatile(
		"andi %0, x30, 0x0004\n\t"
		:"=r"(sensorValue)
		:
		:
		);
		
		sensorValue = 0;
		watersensor = 0;
		
		if ((!sensorValue) && (!watersensor)){
		buzzer_2 = 1;
		buzzer = 0;
		buzzer_reg = buzzer*8;
		buzzer_2_reg = buzzer_2*16;
	       		
		}
	 
		if ((!sensorValue) && (watersensor)){
		buzzer_2 = 0;
		buzzer = 0;
		buzzer_reg = buzzer*8;
		buzzer_2_reg = buzzer_2*16;
		
		}
		
		if ((sensorValue) && (!watersensor)){
		buzzer_2 = 1;
		buzzer = 1;
		buzzer_reg = buzzer*8;
		buzzer_2_reg = buzzer_2*16;
		}
		
		if ((sensorValue) && (watersensor)){
		buzzer_2 = 0;
		buzzer = 1;
		buzzer_reg = buzzer*8;
		buzzer_2_reg = buzzer_2*16;
		}
		}
		
		
		

		asm volatile(
			"and x30, x30, %2\n\t"
			"or x30, x30, %0 \n\t"
			"or x30, x30, %1 \n\t"
			: 
			:"r"(buzzer_reg),"r"(buzzer_2_reg), "r"(mask1)
			:"x30"
			);
	    


	    	
	    	
	    	asm volatile(
	    	"addi %0, x30, 0\n\t"
	    	:"=r"(test4)
	    	:
	    	:"x30"
	    	);
	    	printf("Test4 = %d\n",test4);
	    printf("IRSensorPin = %d, reset=%d, buzzer_object = %d, buzzer_water = %d, watersensorpin=%d\n", sensorValue, reset, buzzer, buzzer_2, watersensor);

	    return 0;
	}
	}
