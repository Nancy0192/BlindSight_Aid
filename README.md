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



int sensorValue;
int reset;
int watersensor;
int buzzer = 0;
int buzzer_2 = 0;


void delay(int milliseconds) {
    for (int i = 0; i < milliseconds; i++) {
        for (int j = 0; j < 10000; j++) {
            // Adjust the loop count based on your microcontroller's speed
        }
    }
}


int main() {

	int buzzer_reg, buzzer_2_reg;
	buzzer_reg = buzzer*8;
        buzzer_2_reg = buzzer_2*16;
	asm(
	"or x30, x30,%0 \n\t"
	"or x30, x30,%1 \n\t" 
	:"=r"(buzzer_reg),"=r"(buzzer_2_reg));


    while (1) {
	
    	asm(
	"andi %0, x30, 1\n\t"
	:"=r"(reset));
    	if (reset)
    	{
    	buzzer =0;
        buzzer_2 =0;
	buzzer_reg = buzzer*8;
        buzzer_2_reg = buzzer_2*16;
        asm(
	"or x30, x30,%0 \n\t"
	"or x30, x30,%1 \n\t"
	:"=r"(buzzer_reg),"=r"(buzzer_2_reg));
    	}
	int water_reg;

	asm(
	"andi %0, x30, 2\n\t"
	:"=r"(water_reg));
    	
	watersensor = water_reg/2;
    	
    	if (!watersensor){
    		
    		buzzer_2 = 1;
       		buzzer_2_reg = buzzer_2*16;

		asm(
		"or x30, x30,%0 \n\t"
		:"=r"(buzzer_2_reg));
    		
    		
    	}

	int ir_sensor_reg;
    	asm(
	"andi %0, x30, 3\n\t"
	:"=r"(ir_sensor_reg));

	sensorValue = ir_sensor_reg/4;
        
        if (sensorValue) {
        	buzzer = 1;
		buzzer_reg = buzzer*8;
		asm(
	 	"or x30, x30,%0 \n\t"
		:"=r"(buzzer_reg));

        } else {
        	buzzer =0;
		buzzer_reg = buzzer*8;
		asm(
	 	"or x30, x30,%0 \n\t"
		:"=r"(buzzer_reg));

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
x30[2] is an input pin used for water detection.
x30[3] is an output pin used to indicate about the object detection.
x30[4] is an output pin used to indicate about the water detection. 
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
  34:	70f78793          	add	a5,a5,1807 # 270f <.L10+0x253f>
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
  68:	fe010113          	add	sp,sp,-32
  6c:	00112e23          	sw	ra,28(sp)
  70:	00812c23          	sw	s0,24(sp)
  74:	02010413          	add	s0,sp,32
  78:	000007b7          	lui	a5,0x0
  7c:	0007a783          	lw	a5,0(a5) # 0 <delay>
  80:	00379793          	sll	a5,a5,0x3
  84:	fef42623          	sw	a5,-20(s0)
  88:	000007b7          	lui	a5,0x0
  8c:	0007a783          	lw	a5,0(a5) # 0 <delay>
  90:	00479793          	sll	a5,a5,0x4
  94:	fef42423          	sw	a5,-24(s0)
  98:	00ef6f33          	or	t5,t5,a4
  9c:	00ff6f33          	or	t5,t5,a5
  a0:	fee42623          	sw	a4,-20(s0)
  a4:	fef42423          	sw	a5,-24(s0)

000000a8 <.L11>:
  a8:	001f7713          	and	a4,t5,1
  ac:	000007b7          	lui	a5,0x0
  b0:	00e7a023          	sw	a4,0(a5) # 0 <delay>
  b4:	000007b7          	lui	a5,0x0
  b8:	0007a783          	lw	a5,0(a5) # 0 <delay>
  bc:	04078263          	beqz	a5,100 <.L7>
  c0:	000007b7          	lui	a5,0x0
  c4:	0007a023          	sw	zero,0(a5) # 0 <delay>
  c8:	000007b7          	lui	a5,0x0
  cc:	0007a023          	sw	zero,0(a5) # 0 <delay>
  d0:	000007b7          	lui	a5,0x0
  d4:	0007a783          	lw	a5,0(a5) # 0 <delay>
  d8:	00379793          	sll	a5,a5,0x3
  dc:	fef42623          	sw	a5,-20(s0)
  e0:	000007b7          	lui	a5,0x0
  e4:	0007a783          	lw	a5,0(a5) # 0 <delay>
  e8:	00479793          	sll	a5,a5,0x4
  ec:	fef42423          	sw	a5,-24(s0)
  f0:	00ef6f33          	or	t5,t5,a4
  f4:	00ff6f33          	or	t5,t5,a5
  f8:	fee42623          	sw	a4,-20(s0)
  fc:	fef42423          	sw	a5,-24(s0)

00000100 <.L7>:
 100:	002f7793          	and	a5,t5,2
 104:	fef42223          	sw	a5,-28(s0)
 108:	fe442783          	lw	a5,-28(s0)
 10c:	01f7d713          	srl	a4,a5,0x1f
 110:	00f707b3          	add	a5,a4,a5
 114:	4017d793          	sra	a5,a5,0x1
 118:	00078713          	mv	a4,a5
 11c:	000007b7          	lui	a5,0x0
 120:	00e7a023          	sw	a4,0(a5) # 0 <delay>
 124:	000007b7          	lui	a5,0x0
 128:	0007a783          	lw	a5,0(a5) # 0 <delay>
 12c:	02079463          	bnez	a5,154 <.L8>
 130:	000007b7          	lui	a5,0x0
 134:	00100713          	li	a4,1
 138:	00e7a023          	sw	a4,0(a5) # 0 <delay>
 13c:	000007b7          	lui	a5,0x0
 140:	0007a783          	lw	a5,0(a5) # 0 <delay>
 144:	00479793          	sll	a5,a5,0x4
 148:	fef42423          	sw	a5,-24(s0)
 14c:	00ff6f33          	or	t5,t5,a5
 150:	fef42423          	sw	a5,-24(s0)

00000154 <.L8>:
 154:	003f7793          	and	a5,t5,3
 158:	fef42023          	sw	a5,-32(s0)
 15c:	fe042783          	lw	a5,-32(s0)
 160:	41f7d713          	sra	a4,a5,0x1f
 164:	00377713          	and	a4,a4,3
 168:	00f707b3          	add	a5,a4,a5
 16c:	4027d793          	sra	a5,a5,0x2
 170:	00078713          	mv	a4,a5
 174:	000007b7          	lui	a5,0x0
 178:	00e7a023          	sw	a4,0(a5) # 0 <delay>
 17c:	000007b7          	lui	a5,0x0
 180:	0007a783          	lw	a5,0(a5) # 0 <delay>
 184:	02078663          	beqz	a5,1b0 <.L9>
 188:	000007b7          	lui	a5,0x0
 18c:	00100713          	li	a4,1
 190:	00e7a023          	sw	a4,0(a5) # 0 <delay>
 194:	000007b7          	lui	a5,0x0
 198:	0007a783          	lw	a5,0(a5) # 0 <delay>
 19c:	00379793          	sll	a5,a5,0x3
 1a0:	fef42623          	sw	a5,-20(s0)
 1a4:	00ff6f33          	or	t5,t5,a5
 1a8:	fef42623          	sw	a5,-20(s0)
 1ac:	0240006f          	j	1d0 <.L10>

000001b0 <.L9>:
 1b0:	000007b7          	lui	a5,0x0
 1b4:	0007a023          	sw	zero,0(a5) # 0 <delay>
 1b8:	000007b7          	lui	a5,0x0
 1bc:	0007a783          	lw	a5,0(a5) # 0 <delay>
 1c0:	00379793          	sll	a5,a5,0x3
 1c4:	fef42623          	sw	a5,-20(s0)
 1c8:	00ff6f33          	or	t5,t5,a5
 1cc:	fef42623          	sw	a5,-20(s0)

000001d0 <.L10>:
 1d0:	3e800513          	li	a0,1000
 1d4:	00000097          	auipc	ra,0x0
 1d8:	000080e7          	jalr	ra # 1d4 <.L10+0x4>
 1dc:	ecdff06f          	j	a8 <.L11>
```

### UNIQUE INSTRUCTION

```
Number of different instructions: 20
List of unique instructions:
lui
ret
and
mv
beqz
li
bnez
blt
add
srl
j
auipc
sll
jalr
sw
lw
bge
nop
sra
or

```

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/9c43d7cd-245f-49c6-b61c-d0b4ebeee232)


