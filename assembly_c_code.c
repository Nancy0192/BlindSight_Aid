
int main() {
	int sensorValue;
	int reset;
	int watersensor;
	int buzzer = 0;
	int buzzer_2 = 0;
	int mask1 = 0xFFFFFFE7;

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
	
	    while (1)
		 {
		
	 	asm volatile(
		"andi %0, x30, 1\n\t"
		:"=r"(reset)
		:
		:
		);
		
	    	if (reset)
	    	{
	    	buzzer =0;
		buzzer_2 =0;
		buzzer_reg = buzzer*8;
		buzzer_2_reg = buzzer_2*16;
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
	    

	}
	
	return 0;
	
	}
