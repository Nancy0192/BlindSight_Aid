# BlindSight_Aid

This repository contains RISC-V based blind sight aid.


## AIM
Navigating the world independently is a fundamental human right, yet visually impaired individuals face significant challenges in mobility and safety. This advanced assistive device aims to empower visually impaired individuals by enhancing their spatial awareness, obstacle detection, and overall confidence while navigating unfamiliar environments.
We will be using RISC-V to build the device and the sensor for that partiular functionality.


## BLOCK DIAGRAM OF THE BLIND STICK


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/7af45170-4c66-4a9c-a066-b5cd7773b6ca)





## ASSEMBLY CODE GENERATION
We will be using RISC-V GNU Toolchain to convert our C code into assembly code. Let us first go through the RISC-V:

### RISC-V TOOLCHAIN
RISC-V is an open-source instruction set architecture (ISA) used for the development of custom processors targeting a variety of end applications.RISC-V ISA is considered the fifth generation of processors built on the concept of the reduced instruction set computer (RISC). Due to its openness and its technical merits, it has become very popular in recent years. The royalty-free RISC-V ISA features a small core set of instructions upon which all the design’s software runs. Its optional extensions allow designers to tailor the architecture for a variety of different end markets. Essentially, the RISC-V architecture allows designers to customize and build their processor in a way that’s tailored to their target end applications, so they can optimize the power, performance, and area (PPA) for those applications. The RISC-V ISA also provides the flexibility to pick and choose from available features, rather than having to use the full feature set. 
The GNU compile toolchain is a set of programming tools in LINUX system that can be use for compiling a code to generate certain executable program, library and debugger and whose detail can be found in references. RISC-V is one such toolchain which supports C and C++ cross compiler. It supports two build modes: a generic ELF/Newlib toolchain and a more sophisticated Linux-ELF/glibc toolchain and the github link for the same can be found in references.

### C Code

```

//#include <stdio.h>
//#define IR_SENSOR_PIN 17  // Replace with the actual GPIO pin number

int sensorValue;
int reset;
int LDR;
int push_button_LDR;
int watersensor;
int buzzer = 0;
int buzzer_2 = 0;
int buzzer_3 = 0;


void delay(int milliseconds) {
    for (int i = 0; i < milliseconds; i++) {
        for (int j = 0; j < 10000; j++) {
            // Adjust the loop count based on your microcontroller's speed
        }
    }
}


int main() {


  //  pinMode(IR_SENSOR_PIN, INPUT);

    while (1) {
    	if (reset)
    	{
    	buzzer =0;
        buzzer_2 =0;
        buzzer_3 = 0;
    	}
    	
    	
    	if (!LDR){
    		
    		buzzer_2 = 1;
    		if (push_button_LDR)
    		{
    		buzzer=1;
    		}
    		
    		
    	}
    	
    	if (!watersensor){
    		
    		buzzer_3 = 1;
    		
    	}
    	
    	
        
        if (sensorValue) {
        	buzzer = 1;
            // Object detected, take appropriate action
           // printf("Object Detected!\n");
            // Implement your code here for what to do when an object is detected.
        } else {
        	buzzer =0;
            // No object detected
            //printf("No Object Detected\n");
            // Implement your code here for what to do when no object is detected.
        }

        delay(1000);  // Delay between readings
    }

    return 0;
}




```

### ASSEMBLY STRUCTURE

Commands to convert C code into assmbly code using RISC-V 

```
riscv64-unknown-elf-gcc -O1 -mabi=ilp32 -march=rv32i -o final_code.o final_code.c
```

### GPIO

```
x30[0] is an input pin for IR sensor to detect the object.
x30[1]  is an input pin used as a restart trigger.
x30[2] is an input pin used for LDR to check the light.
x30[3] is an input pin used for water detection.
x30[4] is an output pin used to indicate about the object detection.
x30[5] is an output pin used to indicate about the water detection. 
x30[6] is an output pin used to indicate about the light detection.
x30[7] is an output pin used when there is no light.
```




### ASSEMBLY CODE


```
Disassembly of section .text:

00000000 <delay>:
   0:	fd010113          	add	sp,sp,-48
   4:	02812623          	sw	s0,44(sp)
   8:	03010413          	add	s0,sp,48
   c:	fca42e23          	sw	a0,-36(s0)
  10:	fe042623          	sw	zero,-20(s0)
  14:	0340006f          	j	48 <.L2>

00000018 <.L5>:
  18:	fe042423          	sw	zero,-24(s0)
  1c:	0100006f          	j	2c <.L3>

00000020 <.L4>:
  20:	fe842783          	lw	a5,-24(s0)
  24:	00178793          	add	a5,a5,1
  28:	fef42423          	sw	a5,-24(s0)

0000002c <.L3>:
  2c:	fe842703          	lw	a4,-24(s0)
  30:	000027b7          	lui	a5,0x2
  34:	70f78793          	add	a5,a5,1807 # 270f <.L11+0x260b>
  38:	fee7d4e3          	bge	a5,a4,20 <.L4>
  3c:	fec42783          	lw	a5,-20(s0)
  40:	00178793          	add	a5,a5,1
  44:	fef42623          	sw	a5,-20(s0)

00000048 <.L2>:
  48:	fec42703          	lw	a4,-20(s0)
  4c:	fdc42783          	lw	a5,-36(s0)
  50:	fcf744e3          	blt	a4,a5,18 <.L5>
  54:	00000013          	nop
  58:	00000013          	nop
  5c:	02c12403          	lw	s0,44(sp)
  60:	03010113          	add	sp,sp,48
  64:	00008067          	ret

00000068 <main>:
  68:	ff010113          	add	sp,sp,-16
  6c:	00112623          	sw	ra,12(sp)
  70:	00812423          	sw	s0,8(sp)
  74:	01010413          	add	s0,sp,16

00000078 <.L12>:
  78:	000007b7          	lui	a5,0x0
  7c:	0007a783          	lw	a5,0(a5) # 0 <delay>
  80:	00078a63          	beqz	a5,94 <.L7>
  84:	000007b7          	lui	a5,0x0
  88:	0007a023          	sw	zero,0(a5) # 0 <delay>
  8c:	000007b7          	lui	a5,0x0
  90:	0007a023          	sw	zero,0(a5) # 0 <delay>

00000094 <.L7>:
  94:	000007b7          	lui	a5,0x0
  98:	0007a783          	lw	a5,0(a5) # 0 <delay>
  9c:	02079463          	bnez	a5,c4 <.L8>
  a0:	000007b7          	lui	a5,0x0
  a4:	00100713          	li	a4,1
  a8:	00e7a023          	sw	a4,0(a5) # 0 <delay>
  ac:	000007b7          	lui	a5,0x0
  b0:	0007a783          	lw	a5,0(a5) # 0 <delay>
  b4:	00078863          	beqz	a5,c4 <.L8>
  b8:	000007b7          	lui	a5,0x0
  bc:	00100713          	li	a4,1
  c0:	00e7a023          	sw	a4,0(a5) # 0 <delay>

000000c4 <.L8>:
  c4:	000007b7          	lui	a5,0x0
  c8:	0007a783          	lw	a5,0(a5) # 0 <delay>
  cc:	00079863          	bnez	a5,dc <.L9>
  d0:	000007b7          	lui	a5,0x0
  d4:	00100713          	li	a4,1
  d8:	00e7a023          	sw	a4,0(a5) # 0 <delay>

000000dc <.L9>:
  dc:	000007b7          	lui	a5,0x0
  e0:	0007a703          	lw	a4,0(a5) # 0 <delay>
  e4:	00100793          	li	a5,1
  e8:	00f71a63          	bne	a4,a5,fc <.L10>
  ec:	000007b7          	lui	a5,0x0
  f0:	00100713          	li	a4,1
  f4:	00e7a023          	sw	a4,0(a5) # 0 <delay>
  f8:	00c0006f          	j	104 <.L11>

000000fc <.L10>:
  fc:	000007b7          	lui	a5,0x0
 100:	0007a023          	sw	zero,0(a5) # 0 <delay>

00000104 <.L11>:
 104:	3e800513          	li	a0,1000
 108:	00000097          	auipc	ra,0x0
 10c:	000080e7          	jalr	ra # 108 <.L11+0x4>
 110:	f69ff06f          	j	78 <.L12>
```

### UNIQUE INSTRUCTION

```
Number of different instructions: 15
List of unique instructions:
bge
add
lui
ret
nop
li
blt
beqz
auipc
lw
sw
bnez
bne
jalr
j    

```


