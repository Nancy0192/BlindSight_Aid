# BlindSight_Aid

This repository contains RISC-V based blind sight aid.


## AIM
Navigating the world independently is a fundamental human right, yet visually impaired individuals face significant challenges in mobility and safety. This advanced assistive device aims to empower visually impaired individuals by enhancing their spatial awareness, obstacle detection, and overall confidence while navigating unfamiliar environments.
We will be using RISC-V to build the device and the sensor for that partiular functionality.


## BLOCK DIAGRAM OF THE BLIND STICK


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/130a69a7-e9ec-4d0d-a48c-cd235009702a)






## ASSEMBLY CODE GENERATION
We will be using RISC-V GNU Toolchain to convert our C code into assembly code. Let us first go through the RISC-V:

### RISC-V TOOLCHAIN
RISC-V is an open-source instruction set architecture (ISA) used for the development of custom processors targeting a variety of end applications.RISC-V ISA is considered the fifth generation of processors built on the concept of the reduced instruction set computer (RISC). Due to its openness and its technical merits, it has become very popular in recent years. The royalty-free RISC-V ISA features a small core set of instructions upon which all the design’s software runs. Its optional extensions allow designers to tailor the architecture for a variety of different end markets. Essentially, the RISC-V architecture allows designers to customize and build their processor in a way that’s tailored to their target end applications, so they can optimize the power, performance, and area (PPA) for those applications. The RISC-V ISA also provides the flexibility to pick and choose from available features, rather than having to use the full feature set. 
The GNU compile toolchain is a set of programming tools in LINUX system that can be use for compiling a code to generate certain executable program, library and debugger and whose detail can be found in references. RISC-V is one such toolchain which supports C and C++ cross compiler. It supports two build modes: a generic ELF/Newlib toolchain and a more sophisticated Linux-ELF/glibc toolchain and the github link for the same can be found in references.

### C Code

```
//#include <stdio.h>
//#include<stdlib.h>

int main() {
	int sensorValue;
	int reset;
	int watersensor;
	int buzzer = 0;
	int buzzer_2 = 0;
	int mask1 = 0xFFFFFFF7;
//	int test,test1,test2,test3,test4;


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
	/*
	 asm volatile(
    	"addi x30, x30, 0\n\t"
    	:"=r"(test)
    	:
    	:"x30"
    	);
    	printf("Test = %d\n",test);
	printf("IRSensorPin = %d, reset=%d, buzzer_object = %d, buzzer_water = %d, watersensorpin=%d\n", sensorValue, reset, buzzer_reg, buzzer_2_reg, watersensor);
        printf("Inside while 1\n");
    	int z;
	for(z=0;z<1;z++)
	*/
	
	    while (1)
		 {
		
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
	    	}
	    	
	    	/*
	    	asm volatile(
	    	"addi %0, x30, 0\n\t"
	    	:"=r"(test1)
	    	:
	    	:"x30"
	    	);
	    	printf("test1 = %d\n",test1);
		printf("Reset Button_val=%d\n",reset);
		*/
		
		if (!reset){
		int water_reg;
		
		

		asm volatile(
		"andi %0, x30, 2\n\t"
		:"=r"(water_reg)
		:
		:
		);
	    	
		watersensor = water_reg/2;
//	    	watersensor = 1;
	    	if (!watersensor){
	    		
	    		buzzer_2 = 1;
	       		buzzer_2_reg = buzzer_2*16;
	       		/*

		        asm volatile(
		    	"addi %0, x30, 0\n\t"
		    	:"=r"(test2)
		    	:
		    	:"x30"
		    	);
		    	printf("test2 = %d\n",test2);
		        printf("IRSensorPin = %d, reset=%d, buzzer_object = %d, buzzer_water = %d, watersensorpin=%d\n", sensorValue, reset, buzzer_reg, buzzer_2_reg, watersensor);*/
	    		
	    		
	    	}
	    	
	    	else if(watersensor){
	    	
	    		buzzer_2 = 0;
	       		buzzer_2_reg = buzzer_2*16;
	       		
	       		/*

			asm volatile(
		    	"addi %0, x30, 0\n\t"
		    	:"=r"(test2)
		    	:
		    	:"x30"
		    	);
		    	printf("test2 = %d\n",test2);
		    	printf("IRSensorPin = %d, reset=%d, buzzer_object = %d, buzzer_water = %d, watersensorpin=%d\n", sensorValue, reset, buzzer_reg, buzzer_2_reg, watersensor);
		    	*/
	    	
	    	}


		int ir_sensor_reg;
	    	asm volatile(
		"andi %0, x30, 4\n\t"
		:"=r"(ir_sensor_reg)
		:
		:
		);

		sensorValue = ir_sensor_reg/4;
		sensorValue = 1;
		
		if (sensorValue) {
			buzzer = 1;
			buzzer_reg = buzzer*8;
			/*

			asm volatile(
		    	"addi %0, x30, 0\n\t"
		    	:"=r"(test3)
		    	:
		    	:"x30"
		    	);
		    	printf("test3 = %d\n",test3);
		        printf("IRSensorPin = %d, reset=%d, buzzer_object = %d, buzzer_water = %d, watersensorpin=%d\n", sensorValue, reset, buzzer_reg, buzzer_2_reg, watersensor);*/

		} else if (!sensorValue){
			buzzer =0;
			buzzer_reg = buzzer*8;
			/*

			asm volatile(
		    	"addi %0, x30, 0\n\t"
		    	:"=r"(test3)
		    	:
		    	:"x30"
		    	);
		    	printf("test3 = %d\n",test3);
		    	
		        printf("IRSensorPin = %d, reset=%d, buzzer_object = %d, buzzer_water = %d, watersensorpin=%d\n", sensorValue, reset, buzzer_reg, buzzer_2_reg, watersensor);*/

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

	    	
	    	/*
	    	asm volatile(
	    	"addi %0, x30, 0\n\t"
	    	:"=r"(test4)
	    	:
	    	:"x30"
	    	);
	    	printf("Test4 = %d\n",test4);
	    printf("IRSensorPin = %d, reset=%d, buzzer_object = %d, buzzer_water = %d, watersensorpin=%d\n", sensorValue, reset, buzzer_reg, buzzer_2_reg, watersensor);*/

	    return 0;
	}
	}
```

### GCC COMPILER RESULTS

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/5893aa19-f7ed-4693-b1c5-a88f4308b969)


### ASSEMBLY STRUCTURE

Commands to convert C code into assmbly code using RISC-V 

```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o ./out check_f.c 
riscv64-unknown-elf-objdump -d  -r out > blindstick_assembly.txt
```

### GPIO

```
x30[0] is an input pin for IR sensor to detect the object.
x30[1]  is an input pin used as a restart trigger.
x30[2] is an input pin used for water detection.
x30[3] is an output pin used to indicate about the object detection.
x30[4] is an output pin used to indicate about the water detection. 
```




### ASSEMBLY CODE


```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fc010113          	addi	sp,sp,-64
   10058:	02812e23          	sw	s0,60(sp)
   1005c:	04010413          	addi	s0,sp,64
   10060:	fe042223          	sw	zero,-28(s0)
   10064:	fe042023          	sw	zero,-32(s0)
   10068:	ff700793          	li	a5,-9
   1006c:	fcf42e23          	sw	a5,-36(s0)
   10070:	fe442783          	lw	a5,-28(s0)
   10074:	00379793          	slli	a5,a5,0x3
   10078:	fef42623          	sw	a5,-20(s0)
   1007c:	fe042783          	lw	a5,-32(s0)
   10080:	00479793          	slli	a5,a5,0x4
   10084:	fef42423          	sw	a5,-24(s0)
   10088:	fec42783          	lw	a5,-20(s0)
   1008c:	fe842703          	lw	a4,-24(s0)
   10090:	fdc42683          	lw	a3,-36(s0)
   10094:	00df7f33          	and	t5,t5,a3
   10098:	00ff6f33          	or	t5,t5,a5
   1009c:	00ef6f33          	or	t5,t5,a4
   100a0:	001f7793          	andi	a5,t5,1
   100a4:	fcf42c23          	sw	a5,-40(s0)
   100a8:	fc042c23          	sw	zero,-40(s0)
   100ac:	fd842783          	lw	a5,-40(s0)
   100b0:	02078263          	beqz	a5,100d4 <main+0x80>
   100b4:	fe042223          	sw	zero,-28(s0)
   100b8:	fe042023          	sw	zero,-32(s0)
   100bc:	fe442783          	lw	a5,-28(s0)
   100c0:	00379793          	slli	a5,a5,0x3
   100c4:	fef42623          	sw	a5,-20(s0)
   100c8:	fe042783          	lw	a5,-32(s0)
   100cc:	00479793          	slli	a5,a5,0x4
   100d0:	fef42423          	sw	a5,-24(s0)
   100d4:	fd842783          	lw	a5,-40(s0)
   100d8:	0a079c63          	bnez	a5,10190 <main+0x13c>
   100dc:	002f7793          	andi	a5,t5,2
   100e0:	fcf42a23          	sw	a5,-44(s0)
   100e4:	fd442783          	lw	a5,-44(s0)
   100e8:	01f7d713          	srli	a4,a5,0x1f
   100ec:	00f707b3          	add	a5,a4,a5
   100f0:	4017d793          	srai	a5,a5,0x1
   100f4:	fcf42823          	sw	a5,-48(s0)
   100f8:	fd042783          	lw	a5,-48(s0)
   100fc:	00079e63          	bnez	a5,10118 <main+0xc4>
   10100:	00100793          	li	a5,1
   10104:	fef42023          	sw	a5,-32(s0)
   10108:	fe042783          	lw	a5,-32(s0)
   1010c:	00479793          	slli	a5,a5,0x4
   10110:	fef42423          	sw	a5,-24(s0)
   10114:	01c0006f          	j	10130 <main+0xdc>
   10118:	fd042783          	lw	a5,-48(s0)
   1011c:	00078a63          	beqz	a5,10130 <main+0xdc>
   10120:	fe042023          	sw	zero,-32(s0)
   10124:	fe042783          	lw	a5,-32(s0)
   10128:	00479793          	slli	a5,a5,0x4
   1012c:	fef42423          	sw	a5,-24(s0)
   10130:	004f7793          	andi	a5,t5,4
   10134:	fcf42623          	sw	a5,-52(s0)
   10138:	fcc42783          	lw	a5,-52(s0)
   1013c:	41f7d713          	srai	a4,a5,0x1f
   10140:	00377713          	andi	a4,a4,3
   10144:	00f707b3          	add	a5,a4,a5
   10148:	4027d793          	srai	a5,a5,0x2
   1014c:	fcf42423          	sw	a5,-56(s0)
   10150:	00100793          	li	a5,1
   10154:	fcf42423          	sw	a5,-56(s0)
   10158:	fc842783          	lw	a5,-56(s0)
   1015c:	00078e63          	beqz	a5,10178 <main+0x124>
   10160:	00100793          	li	a5,1
   10164:	fef42223          	sw	a5,-28(s0)
   10168:	fe442783          	lw	a5,-28(s0)
   1016c:	00379793          	slli	a5,a5,0x3
   10170:	fef42623          	sw	a5,-20(s0)
   10174:	01c0006f          	j	10190 <main+0x13c>
   10178:	fc842783          	lw	a5,-56(s0)
   1017c:	00079a63          	bnez	a5,10190 <main+0x13c>
   10180:	fe042223          	sw	zero,-28(s0)
   10184:	fe442783          	lw	a5,-28(s0)
   10188:	00379793          	slli	a5,a5,0x3
   1018c:	fef42623          	sw	a5,-20(s0)
   10190:	fec42783          	lw	a5,-20(s0)
   10194:	fe842703          	lw	a4,-24(s0)
   10198:	fdc42683          	lw	a3,-36(s0)
   1019c:	00df7f33          	and	t5,t5,a3
   101a0:	00ff6f33          	or	t5,t5,a5
   101a4:	00ef6f33          	or	t5,t5,a4
   101a8:	00000793          	li	a5,0
   101ac:	00078513          	mv	a0,a5
   101b0:	03c12403          	lw	s0,60(sp)
   101b4:	04010113          	addi	sp,sp,64
   101b8:	00008067          	ret
```

### UNIQUE INSTRUCTION

```
Number of different instructions: 16
List of unique instructions:
addi
slli
bnez
and
li
beqz
srli
add
j
mv
srai
ret
andi
or
sw
lw

```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/172b8533-4583-4de3-9f71-856caf203e2f)



### SPIKE SIMULATION

Use the following command to simulate the C code using spike:

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out check.c
spike pk out
```

The code consist of 3 inputs (for reset, IR sensor, water sensor) and two outputs. We will go through each condition and verify it using the spike simulation.

**Condition 1** When Reset = 1 <br>

When reset = 1 the code will not enter the while loop and will turn both the outputs zero.

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/fd24205d-f03e-4679-9b3c-272d2283f987)



**Condition 2** when Reset =0, IR sensor = 1, water sensor = 1 (when it will detect the water it will send zero to the processor)

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/d65e3349-8b10-4ff4-9a37-209b564e466f)


**Condition 3** when Reset =0, IR sensor = 0, water sensor = 1 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/58d63522-eac3-40bd-84bd-c2c390f17f71)


**Condition 4** when Reset =0, IR sensor = 1, water sensor = 0 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/fe58c2de-f522-4073-9e6d-4c819c01bf04)


**Condition 5** when Reset =0, IR sensor = 0, water sensor = 0 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/b83c7a2f-7a27-4d20-a5e2-41e0da96d57b)







