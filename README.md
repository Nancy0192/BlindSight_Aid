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

int main() {
	int sensorValue;
	int reset;
	int watersensor;
	int buzzer = 0;
	int buzzer_2 = 0;


	int buzzer_reg, buzzer_2_reg;
	buzzer_reg = buzzer*8;
        buzzer_2_reg = buzzer_2*16;
	asm volatile(
	"or x30, x30,%0 \n\t"
	"or x30, x30,%1 \n\t"
	: 
	:"r"(buzzer_reg),"r"(buzzer_2_reg)
	:"x30"
	);


    while (1) {
	
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
        asm volatile(
	"or x30, x30,%0 \n\t"
	"or x30, x30,%1 \n\t"
	:
	:"r"(buzzer_reg),"r"(buzzer_2_reg)
	:"x30"
	);
    	}
	int water_reg;

	asm volatile(
	"andi %0, x30, 2\n\t"
	:"=r"(water_reg)
	:
	:
	);
    	
	watersensor = water_reg/2;
    	
    	if (!watersensor){
    		
    		buzzer_2 = 1;
       		buzzer_2_reg = buzzer_2*16;

		asm volatile(
		"or x30, x30,%0 \n\t"
		:
		:"r"(buzzer_2_reg)
		:"x30"
		);
    		
    		
    	}
    	
    	else if(watersensor){
    	
    		buzzer_2 = 0;
       		buzzer_2_reg = buzzer_2*16;

		asm volatile(
		"or x30, x30,%0 \n\t"
		:
		:"r"(buzzer_2_reg)
		:"x30"
		);
    	
    	}

	int ir_sensor_reg;
    	asm volatile(
	"andi %0, x30, 3\n\t"
	:"=r"(ir_sensor_reg)
	:
	:
	);

	sensorValue = ir_sensor_reg/4;
        
        if (sensorValue) {
        	buzzer = 1;
		buzzer_reg = buzzer*8;
		asm volatile(
	 	"or x30, x30,%0 \n\t"
	 	:
		:"r"(buzzer_reg)
		:"x30"
		);

        } else if (!sensorValue){
        	buzzer =0;
		buzzer_reg = buzzer*8;
		asm volatile(
	 	"or x30, x30,%0 \n\t"
	 	:
		:"r"(buzzer_reg)
		:"x30"
		);

        }
    }

    return 0;
}

```

### GCC COMPILER RESULTS

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/5893aa19-f7ed-4693-b1c5-a88f4308b969)


### ASSEMBLY STRUCTURE

Commands to convert C code into assmbly code using RISC-V 

```
/home/nancy/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o ./out blindsight_aid.c
/home/nancy/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d -r out > assembly.txt

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
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fe042423          	sw	zero,-24(s0)
   10068:	fec42783          	lw	a5,-20(s0)
   1006c:	00379793          	slli	a5,a5,0x3
   10070:	fef42223          	sw	a5,-28(s0)
   10074:	fe842783          	lw	a5,-24(s0)
   10078:	00479793          	slli	a5,a5,0x4
   1007c:	fef42023          	sw	a5,-32(s0)
   10080:	fe442783          	lw	a5,-28(s0)
   10084:	fe042703          	lw	a4,-32(s0)
   10088:	00ff6f33          	or	t5,t5,a5
   1008c:	00ef6f33          	or	t5,t5,a4
   10090:	001f7793          	andi	a5,t5,1
   10094:	fcf42e23          	sw	a5,-36(s0)
   10098:	fdc42783          	lw	a5,-36(s0)
   1009c:	02078a63          	beqz	a5,100d0 <main+0x7c>
   100a0:	fe042623          	sw	zero,-20(s0)
   100a4:	fe042423          	sw	zero,-24(s0)
   100a8:	fec42783          	lw	a5,-20(s0)
   100ac:	00379793          	slli	a5,a5,0x3
   100b0:	fef42223          	sw	a5,-28(s0)
   100b4:	fe842783          	lw	a5,-24(s0)
   100b8:	00479793          	slli	a5,a5,0x4
   100bc:	fef42023          	sw	a5,-32(s0)
   100c0:	fe442783          	lw	a5,-28(s0)
   100c4:	fe042703          	lw	a4,-32(s0)
   100c8:	00ff6f33          	or	t5,t5,a5
   100cc:	00ef6f33          	or	t5,t5,a4
   100d0:	002f7793          	andi	a5,t5,2
   100d4:	fcf42c23          	sw	a5,-40(s0)
   100d8:	fd842783          	lw	a5,-40(s0)
   100dc:	01f7d713          	srli	a4,a5,0x1f
   100e0:	00f707b3          	add	a5,a4,a5
   100e4:	4017d793          	srai	a5,a5,0x1
   100e8:	fcf42a23          	sw	a5,-44(s0)
   100ec:	fd442783          	lw	a5,-44(s0)
   100f0:	02079263          	bnez	a5,10114 <main+0xc0>
   100f4:	00100793          	li	a5,1
   100f8:	fef42423          	sw	a5,-24(s0)
   100fc:	fe842783          	lw	a5,-24(s0)
   10100:	00479793          	slli	a5,a5,0x4
   10104:	fef42023          	sw	a5,-32(s0)
   10108:	fe042783          	lw	a5,-32(s0)
   1010c:	00ff6f33          	or	t5,t5,a5
   10110:	0240006f          	j	10134 <main+0xe0>
   10114:	fd442783          	lw	a5,-44(s0)
   10118:	00078e63          	beqz	a5,10134 <main+0xe0>
   1011c:	fe042423          	sw	zero,-24(s0)
   10120:	fe842783          	lw	a5,-24(s0)
   10124:	00479793          	slli	a5,a5,0x4
   10128:	fef42023          	sw	a5,-32(s0)
   1012c:	fe042783          	lw	a5,-32(s0)
   10130:	00ff6f33          	or	t5,t5,a5
   10134:	003f7793          	andi	a5,t5,3
   10138:	fcf42823          	sw	a5,-48(s0)
   1013c:	fd042783          	lw	a5,-48(s0)
   10140:	41f7d713          	srai	a4,a5,0x1f
   10144:	00377713          	andi	a4,a4,3
   10148:	00f707b3          	add	a5,a4,a5
   1014c:	4027d793          	srai	a5,a5,0x2
   10150:	fcf42623          	sw	a5,-52(s0)
   10154:	fcc42783          	lw	a5,-52(s0)
   10158:	02078263          	beqz	a5,1017c <main+0x128>
   1015c:	00100793          	li	a5,1
   10160:	fef42623          	sw	a5,-20(s0)
   10164:	fec42783          	lw	a5,-20(s0)
   10168:	00379793          	slli	a5,a5,0x3
   1016c:	fef42223          	sw	a5,-28(s0)
   10170:	fe442783          	lw	a5,-28(s0)
   10174:	00ff6f33          	or	t5,t5,a5
   10178:	f19ff06f          	j	10090 <main+0x3c>
   1017c:	fcc42783          	lw	a5,-52(s0)
   10180:	f00798e3          	bnez	a5,10090 <main+0x3c>
   10184:	fe042623          	sw	zero,-20(s0)
   10188:	fec42783          	lw	a5,-20(s0)
   1018c:	00379793          	slli	a5,a5,0x3
   10190:	fef42223          	sw	a5,-28(s0)
   10194:	fe442783          	lw	a5,-28(s0)
   10198:	00ff6f33          	or	t5,t5,a5
   1019c:	ef5ff06f          	j	10090 <main+0x3c>
```

### UNIQUE INSTRUCTION

```
Number of different instructions: 9
List of unique instructions:
j
sw
addi
bne
lw
andi
li
or
slli
```


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/50f76fc1-7223-44d7-8389-1dec27707608)




