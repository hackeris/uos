/*
 * cpu.c
 *
 *  Created on: Nov 2, 2014
 *      Author: hackeris
 */

#include <cpu.h>
#include <klib.h>

// Global Descriptor Table (GDT)
static struct gdt_descriptor _gdt[MAX_DESCRIPTORS];
// gdtr data
static struct gdtr _gdtr;
// interrupt descriptor table
static struct idt_descriptor _idt[I86_MAX_INTERRUPTS];
// idtr structure used to help define the cpu's idtr register
static struct idtr _idtr;

void gdt_set_descriptor(unsigned int i, unsigned int base, unsigned int limit,
		unsigned char access, unsigned char grand) {

	if (i > MAX_DESCRIPTORS)
		return;

	// null out the descriptor
	memset((void*) &_gdt[i], 0, sizeof(struct gdt_descriptor));

	// set limit and base addresses
	_gdt[i].baseLo = base & 0xffff;
	_gdt[i].baseMid = (base >> 16) & 0xff;
	_gdt[i].baseHi = (base >> 24) & 0xff;
	_gdt[i].limit = limit & 0xffff;

	// set flags and grandularity bytes
	_gdt[i].flags = access;
	_gdt[i].grand = (limit >> 16) & 0x0f;
	_gdt[i].grand |= grand & 0xf0;
}

int i86_gdt_initialize() {

	// set up gdtr
	_gdtr.m_limit = (sizeof(struct gdt_descriptor) * MAX_DESCRIPTORS) - 1;
	_gdtr.m_base = (uint32_t) &_gdt[0];

	// set null descriptor
	gdt_set_descriptor(0, 0, 0, 0, 0);

	//! set default code descriptor
	gdt_set_descriptor(1, 0, 0xffffffff,
			I86_GDT_DESC_READWRITE | I86_GDT_DESC_EXEC_CODE
					| I86_GDT_DESC_CODEDATA | I86_GDT_DESC_MEMORY,
			I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);
	//! set default data descriptor
	gdt_set_descriptor(2, 0, 0xffffffff,
	I86_GDT_DESC_READWRITE | I86_GDT_DESC_CODEDATA | I86_GDT_DESC_MEMORY,
	I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	gdt_install(&_gdtr);

	return 0;
}

void i86_default_handler() {

	kprintf("Interrupted\n");
	for (;;) {
		;
	}
}

// installs a new interrupt handler
int i86_install_ir(uint32_t i, uint16_t flags, uint16_t sel,
		i86_irq_handler irq) {

	if (i > I86_MAX_INTERRUPTS)
		return 0;

	if (!irq)
		return 0;

	// get base address of interrupt handler
	uint64_t uiBase = (uint64_t) &(*irq);

	// store base address into idt
	_idt[i].baseLo = (uint16_t)(uiBase & 0xffff);
	_idt[i].baseHi = (uint16_t)((uiBase >> 16) & 0xffff);
	_idt[i].reserved = 0;
	_idt[i].flags = (uint8_t)(flags);
	_idt[i].sel = sel;

	return 0;
}

// initialize idt
int i86_idt_initialize(uint16_t codeSel) {

	// set up idtr for processor
	_idtr.limit = sizeof(struct idt_descriptor) * I86_MAX_INTERRUPTS - 1;
	_idtr.base = (uint32_t) &_idt[0];

	// null out the idt
	memset((void*) &_idt[0], 0,
			sizeof(struct idt_descriptor) * I86_MAX_INTERRUPTS - 1);

	// register default handlers
	int i;
	for (i = 0; i < I86_MAX_INTERRUPTS; i++)
		i86_install_ir(i, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32, codeSel,
				(i86_irq_handler) i86_default_handler);

	// install our idt
	idt_install(&_idtr);

	return 0;
}