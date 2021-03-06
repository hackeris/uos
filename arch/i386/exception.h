/*
 * exception.h
 *
 *  Created on: Mar 28, 2015
 *      Author: hackeris
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#define _cdecl
#define interrupt

#define intstart()	\
	__asm("cli\r\n""subl $4,%ebp")

#include <types.h>

//! divide by 0
extern void _cdecl divide_by_zero_fault(uint32_t a, uint32_t b, uint32_t c);

//! single step
extern void _cdecl single_step_trap(uint32_t cs, uint32_t eip, uint32_t eflags);

//! non maskable interrupt trap
extern void _cdecl nmi_trap(uint32_t cs, uint32_t eip, uint32_t eflags);

//! breakpoint hit
extern void _cdecl breakpoint_trap(uint32_t cs, uint32_t eip, uint32_t eflags);

//! overflow
extern void _cdecl overflow_trap(uint32_t cs, uint32_t eip, uint32_t eflags);

//! bounds check
extern void _cdecl bounds_check_fault(uint32_t cs, uint32_t eip,
		uint32_t eflags);

//! invalid opcode / instruction
extern void _cdecl invalid_opcode_fault(uint32_t cs, uint32_t eip,
		uint32_t eflags);

//! device not available
extern void _cdecl no_device_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

//! double fault
extern void _cdecl double_fault_abort(uint32_t eip, uint32_t cs, uint32_t flags,
		uint32_t err);

//! invalid Task State Segment (TSS)
extern void _cdecl invalid_tss_fault(uint32_t eip, uint32_t cs, uint32_t flags,
		uint32_t err);

//! segment not present
extern void _cdecl no_segment_fault(uint32_t eip, uint32_t cs, uint32_t flags,
		uint32_t err);

//! stack fault
extern void _cdecl stack_fault(uint32_t eip, uint32_t cs, uint32_t flags,
		uint32_t err);

//! general protection fault
extern void _cdecl general_protection_fault(uint32_t eip, uint32_t cs,
		uint32_t flags, uint32_t err);

//! page fault
extern void _cdecl page_fault(uint32_t eip, uint32_t cs, uint32_t flags,
		uint32_t err);

//! Floating Point Unit (FPU) error
extern void _cdecl fpu_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

//! alignment check
extern void _cdecl alignment_check_fault(uint32_t eip, uint32_t cs,
		uint32_t flags, uint32_t err);

//! machine check
extern void _cdecl machine_check_abort(uint32_t cs, uint32_t eip,
		uint32_t flags);

//! Floating Point Unit (FPU) Single Instruction Multiple Data (SIMD) error
extern void _cdecl simd_fpu_fault(uint32_t cs, uint32_t eip, uint32_t eflags);

#endif /* EXCEPTION_H_ */
