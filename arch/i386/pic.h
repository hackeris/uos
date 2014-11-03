/*
 * pic.h
 *
 *  Created on: Nov 3, 2014
 *      Author: hackeris
 */

#ifndef PIC_H_
#define PIC_H_

#include <types.h>

// The following devices use PIC 1 to generate interrupts
#define		I86_PIC_IRQ_TIMER			0
#define		I86_PIC_IRQ_KEYBOARD		1
#define		I86_PIC_IRQ_SERIAL2			3
#define		I86_PIC_IRQ_SERIAL1			4
#define		I86_PIC_IRQ_PARALLEL2		5
#define		I86_PIC_IRQ_DISKETTE		6
#define		I86_PIC_IRQ_PARALLEL1		7

// The following devices use PIC 2 to generate interrupts
#define		I86_PIC_IRQ_CMOSTIMER		0
#define		I86_PIC_IRQ_CGARETRACE		1
#define		I86_PIC_IRQ_AUXILIARY		4
#define		I86_PIC_IRQ_FPU				5
#define		I86_PIC_IRQ_HDC				6

//-----------------------------------------------
//	Command words are used to control the devices
//-----------------------------------------------

// Command Word 2 bit masks. Use when sending commands
#define		I86_PIC_OCW2_MASK_L1		1		//00000001
#define		I86_PIC_OCW3_MASK_RIS		1		//00000001
#define I86_PIC1_REG_COMMAND	0x20
#define I86_PIC1_REG_STATUS		0x20
#define I86_PIC1_REG_DATA		0x21
#define I86_PIC1_REG_IMR		0x21

// PIC 2 register port addresses
#define I86_PIC2_REG_COMMAND	0xA0
#define I86_PIC2_REG_STATUS		0xA0
#define I86_PIC2_REG_DATA		0xA1
#define I86_PIC2_REG_IMR		0xA1

// Initialization Control Word 1 bit masks
#define I86_PIC_ICW1_MASK_IC4			0x1			//00000001
#define	I86_PIC_ICW1_MASK_INIT		0x10		//00010000

// Initialization Control Word 4 bit masks
#define I86_PIC_ICW4_MASK_UPM			0x1			//00000001
//	Initialization Command 1 control bits
//-----------------------------------------------

#define I86_PIC_ICW1_IC4_EXPECT				1			//1
#define I86_PIC_ICW1_SNGL_YES				2			//10
#define I86_PIC_ICW1_INIT_YES				0x10		//10000
//	Initialization Command 4 control bits
//-----------------------------------------------

#define I86_PIC_ICW4_UPM_86MODE			1			//1
// Read data byte from pic
extern uint8_t i86_pic_read_data(uint8_t picNum);

// Send a data byte to pic
extern void i86_pic_send_data(uint8_t data, uint8_t picNum);

// Send operational command to pic
extern void i86_pic_send_command(uint8_t cmd, uint8_t picNum);

// Enables and disables interrupts
extern void i86_pic_mask_irq(uint8_t irqmask, uint8_t picNum);

// Initialize pic
extern void i86_pic_initialize(uint8_t base0, uint8_t base1);

#endif /* PIC_H_ */