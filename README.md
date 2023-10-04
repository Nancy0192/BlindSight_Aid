# BlindSight_Aid

This repository contains RISC-V based blind sight aid.


## AIM
Navigating the world independently is a fundamental human right, yet visually impaired individuals face significant challenges in mobility and safety. This advanced assistive device aims to empower visually impaired individuals by enhancing their spatial awareness, obstacle detection, and overall confidence while navigating unfamiliar environments.
We will be using RISC-V to build the device and the sensor for that partiular functionality.


## BLOCK DIAGRAM OF THE BLIND STICK

![image](https://github.com/Nancy0192/BlindSight_Aid/assets/140998633/974e335b-9308-4ee4-b424-be3aadfea1b8)


## ASSEMBLY CODE GENERATION
We will be using RISC-V GNU Toolchain to convert our C code into assembly code. Let us first go through the RISC-V:

### RISC-V TOOLCHAIN
RISC-V is an open-source instruction set architecture (ISA) used for the development of custom processors targeting a variety of end applications.RISC-V ISA is considered the fifth generation of processors built on the concept of the reduced instruction set computer (RISC). Due to its openness and its technical merits, it has become very popular in recent years. The royalty-free RISC-V ISA features a small core set of instructions upon which all the design’s software runs. Its optional extensions allow designers to tailor the architecture for a variety of different end markets. Essentially, the RISC-V architecture allows designers to customize and build their processor in a way that’s tailored to their target end applications, so they can optimize the power, performance, and area (PPA) for those applications. The RISC-V ISA also provides the flexibility to pick and choose from available features, rather than having to use the full feature set. 
The GNU compile toolchain is a set of programming tools in LINUX system that can be use for compiling a code to generate certain executable program, library and debugger and whose detail can be found in references. RISC-V is one such toolchain which supports C and C++ cross compiler. It supports two build modes: a generic ELF/Newlib toolchain and a more sophisticated Linux-ELF/glibc toolchain and the github link for the same can be found in references.

### C Code

```

//#include <stdio.h>
//#define IR_SENSOR_PIN 17  // Replace with the actual GPIO pin number

int sensorValue = 0;
int buzzer = 0;
int buzzer_2 = 0;
int buzzer_3 = 0;
int reset =0;
int LDR = 1;
int push_button_LDR =0;
int watersensor = 1;


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
    	sensorValue =0;
    	buzzer =0;
    	}
    	
    	
    	if (LDR == 0){
    		
    		buzzer_2 = 1;
    		if (push_button_LDR)
    		{
    		buzzer=1;
    		}
    		
    		
    	}
    	
    	if (watersensor == 0){
    		
    		buzzer_3 = 1;
    		
    	}
    	
    	
        
        if (sensorValue == 1) {
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

final_code.o:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <register_fini>:
   10074:	ffff0797          	auipc	a5,0xffff0
   10078:	f8c78793          	addi	a5,a5,-116 # 0 <register_fini-0x10074>
   1007c:	00078863          	beqz	a5,1008c <register_fini+0x18>
   10080:	00000517          	auipc	a0,0x0
   10084:	13850513          	addi	a0,a0,312 # 101b8 <__libc_fini_array>
   10088:	0e80006f          	j	10170 <atexit>
   1008c:	00008067          	ret

00010090 <_start>:
   10090:	00002197          	auipc	gp,0x2
   10094:	d1018193          	addi	gp,gp,-752 # 11da0 <__global_pointer$>
   10098:	c3c18513          	addi	a0,gp,-964 # 119dc <_edata>
   1009c:	c7018613          	addi	a2,gp,-912 # 11a10 <__BSS_END__>
   100a0:	40a60633          	sub	a2,a2,a0
   100a4:	00000593          	li	a1,0
   100a8:	204000ef          	jal	ra,102ac <memset>
   100ac:	00000517          	auipc	a0,0x0
   100b0:	10c50513          	addi	a0,a0,268 # 101b8 <__libc_fini_array>
   100b4:	0bc000ef          	jal	ra,10170 <atexit>
   100b8:	160000ef          	jal	ra,10218 <__libc_init_array>
   100bc:	00012503          	lw	a0,0(sp)
   100c0:	00410593          	addi	a1,sp,4
   100c4:	00000613          	li	a2,0
   100c8:	0a4000ef          	jal	ra,1016c <main>
   100cc:	0b80006f          	j	10184 <exit>

000100d0 <__do_global_dtors_aux>:
   100d0:	c541c783          	lbu	a5,-940(gp) # 119f4 <completed.5434>
   100d4:	04079463          	bnez	a5,1011c <__do_global_dtors_aux+0x4c>
   100d8:	ffff0797          	auipc	a5,0xffff0
   100dc:	f2878793          	addi	a5,a5,-216 # 0 <register_fini-0x10074>
   100e0:	02078863          	beqz	a5,10110 <__do_global_dtors_aux+0x40>
   100e4:	ff010113          	addi	sp,sp,-16
   100e8:	00001517          	auipc	a0,0x1
   100ec:	4a850513          	addi	a0,a0,1192 # 11590 <__FRAME_END__>
   100f0:	00112623          	sw	ra,12(sp)
   100f4:	00000097          	auipc	ra,0x0
   100f8:	000000e7          	jalr	zero # 0 <register_fini-0x10074>
   100fc:	00c12083          	lw	ra,12(sp)
   10100:	00100793          	li	a5,1
   10104:	c4f18a23          	sb	a5,-940(gp) # 119f4 <completed.5434>
   10108:	01010113          	addi	sp,sp,16
   1010c:	00008067          	ret
   10110:	00100793          	li	a5,1
   10114:	c4f18a23          	sb	a5,-940(gp) # 119f4 <completed.5434>
   10118:	00008067          	ret
   1011c:	00008067          	ret

00010120 <frame_dummy>:
   10120:	ffff0797          	auipc	a5,0xffff0
   10124:	ee078793          	addi	a5,a5,-288 # 0 <register_fini-0x10074>
   10128:	00078c63          	beqz	a5,10140 <frame_dummy+0x20>
   1012c:	c5818593          	addi	a1,gp,-936 # 119f8 <object.5439>
   10130:	00001517          	auipc	a0,0x1
   10134:	46050513          	addi	a0,a0,1120 # 11590 <__FRAME_END__>
   10138:	00000317          	auipc	t1,0x0
   1013c:	00000067          	jr	zero # 0 <register_fini-0x10074>
   10140:	00008067          	ret

00010144 <delay>:
   10144:	00000713          	li	a4,0
   10148:	000026b7          	lui	a3,0x2
   1014c:	00a05e63          	blez	a0,10168 <delay+0x24>
   10150:	71068793          	addi	a5,a3,1808 # 2710 <register_fini-0xd964>
   10154:	fff78793          	addi	a5,a5,-1
   10158:	fe079ee3          	bnez	a5,10154 <delay+0x10>
   1015c:	00170713          	addi	a4,a4,1
   10160:	fee518e3          	bne	a0,a4,10150 <delay+0xc>
   10164:	00008067          	ret
   10168:	00008067          	ret

0001016c <main>:
   1016c:	0000006f          	j	1016c <main>

00010170 <atexit>:
   10170:	00050593          	mv	a1,a0
   10174:	00000693          	li	a3,0
   10178:	00000613          	li	a2,0
   1017c:	00000513          	li	a0,0
   10180:	2080006f          	j	10388 <__register_exitproc>

00010184 <exit>:
   10184:	ff010113          	addi	sp,sp,-16
   10188:	00000593          	li	a1,0
   1018c:	00812423          	sw	s0,8(sp)
   10190:	00112623          	sw	ra,12(sp)
   10194:	00050413          	mv	s0,a0
   10198:	28c000ef          	jal	ra,10424 <__call_exitprocs>
   1019c:	c2818793          	addi	a5,gp,-984 # 119c8 <_global_impure_ptr>
   101a0:	0007a503          	lw	a0,0(a5)
   101a4:	03c52783          	lw	a5,60(a0)
   101a8:	00078463          	beqz	a5,101b0 <exit+0x2c>
   101ac:	000780e7          	jalr	a5
   101b0:	00040513          	mv	a0,s0
   101b4:	38c000ef          	jal	ra,10540 <_exit>

000101b8 <__libc_fini_array>:
   101b8:	ff010113          	addi	sp,sp,-16
   101bc:	00812423          	sw	s0,8(sp)
   101c0:	00001797          	auipc	a5,0x1
   101c4:	3dc78793          	addi	a5,a5,988 # 1159c <__init_array_end>
   101c8:	00001417          	auipc	s0,0x1
   101cc:	3d840413          	addi	s0,s0,984 # 115a0 <__fini_array_end>
   101d0:	40f40433          	sub	s0,s0,a5
   101d4:	00112623          	sw	ra,12(sp)
   101d8:	00912223          	sw	s1,4(sp)
   101dc:	40245413          	srai	s0,s0,0x2
   101e0:	02040263          	beqz	s0,10204 <__libc_fini_array+0x4c>
   101e4:	00241493          	slli	s1,s0,0x2
   101e8:	ffc48493          	addi	s1,s1,-4
   101ec:	00f484b3          	add	s1,s1,a5
   101f0:	0004a783          	lw	a5,0(s1)
   101f4:	fff40413          	addi	s0,s0,-1
   101f8:	ffc48493          	addi	s1,s1,-4
   101fc:	000780e7          	jalr	a5
   10200:	fe0418e3          	bnez	s0,101f0 <__libc_fini_array+0x38>
   10204:	00c12083          	lw	ra,12(sp)
   10208:	00812403          	lw	s0,8(sp)
   1020c:	00412483          	lw	s1,4(sp)
   10210:	01010113          	addi	sp,sp,16
   10214:	00008067          	ret

00010218 <__libc_init_array>:
   10218:	ff010113          	addi	sp,sp,-16
   1021c:	00812423          	sw	s0,8(sp)
   10220:	01212023          	sw	s2,0(sp)
   10224:	00001417          	auipc	s0,0x1
   10228:	37040413          	addi	s0,s0,880 # 11594 <__init_array_start>
   1022c:	00001917          	auipc	s2,0x1
   10230:	36890913          	addi	s2,s2,872 # 11594 <__init_array_start>
   10234:	40890933          	sub	s2,s2,s0
   10238:	00112623          	sw	ra,12(sp)
   1023c:	00912223          	sw	s1,4(sp)
   10240:	40295913          	srai	s2,s2,0x2
   10244:	00090e63          	beqz	s2,10260 <__libc_init_array+0x48>
   10248:	00000493          	li	s1,0
   1024c:	00042783          	lw	a5,0(s0)
   10250:	00148493          	addi	s1,s1,1
   10254:	00440413          	addi	s0,s0,4
   10258:	000780e7          	jalr	a5
   1025c:	fe9918e3          	bne	s2,s1,1024c <__libc_init_array+0x34>
   10260:	00001417          	auipc	s0,0x1
   10264:	33440413          	addi	s0,s0,820 # 11594 <__init_array_start>
   10268:	00001917          	auipc	s2,0x1
   1026c:	33490913          	addi	s2,s2,820 # 1159c <__init_array_end>
   10270:	40890933          	sub	s2,s2,s0
   10274:	40295913          	srai	s2,s2,0x2
   10278:	00090e63          	beqz	s2,10294 <__libc_init_array+0x7c>
   1027c:	00000493          	li	s1,0
   10280:	00042783          	lw	a5,0(s0)
   10284:	00148493          	addi	s1,s1,1
   10288:	00440413          	addi	s0,s0,4
   1028c:	000780e7          	jalr	a5
   10290:	fe9918e3          	bne	s2,s1,10280 <__libc_init_array+0x68>
   10294:	00c12083          	lw	ra,12(sp)
   10298:	00812403          	lw	s0,8(sp)
   1029c:	00412483          	lw	s1,4(sp)
   102a0:	00012903          	lw	s2,0(sp)
   102a4:	01010113          	addi	sp,sp,16
   102a8:	00008067          	ret

000102ac <memset>:
   102ac:	00f00313          	li	t1,15
   102b0:	00050713          	mv	a4,a0
   102b4:	02c37e63          	bgeu	t1,a2,102f0 <memset+0x44>
   102b8:	00f77793          	andi	a5,a4,15
   102bc:	0a079063          	bnez	a5,1035c <memset+0xb0>
   102c0:	08059263          	bnez	a1,10344 <memset+0x98>
   102c4:	ff067693          	andi	a3,a2,-16
   102c8:	00f67613          	andi	a2,a2,15
   102cc:	00e686b3          	add	a3,a3,a4
   102d0:	00b72023          	sw	a1,0(a4)
   102d4:	00b72223          	sw	a1,4(a4)
   102d8:	00b72423          	sw	a1,8(a4)
   102dc:	00b72623          	sw	a1,12(a4)
   102e0:	01070713          	addi	a4,a4,16
   102e4:	fed766e3          	bltu	a4,a3,102d0 <memset+0x24>
   102e8:	00061463          	bnez	a2,102f0 <memset+0x44>
   102ec:	00008067          	ret
   102f0:	40c306b3          	sub	a3,t1,a2
   102f4:	00269693          	slli	a3,a3,0x2
   102f8:	00000297          	auipc	t0,0x0
   102fc:	005686b3          	add	a3,a3,t0
   10300:	00c68067          	jr	12(a3)
   10304:	00b70723          	sb	a1,14(a4)
   10308:	00b706a3          	sb	a1,13(a4)
   1030c:	00b70623          	sb	a1,12(a4)
   10310:	00b705a3          	sb	a1,11(a4)
   10314:	00b70523          	sb	a1,10(a4)
   10318:	00b704a3          	sb	a1,9(a4)
   1031c:	00b70423          	sb	a1,8(a4)
   10320:	00b703a3          	sb	a1,7(a4)
   10324:	00b70323          	sb	a1,6(a4)
   10328:	00b702a3          	sb	a1,5(a4)
   1032c:	00b70223          	sb	a1,4(a4)
   10330:	00b701a3          	sb	a1,3(a4)
   10334:	00b70123          	sb	a1,2(a4)
   10338:	00b700a3          	sb	a1,1(a4)
   1033c:	00b70023          	sb	a1,0(a4)
   10340:	00008067          	ret
   10344:	0ff5f593          	andi	a1,a1,255
   10348:	00859693          	slli	a3,a1,0x8
   1034c:	00d5e5b3          	or	a1,a1,a3
   10350:	01059693          	slli	a3,a1,0x10
   10354:	00d5e5b3          	or	a1,a1,a3
   10358:	f6dff06f          	j	102c4 <memset+0x18>
   1035c:	00279693          	slli	a3,a5,0x2
   10360:	00000297          	auipc	t0,0x0
   10364:	005686b3          	add	a3,a3,t0
   10368:	00008293          	mv	t0,ra
   1036c:	fa0680e7          	jalr	-96(a3)
   10370:	00028093          	mv	ra,t0
   10374:	ff078793          	addi	a5,a5,-16
   10378:	40f70733          	sub	a4,a4,a5
   1037c:	00f60633          	add	a2,a2,a5
   10380:	f6c378e3          	bgeu	t1,a2,102f0 <memset+0x44>
   10384:	f3dff06f          	j	102c0 <memset+0x14>

00010388 <__register_exitproc>:
   10388:	c2818793          	addi	a5,gp,-984 # 119c8 <_global_impure_ptr>
   1038c:	0007a703          	lw	a4,0(a5)
   10390:	14872783          	lw	a5,328(a4)
   10394:	04078c63          	beqz	a5,103ec <__register_exitproc+0x64>
   10398:	0047a703          	lw	a4,4(a5)
   1039c:	01f00813          	li	a6,31
   103a0:	06e84e63          	blt	a6,a4,1041c <__register_exitproc+0x94>
   103a4:	00271813          	slli	a6,a4,0x2
   103a8:	02050663          	beqz	a0,103d4 <__register_exitproc+0x4c>
   103ac:	01078333          	add	t1,a5,a6
   103b0:	08c32423          	sw	a2,136(t1) # 101c0 <__libc_fini_array+0x8>
   103b4:	1887a883          	lw	a7,392(a5)
   103b8:	00100613          	li	a2,1
   103bc:	00e61633          	sll	a2,a2,a4
   103c0:	00c8e8b3          	or	a7,a7,a2
   103c4:	1917a423          	sw	a7,392(a5)
   103c8:	10d32423          	sw	a3,264(t1)
   103cc:	00200693          	li	a3,2
   103d0:	02d50463          	beq	a0,a3,103f8 <__register_exitproc+0x70>
   103d4:	00170713          	addi	a4,a4,1
   103d8:	00e7a223          	sw	a4,4(a5)
   103dc:	010787b3          	add	a5,a5,a6
   103e0:	00b7a423          	sw	a1,8(a5)
   103e4:	00000513          	li	a0,0
   103e8:	00008067          	ret
   103ec:	14c70793          	addi	a5,a4,332
   103f0:	14f72423          	sw	a5,328(a4)
   103f4:	fa5ff06f          	j	10398 <__register_exitproc+0x10>
   103f8:	18c7a683          	lw	a3,396(a5)
   103fc:	00170713          	addi	a4,a4,1
   10400:	00e7a223          	sw	a4,4(a5)
   10404:	00c6e633          	or	a2,a3,a2
   10408:	18c7a623          	sw	a2,396(a5)
   1040c:	010787b3          	add	a5,a5,a6
   10410:	00b7a423          	sw	a1,8(a5)
   10414:	00000513          	li	a0,0
   10418:	00008067          	ret
   1041c:	fff00513          	li	a0,-1
   10420:	00008067          	ret

00010424 <__call_exitprocs>:
   10424:	fd010113          	addi	sp,sp,-48
   10428:	c2818793          	addi	a5,gp,-984 # 119c8 <_global_impure_ptr>
   1042c:	01812423          	sw	s8,8(sp)
   10430:	0007ac03          	lw	s8,0(a5)
   10434:	01312e23          	sw	s3,28(sp)
   10438:	01412c23          	sw	s4,24(sp)
   1043c:	01512a23          	sw	s5,20(sp)
   10440:	01612823          	sw	s6,16(sp)
   10444:	02112623          	sw	ra,44(sp)
   10448:	02812423          	sw	s0,40(sp)
   1044c:	02912223          	sw	s1,36(sp)
   10450:	03212023          	sw	s2,32(sp)
   10454:	01712623          	sw	s7,12(sp)
   10458:	00050a93          	mv	s5,a0
   1045c:	00058b13          	mv	s6,a1
   10460:	00100a13          	li	s4,1
   10464:	fff00993          	li	s3,-1
   10468:	148c2903          	lw	s2,328(s8)
   1046c:	02090863          	beqz	s2,1049c <__call_exitprocs+0x78>
   10470:	00492483          	lw	s1,4(s2)
   10474:	fff48413          	addi	s0,s1,-1
   10478:	02044263          	bltz	s0,1049c <__call_exitprocs+0x78>
   1047c:	00249493          	slli	s1,s1,0x2
   10480:	009904b3          	add	s1,s2,s1
   10484:	040b0463          	beqz	s6,104cc <__call_exitprocs+0xa8>
   10488:	1044a783          	lw	a5,260(s1)
   1048c:	05678063          	beq	a5,s6,104cc <__call_exitprocs+0xa8>
   10490:	fff40413          	addi	s0,s0,-1
   10494:	ffc48493          	addi	s1,s1,-4
   10498:	ff3416e3          	bne	s0,s3,10484 <__call_exitprocs+0x60>
   1049c:	02c12083          	lw	ra,44(sp)
   104a0:	02812403          	lw	s0,40(sp)
   104a4:	02412483          	lw	s1,36(sp)
   104a8:	02012903          	lw	s2,32(sp)
   104ac:	01c12983          	lw	s3,28(sp)
   104b0:	01812a03          	lw	s4,24(sp)
   104b4:	01412a83          	lw	s5,20(sp)
   104b8:	01012b03          	lw	s6,16(sp)
   104bc:	00c12b83          	lw	s7,12(sp)
   104c0:	00812c03          	lw	s8,8(sp)
   104c4:	03010113          	addi	sp,sp,48
   104c8:	00008067          	ret
   104cc:	00492783          	lw	a5,4(s2)
   104d0:	0044a683          	lw	a3,4(s1)
   104d4:	fff78793          	addi	a5,a5,-1
   104d8:	04878a63          	beq	a5,s0,1052c <__call_exitprocs+0x108>
   104dc:	0004a223          	sw	zero,4(s1)
   104e0:	fa0688e3          	beqz	a3,10490 <__call_exitprocs+0x6c>
   104e4:	18892783          	lw	a5,392(s2)
   104e8:	008a1733          	sll	a4,s4,s0
   104ec:	00492b83          	lw	s7,4(s2)
   104f0:	00f777b3          	and	a5,a4,a5
   104f4:	00079e63          	bnez	a5,10510 <__call_exitprocs+0xec>
   104f8:	000680e7          	jalr	a3
   104fc:	00492783          	lw	a5,4(s2)
   10500:	f77794e3          	bne	a5,s7,10468 <__call_exitprocs+0x44>
   10504:	148c2783          	lw	a5,328(s8)
   10508:	f92784e3          	beq	a5,s2,10490 <__call_exitprocs+0x6c>
   1050c:	f5dff06f          	j	10468 <__call_exitprocs+0x44>
   10510:	18c92783          	lw	a5,396(s2)
   10514:	0844a583          	lw	a1,132(s1)
   10518:	00f77733          	and	a4,a4,a5
   1051c:	00071c63          	bnez	a4,10534 <__call_exitprocs+0x110>
   10520:	000a8513          	mv	a0,s5
   10524:	000680e7          	jalr	a3
   10528:	fd5ff06f          	j	104fc <__call_exitprocs+0xd8>
   1052c:	00892223          	sw	s0,4(s2)
   10530:	fb1ff06f          	j	104e0 <__call_exitprocs+0xbc>
   10534:	00058513          	mv	a0,a1
   10538:	000680e7          	jalr	a3
   1053c:	fc1ff06f          	j	104fc <__call_exitprocs+0xd8>

00010540 <_exit>:
   10540:	00000593          	li	a1,0
   10544:	00000613          	li	a2,0
   10548:	00000693          	li	a3,0
   1054c:	00000713          	li	a4,0
   10550:	00000793          	li	a5,0
   10554:	05d00893          	li	a7,93
   10558:	00000073          	ecall
   1055c:	00054463          	bltz	a0,10564 <_exit+0x24>
   10560:	0000006f          	j	10560 <_exit+0x20>
   10564:	ff010113          	addi	sp,sp,-16
   10568:	00812423          	sw	s0,8(sp)
   1056c:	00050413          	mv	s0,a0
   10570:	00112623          	sw	ra,12(sp)
   10574:	40800433          	neg	s0,s0
   10578:	00c000ef          	jal	ra,10584 <__errno>
   1057c:	00852023          	sw	s0,0(a0)
   10580:	0000006f          	j	10580 <_exit+0x40>

00010584 <__errno>:
   10584:	c3818793          	addi	a5,gp,-968 # 119d8 <_impure_ptr>
   10588:	0007a503          	lw	a0,0(a5)
   1058c:	00008067          	ret

```

### UNIQUE INSTRUCTION

```

Number of different instructions: 33
List of unique instructions:
neg
and
jr
sw
beqz
bgeu
lw
or
lui
auipc
sll
bltu
blez
li
sb
slli
beq
add
ret
lbu
sub
jalr
bnez
srai
mv
bltz
j
ecall
jal
blt
bne
addi
andi

```




