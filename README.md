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
void delay(int);



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

        delay(1000);  // Delay between readings
    }

    return 0;
}


void delay(int milliseconds) {
    for (int i = 0; i < milliseconds; i++) {
        for (int j = 0; j < 10000; j++) {
            // Adjust the loop count based on your microcontroller's speed
        }
    }
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
Disassembly of section .text:

00010074 <main>:
   10074:	fc010113          	add	sp,sp,-64
   10078:	02112e23          	sw	ra,60(sp)
   1007c:	02812c23          	sw	s0,56(sp)
   10080:	04010413          	add	s0,sp,64
   10084:	fe042623          	sw	zero,-20(s0)
   10088:	fe042423          	sw	zero,-24(s0)
   1008c:	fec42783          	lw	a5,-20(s0)
   10090:	00379793          	sll	a5,a5,0x3
   10094:	fef42223          	sw	a5,-28(s0)
   10098:	fe842783          	lw	a5,-24(s0)
   1009c:	00479793          	sll	a5,a5,0x4
   100a0:	fef42023          	sw	a5,-32(s0)
   100a4:	fe442783          	lw	a5,-28(s0)
   100a8:	fe042703          	lw	a4,-32(s0)
   100ac:	00ff6f33          	or	t5,t5,a5
   100b0:	00ef6f33          	or	t5,t5,a4
   100b4:	001f7793          	and	a5,t5,1
   100b8:	fcf42e23          	sw	a5,-36(s0)
   100bc:	fdc42783          	lw	a5,-36(s0)
   100c0:	02078a63          	beqz	a5,100f4 <main+0x80>
   100c4:	fe042623          	sw	zero,-20(s0)
   100c8:	fe042423          	sw	zero,-24(s0)
   100cc:	fec42783          	lw	a5,-20(s0)
   100d0:	00379793          	sll	a5,a5,0x3
   100d4:	fef42223          	sw	a5,-28(s0)
   100d8:	fe842783          	lw	a5,-24(s0)
   100dc:	00479793          	sll	a5,a5,0x4
   100e0:	fef42023          	sw	a5,-32(s0)
   100e4:	fe442783          	lw	a5,-28(s0)
   100e8:	fe042703          	lw	a4,-32(s0)
   100ec:	00ff6f33          	or	t5,t5,a5
   100f0:	00ef6f33          	or	t5,t5,a4
   100f4:	002f7793          	and	a5,t5,2
   100f8:	fcf42c23          	sw	a5,-40(s0)
   100fc:	fd842783          	lw	a5,-40(s0)
   10100:	01f7d713          	srl	a4,a5,0x1f
   10104:	00f707b3          	add	a5,a4,a5
   10108:	4017d793          	sra	a5,a5,0x1
   1010c:	fcf42a23          	sw	a5,-44(s0)
   10110:	fd442783          	lw	a5,-44(s0)
   10114:	02079263          	bnez	a5,10138 <main+0xc4>
   10118:	00100793          	li	a5,1
   1011c:	fef42423          	sw	a5,-24(s0)
   10120:	fe842783          	lw	a5,-24(s0)
   10124:	00479793          	sll	a5,a5,0x4
   10128:	fef42023          	sw	a5,-32(s0)
   1012c:	fe042783          	lw	a5,-32(s0)
   10130:	00ff6f33          	or	t5,t5,a5
   10134:	0240006f          	j	10158 <main+0xe4>
   10138:	fd442783          	lw	a5,-44(s0)
   1013c:	00078e63          	beqz	a5,10158 <main+0xe4>
   10140:	fe042423          	sw	zero,-24(s0)
   10144:	fe842783          	lw	a5,-24(s0)
   10148:	00479793          	sll	a5,a5,0x4
   1014c:	fef42023          	sw	a5,-32(s0)
   10150:	fe042783          	lw	a5,-32(s0)
   10154:	00ff6f33          	or	t5,t5,a5
   10158:	003f7793          	and	a5,t5,3
   1015c:	fcf42823          	sw	a5,-48(s0)
   10160:	fd042783          	lw	a5,-48(s0)
   10164:	41f7d713          	sra	a4,a5,0x1f
   10168:	00377713          	and	a4,a4,3
   1016c:	00f707b3          	add	a5,a4,a5
   10170:	4027d793          	sra	a5,a5,0x2
   10174:	fcf42623          	sw	a5,-52(s0)
   10178:	fcc42783          	lw	a5,-52(s0)
   1017c:	02078263          	beqz	a5,101a0 <main+0x12c>
   10180:	00100793          	li	a5,1
   10184:	fef42623          	sw	a5,-20(s0)
   10188:	fec42783          	lw	a5,-20(s0)
   1018c:	00379793          	sll	a5,a5,0x3
   10190:	fef42223          	sw	a5,-28(s0)
   10194:	fe442783          	lw	a5,-28(s0)
   10198:	00ff6f33          	or	t5,t5,a5
   1019c:	0240006f          	j	101c0 <main+0x14c>
   101a0:	fcc42783          	lw	a5,-52(s0)
   101a4:	00079e63          	bnez	a5,101c0 <main+0x14c>
   101a8:	fe042623          	sw	zero,-20(s0)
   101ac:	fec42783          	lw	a5,-20(s0)
   101b0:	00379793          	sll	a5,a5,0x3
   101b4:	fef42223          	sw	a5,-28(s0)
   101b8:	fe442783          	lw	a5,-28(s0)
   101bc:	00ff6f33          	or	t5,t5,a5
   101c0:	3e800513          	li	a0,1000
   101c4:	008000ef          	jal	101cc <delay>
   101c8:	eedff06f          	j	100b4 <main+0x40>

000101cc <delay>:
   101cc:	fd010113          	add	sp,sp,-48
   101d0:	02812623          	sw	s0,44(sp)
   101d4:	03010413          	add	s0,sp,48
   101d8:	fca42e23          	sw	a0,-36(s0)
   101dc:	fe042623          	sw	zero,-20(s0)
   101e0:	0340006f          	j	10214 <delay+0x48>
   101e4:	fe042423          	sw	zero,-24(s0)
   101e8:	0100006f          	j	101f8 <delay+0x2c>
   101ec:	fe842783          	lw	a5,-24(s0)
   101f0:	00178793          	add	a5,a5,1
   101f4:	fef42423          	sw	a5,-24(s0)
   101f8:	fe842703          	lw	a4,-24(s0)
   101fc:	000027b7          	lui	a5,0x2
   10200:	70f78793          	add	a5,a5,1807 # 270f <main-0xd965>
   10204:	fee7d4e3          	bge	a5,a4,101ec <delay+0x20>
   10208:	fec42783          	lw	a5,-20(s0)
   1020c:	00178793          	add	a5,a5,1
   10210:	fef42623          	sw	a5,-20(s0)
   10214:	fec42703          	lw	a4,-20(s0)
   10218:	fdc42783          	lw	a5,-36(s0)
   1021c:	fcf744e3          	blt	a4,a5,101e4 <delay+0x18>
   10220:	00000013          	nop
   10224:	00000013          	nop
   10228:	02c12403          	lw	s0,44(sp)
   1022c:	03010113          	add	sp,sp,48
   10230:	00008067          	ret
```

### UNIQUE INSTRUCTION

```
Number of different instructions: 18
List of unique instructions:
srl
and
sw
or
beqz
jal
sll
j
bge
nop
lw
sra
bnez
li
blt
ret
lui
add
```


![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/d7d0d9cd-c769-4031-99ad-34709ede0005)



