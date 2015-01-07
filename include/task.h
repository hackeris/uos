/*
 * task.h
 *
 *  Created on: Jan 7, 2015
 *      Author: hackeris
 */

#ifndef TASK_H_
#define TASK_H_

#include <types.h>

typedef void (*PTASK_FUN)();

typedef struct _task{
	PTASK_FUN	initial_eip;
	uint32_t	stack_size;
	char		name[20];
}task;


#endif /* TASK_H_ */