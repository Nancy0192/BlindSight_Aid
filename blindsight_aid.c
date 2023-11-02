#include <stdio.h>




int main() {

	int sensorValue = 1;
	int watersensor = 0;
	int buzzer = 0;
	int buzzer_2 = 0;
	int reset =0;




    while (1) {
	    	if (reset)
	    	{
	    	sensorValue =0;
	    	buzzer =0;
	    	printf("Resetting the values to Zero\n");
	    	}
    	
		else  {
		

		
		if ((!sensorValue) && (!watersensor)){
		buzzer_2 = 1;
		buzzer = 0;
		
		printf("Object not detected\n Water detected\n");
	
		}
	 
		if ((!sensorValue) && (watersensor)){
		buzzer_2 = 0;
		buzzer = 0;
		
		printf("Object not detected\n Water not detected\n");

		}
		
		if ((sensorValue) && (!watersensor)){
		buzzer_2 = 1;
		buzzer = 1;
		
		printf("Object detected\n Water detected\n");

		}
		
		if ((sensorValue) && (watersensor)){
		buzzer_2 = 0;
		buzzer = 1;
		
		printf("Object detected\n Water not detected\n");

		}
		}
        
  
    }

    return 0;
}


