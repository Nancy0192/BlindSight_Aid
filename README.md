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
include <stdio.h>




int main() {

	int sensorValue;
	int watersensor;
	int reset;
	int buzzer = 0;
	int buzzer_2 = 0;
	

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

```

### GCC COMPILER RESULTS

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/5893aa19-f7ed-4693-b1c5-a88f4308b969)


### ASSEMBLY STRUCTURE

**Code**


```

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
```


Commands to convert C code into assmbly code using RISC-V 

```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o ./out ccode.c 
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
   10054:	fd010113          	addi	sp,sp,-48
   10058:	02812623          	sw	s0,44(sp)
   1005c:	03010413          	addi	s0,sp,48
   10060:	fe042223          	sw	zero,-28(s0)
   10064:	fe042023          	sw	zero,-32(s0)
   10068:	fe700793          	li	a5,-25
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
   100a8:	fd842783          	lw	a5,-40(s0)
   100ac:	02078463          	beqz	a5,100d4 <main+0x80>
   100b0:	fe042223          	sw	zero,-28(s0)
   100b4:	fe042023          	sw	zero,-32(s0)
   100b8:	fe442783          	lw	a5,-28(s0)
   100bc:	00379793          	slli	a5,a5,0x3
   100c0:	fef42623          	sw	a5,-20(s0)
   100c4:	fe042783          	lw	a5,-32(s0)
   100c8:	00479793          	slli	a5,a5,0x4
   100cc:	fef42423          	sw	a5,-24(s0)
   100d0:	0e40006f          	j	101b4 <main+0x160>
   100d4:	002f7793          	andi	a5,t5,2
   100d8:	fcf42a23          	sw	a5,-44(s0)
   100dc:	004f7793          	andi	a5,t5,4
   100e0:	fcf42823          	sw	a5,-48(s0)
   100e4:	fd042783          	lw	a5,-48(s0)
   100e8:	02079863          	bnez	a5,10118 <main+0xc4>
   100ec:	fd442783          	lw	a5,-44(s0)
   100f0:	02079463          	bnez	a5,10118 <main+0xc4>
   100f4:	00100793          	li	a5,1
   100f8:	fef42023          	sw	a5,-32(s0)
   100fc:	fe042223          	sw	zero,-28(s0)
   10100:	fe442783          	lw	a5,-28(s0)
   10104:	00379793          	slli	a5,a5,0x3
   10108:	fef42623          	sw	a5,-20(s0)
   1010c:	fe042783          	lw	a5,-32(s0)
   10110:	00479793          	slli	a5,a5,0x4
   10114:	fef42423          	sw	a5,-24(s0)
   10118:	fd042783          	lw	a5,-48(s0)
   1011c:	02079663          	bnez	a5,10148 <main+0xf4>
   10120:	fd442783          	lw	a5,-44(s0)
   10124:	02078263          	beqz	a5,10148 <main+0xf4>
   10128:	fe042023          	sw	zero,-32(s0)
   1012c:	fe042223          	sw	zero,-28(s0)
   10130:	fe442783          	lw	a5,-28(s0)
   10134:	00379793          	slli	a5,a5,0x3
   10138:	fef42623          	sw	a5,-20(s0)
   1013c:	fe042783          	lw	a5,-32(s0)
   10140:	00479793          	slli	a5,a5,0x4
   10144:	fef42423          	sw	a5,-24(s0)
   10148:	fd042783          	lw	a5,-48(s0)
   1014c:	02078a63          	beqz	a5,10180 <main+0x12c>
   10150:	fd442783          	lw	a5,-44(s0)
   10154:	02079663          	bnez	a5,10180 <main+0x12c>
   10158:	00100793          	li	a5,1
   1015c:	fef42023          	sw	a5,-32(s0)
   10160:	00100793          	li	a5,1
   10164:	fef42223          	sw	a5,-28(s0)
   10168:	fe442783          	lw	a5,-28(s0)
   1016c:	00379793          	slli	a5,a5,0x3
   10170:	fef42623          	sw	a5,-20(s0)
   10174:	fe042783          	lw	a5,-32(s0)
   10178:	00479793          	slli	a5,a5,0x4
   1017c:	fef42423          	sw	a5,-24(s0)
   10180:	fd042783          	lw	a5,-48(s0)
   10184:	02078863          	beqz	a5,101b4 <main+0x160>
   10188:	fd442783          	lw	a5,-44(s0)
   1018c:	02078463          	beqz	a5,101b4 <main+0x160>
   10190:	fe042023          	sw	zero,-32(s0)
   10194:	00100793          	li	a5,1
   10198:	fef42223          	sw	a5,-28(s0)
   1019c:	fe442783          	lw	a5,-28(s0)
   101a0:	00379793          	slli	a5,a5,0x3
   101a4:	fef42623          	sw	a5,-20(s0)
   101a8:	fe042783          	lw	a5,-32(s0)
   101ac:	00479793          	slli	a5,a5,0x4
   101b0:	fef42423          	sw	a5,-24(s0)
   101b4:	fec42783          	lw	a5,-20(s0)
   101b8:	fe842703          	lw	a4,-24(s0)
   101bc:	fdc42683          	lw	a3,-36(s0)
   101c0:	00df7f33          	and	t5,t5,a3
   101c4:	00ff6f33          	or	t5,t5,a5
   101c8:	00ef6f33          	or	t5,t5,a4
   101cc:	00000793          	li	a5,0
   101d0:	00078513          	mv	a0,a5
   101d4:	02c12403          	lw	s0,44(sp)
   101d8:	03010113          	addi	sp,sp,48
   101dc:	00008067          	ret
```

### UNIQUE INSTRUCTION

```
Number of different instructions: 13
List of unique instructions:
sw
and
bnez
slli
j
li
mv
or
andi
ret
addi
lw
beqz
```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/1d85b3a4-df09-47b3-9012-a88426a46af3)




### SPIKE SIMULATION

**Code**

```
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
		printf("Entering While Loop");
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
		printf("Reseting the sensor values");
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
		
		sensorValue = 1;
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
```

Use the following command to simulate the C code using spike:

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out check.c
spike pk out
```

The code consist of 3 inputs (for reset, IR sensor, water sensor) and two outputs. Reset input sets the output to zero. Whenever the IR sensor detects any object in its path the buzzer starts beeping similarly when water sensor detects water it breaks the circuit and hence transmit zero to the processor and hence the second buzzer starts beeping
We will go through each condition and verify it using the spike simulation.

**Condition 1** When Reset = 1 <br>

When reset = 1 the sensor values are not taken into consideration and outputs will be forced to zero.

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/28853f7c-a5b8-4b6f-ab4f-85f1a037142d)




**Condition 2** When Reset =0, IR sensor = 1, Water sensor = 1 <br>

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/e0eee547-50b8-4d38-b539-231e951f8303)



**Condition 3** when Reset =0, IR sensor = 0, water sensor = 1 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/a1ea7707-e8a0-41ee-8093-627a40a12883)



**Condition 4** when Reset =0, IR sensor = 1, water sensor = 0 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/87d12c72-0c98-4999-b33f-7a232de74c64)



**Condition 5** when Reset =0, IR sensor = 0, water sensor = 0 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/353924f3-ef48-4595-b056-47e1835a52a9)



### FUNCTIONAL SIMULATION USING GTKWAVE



**Condition 1** When Reset = 1 <br>


In this example, the initial input condition was "100" which was changed after 1000 unit of time and was updated to "101" which was read in the same cycle and stored in a5 register as shown below:

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/4878b935-e6c3-415c-b14f-3f1988d5b70b)

The expected output is "00" which is updated when the instruction is **101c4:	00ff6f33      or    t5,t5,a5** which OR's the value of a5 register with the previous value of t5.

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/459c4a57-b33a-4951-9573-75a5ccb963b4)

<br>

Simulation Results

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/b8012490-ea2f-4628-8e70-1ca973d01a41)



**Condition 2** When Reset =0, IR sensor = 1, Water sensor = 1 <br>

Similar to the above conditions the oupt values are updated at the instruction  **101c8:	00ef6f33          	or	t5,t5,a4**  which OR's the value of a4 (which stores the value of stack pointer at **101b8:	fe842703          	lw	a4,-24(s0)**) register with the previous value of t5.

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/faf5f24d-f2e0-49ae-b2fb-e087d6b52512)

Simulation Resuls:
![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/cd1ad4d1-9bf2-4d90-8285-8abe9afae598)



**Condition 3** when Reset =0, IR sensor = 0, water sensor = 1 

Similarl to the above condition the output is updated in the same instruction

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/c5ea00cc-d981-4a6b-a666-5bc8af0d4b09)

Simulation Results:

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/adb122a5-d622-4a48-a2fc-b28878c32675)



**Condition 4** when Reset =0, IR sensor = 1, water sensor = 0 

Similarl to the above condition the output is updated in the same instruction

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/c0b4ea68-de2f-4dbb-b3b3-f2a3a7c60a2e)


Simulation Results:

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/e2829662-65e9-4d19-b96e-043c4c08fead)


**Condition 5** when Reset =0, IR sensor = 0, water sensor = 0 


Similarl to the above condition the output is updated in the same instruction

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/ee8d351e-30a9-46f5-a53a-de7e3dd4ecd2)


Simulation Results:


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/ad085f40-7950-4351-9d69-a7a9ec05a216)





### GATE LEVEL SYNTHESIS AND SIMULATION

In our gate-level synthesis process, we've utilized the Yosys tool in conjunction with the "sky130_fd_sc_hd__tt_025C_1v80_256.lib" library, which has been integrated with SRAM cells.<br>
To generate the synthesized netlist, the initial steps involve temporarily excluding the data and instruction memory modules by commenting them out, followed by the following steps:

```
$ yosys
yosys> read_liberty -lib lib/sky130_fd_sc_hd__tt_025C_1v80_512.lib
yosys> read_verilog processor.v
yosys> synth -top wrapper
yosys> dfflibmap -liberty lib/sky130_fd_sc_hd__tt_025C_1v80_512.lib
yosys> abc -liberty lib/sky130_fd_sc_hd__tt_025C_1v80_512.lib
yosys> write_verilog synth_asic.v
```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/5a52644e-bf29-4cce-a3a2-4d8d0b52004b)

In the above image we can see that there are two sram cells mapped in the netlist.
<br>
To validate the UART functionality in this netlist, we ensure that in the "processor.v" file, the variable "writing_inst_done" is set to 1 to exclude the UART module during simulation, followed by the following steps:

```
$ yosys
yosys> read_liberty -lib lib/sky130_fd_sc_hd__tt_025C_1v80_512.lib
yosys> read_verilog processor.v
yosys> synth -top wrapper
yosys> dfflibmap -liberty lib/sky130_fd_sc_hd__tt_025C_1v80_512.lib
yosys> abc -liberty lib/sky130_fd_sc_hd__tt_025C_1v80_512.lib
yosys> write_verilog synth_test.v
```
This will create the netlist for UART functionality.
<br>

To verify the functionality of the GLS using the iverilog command which includes sram modules and related sky130 primitives.
**Commands**


```
iverilog -o test testbench.v synth_test.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v
./test
gtkwave waveform.vcd &
```

**Condition 1** When Reset = 1 <br>



![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/51ee1707-9a64-465e-8e13-ec289973315b)




**Condition 2** When Reset =0, IR sensor = 1, Water sensor = 1 <br>


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/2f3fc68f-756c-4c96-8aba-68225c7868b1)




**Condition 3** when Reset =0, IR sensor = 0, water sensor = 1 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/a3d2d950-7177-4537-8467-b998a172a409)




**Condition 4** when Reset =0, IR sensor = 1, water sensor = 0 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/1f561f49-bfaa-4807-9e21-e2c47b0e5eef)




**Condition 5** when Reset =0, IR sensor = 0, water sensor = 0 

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/6e0315aa-2d8a-48c5-9b4a-cb768a17acb4)


## PHYSICAL DESIGN USING OPENLANE

**OpenLane** : OpenLane is a groundbreaking open-source ASIC (Application-Specific Integrated Circuit) design flow that has transformed the landscape of custom chip development. Developed under the aegis of the SkyWater PDK project, sponsored by Google, OpenLane represents a paradigm shift in the world of integrated circuit design. This powerful tool automates and streamlines the entire ASIC design process, from RTL (Register Transfer Level) design to GDSII file generation, making it accessible to a wider audience while significantly reducing design cycle times.


**MAGIC** 
Magic is a venerable VLSI layout tool, written in the 1980's at Berkeley by John Ousterhout, now famous primarily for writing the scripting interpreter language Tcl. Due largely in part to its liberal Berkeley open-source license, magic has remained popular with universities and small companies. The open-source license has allowed VLSI engineers with a bent toward programming to implement clever ideas and help magic stay abreast of fabrication technology. However, it is the well thought-out core algorithms which lend to magic the greatest part of its popularity. Magic is widely cited as being the easiest tool to use for circuit layout, even for people who ultimately rely on commercial tools for their product design flow.


### Placement And Routing

**Steps to invoke openlane and prepare the design**

```
make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design project
```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/c4d290fe-def9-47d3-b179-7ba39b5c1a3c)


**Steps to Synthesize the design**

```
run_synthesis
```


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/a25a4b51-32a2-4859-b3fb-a0dbe7201a1d)



Synthesis Report:

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/e09ad9e7-a20b-426c-a3d9-f8d7f202a445)




**Steps For Floorplanning**


```
% run_floorplan
```


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/eed32328-89eb-4403-a120-cedf96e0a791)



We can check the layout with magic with the following command :

```
magic -T /home/nancy/OpenLane/vsdstdcelldesign/libs/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def
```


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/f43dda97-792d-4abe-a393-6f6b8081c064)




**Die Area**


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/15d91c70-ae3a-458b-ad19-a3ddbbadd058)






**Core Area**



![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/b3ad23f9-540e-4f0d-9c25-2a5b4db90d11)






### Placement

Placement refers to the process of determining the physical locations of various components on the chip's surface. This step is crucial in the overall ASIC design flow, and it comes after the initial stages of logic synthesis and before routing.
ecide where on the chip's surface each standard cell or block of logic will be physically located. The goal is to optimize the arrangement for factors such as speed, power consumption, and area utilization. Good placement can lead to improved performance and ease of routing in the subsequent steps.
- Global Placement: Initially, a rough assignment of cells to regions of the chip is performed. This is a high-level placement that sets the stage for the detailed placement.
- Detailed Placement: Fine-tune the positions of individual cells within the assigned regions. This step takes into account various factors like interconnectivity, signal delays, and power distribution.


**Steps**

```
% run_placement
```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/34aa2cf4-153c-4269-9251-186737b1bd85)



We can check the layout with magic with the following command :

```
magic -T /home/nancy/OpenLane/vsdstdcelldesign/libs/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def
```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/a8d513c0-0eab-46fe-a5ee-b97a1ec36059)


### Clock Tree Synthesis

ChatGPT

Clock Tree Synthesis (CTS) focuses on designing an efficient and optimized clock distribution network within the chip. The primary goal of CTS is to ensure that the clock signal reaches all elements of the design with minimal skew, jitter, and power consumption. 
In the initial phase of CTS, a global clock distribution network is created. This involves identifying clock source(s) and distributing the clock signal to major regions of the chip. The tool considers constraints like skew, insertion delay, and the overall topology of the clock tree.

```
% run_cts
```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/fbb3f2eb-ba0c-4f70-abe2-e133c04459fd)


### Timing Report

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/c500b49d-d64c-4743-9125-8b1760596dec)


### Area Report

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/44e1d6ed-50a6-4275-b6bc-5751bdcf9813)



### Skew Report

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/81c1d1a9-7831-47d7-a1b6-044dce29fbd1)




### Power Report

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/91b511ac-8152-4263-a0ae-f21169ff54a1)





### Routing

Routing involves creating the physical connections between the placed components on the chip. The primary goal of routing is to implement the logical connections specified in the netlist while adhering to design rules, timing constraints, and other considerations. <br>
In the global routing phase, high-level metal tracks or routing channels are established to connect major sections of the chip. This involves defining the paths for power, clock, and other global signals. <br>
Detailed routing is the more fine-grained phase where individual wires or metal traces are added to connect specific components based on the netlist. This involves navigating around obstacles, avoiding congested areas, and adhering to design rules. <br>


**Steps**

```
% run_routing
```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/33a44849-df03-4db7-9853-8ca3cf69e24e)



### Layout After Routing

**Steps**

```

magic -T /home/nancy/OpenLane/vsdstdcelldesign/libs/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def
```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/1fa1f619-738c-42cf-9395-8f1c8c6bcbbb)



**Layout**


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/9beb0d47-76bf-4a62-920d-6ecf81a1a327)


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/ca37807e-2565-4ef3-9fb9-67a03439bd08)





### Post-Routing Timing Report

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/b17e4cfe-9466-4a02-8dee-75db88ccb62b)




### Post-Routing Area Report

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/d164362f-9f34-4e9e-80d7-1c82caa0e71d)


### Post-Routing Power Report

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/75c602a0-e986-4a81-ba92-3b23c674da50)


### Performance Calculation:

Given a Clock period of 50ns in Json file , setup slack we got after routing is 12.95ns
```
                              1
Max Performance =  ------------------------
                     clock period - slack(setup)

```
```
Max Performance = 0.026990 Ghz

```


## OpenLane Interactive Flow

```
cd Desktop/OpenLane/ 

./flow.tcl -interactive
package require openlane 0.9
prep -design picorv32a
run_synthesis
run_floorplan
run_placement
run_cts
gen_pdn
run_routing
run_magic
run_magic_spice_export
run_magic_drc
run_antenna_check
```


## ACKNOWLEDMENT

- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Mayank Kabra (Founder, Chipcron Pvt. Ltd.)
  


## REFERENCES

- https://github.com/SakethGajawada/RISCV-GNU
- https://github.com/The-OpenROAD-Project/OpenLane








