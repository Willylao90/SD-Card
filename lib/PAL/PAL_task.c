/**
 * @file PAL_task.c
 * @author William Lowther (william.e.lowther@gmail.com)
 * @brief PAL wrapper for RTOS
 * @version 0.1
 * @date 2020-03-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "PAL_task.h"

/**
 * @brief Create a new task and add it to the list of tasks that are ready to run.
 *
 *
 * @param pvTaskCode Pointer to the task entry function.  Tasks
 * must be implemented to never return (i.e. continuous loop).
 *
 * @param pcName A descriptive name for the task.  This is mainly used to
 * facilitate debugging.  The maximum length of the string is defined by
 * configMAX_TASK_NAME_LEN in FreeRTOSConfig.h.
 *
 * @param ulStackDepth The size of the task stack specified as the number of
 * variables the stack can hold - not the number of bytes.  For example, if
 * the stack is 32-bits wide and ulStackDepth is defined as 100 then 400 bytes
 * will be allocated for stack storage.
 *
 * @param pvParameters Pointer that will be used as the parameter for the task
 * being created.
 *
 * @param uxPriority The priority at which the task will run.
 *
 * @param pxStackBuffer Must point to a StackType_t array that has at least
 * ulStackDepth indexes - the array will then be used as the task's stack,
 * removing the need for the stack to be allocated dynamically.
 *
 * @param pxTaskBuffer Must point to a variable of type StaticTask_t, which will
 * then be used to hold the task's data structures, removing the need for the
 * memory to be allocated dynamically.
 *
 * @return If neither pxStackBuffer or pxTaskBuffer are NULL, then the task will
 * be created and a handle to the created task is returned.  If either
 * pxStackBuffer or pxTaskBuffer are NULL then the task will not be created and
 * NULL is returned.
 *
 * Example usage:
   <pre>

	// Dimensions the buffer that the task being created will use as its stack.
	// NOTE:  This is the number of words the stack will hold, not the number of
	// bytes.  For example, if each stack item is 32-bits, and this is set to 100,
	// then 400 bytes (100 * 32-bits) will be allocated.
	#define STACK_SIZE 200

	// Structure that will hold the TCB of the task being created.
	StaticTask_t xTaskBuffer;

	// Buffer that the task being created will use as its stack.  Note this is
	// an array of StackType_t variables.  The size of StackType_t is dependent on
	// the RTOS port.
	StackType_t xStack[ STACK_SIZE ];

	// Function that implements the task being created.
	void vTaskCode( void * pvParameters )
	{
		// The parameter value is expected to be 1 as 1 is passed in the
		// pvParameters value in the call to xTaskCreateStatic().
		configASSERT( ( uint32_t ) pvParameters == 1UL );

		for( ;; )
		{
			// Task code goes here.
		}
	}

	// Function that creates a task.
	void vOtherFunction( void )
	{
		TaskHandle_t xHandle = NULL;

		// Create the task without using any dynamic memory allocation.
		xHandle = xTaskCreateStatic(
					  vTaskCode,       // Function that implements the task.
					  "NAME",          // Text name for the task.
					  STACK_SIZE,      // Stack size in words, not bytes.
					  ( void * ) 1,    // Parameter passed into the task.
					  tskIDLE_PRIORITY,// Priority at which the task is created.
					  xStack,          // Array to use as the task's stack.
					  &xTaskBuffer );  // Variable to hold the task's data structure.

		// puxStackBuffer and pxTaskBuffer were not NULL, so the task will have
		// been created, and xHandle will be the task's handle.  Use the handle
		// to suspend the task.
		vTaskSuspend( xHandle );
	}
   </pre>
 */
TaskHandle_t PAL_TaskCreateStatic(TaskFunction_t pxTaskCode,
								  const char *const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
								  const uint32_t ulStackDepth,
								  void *const pvParameters,
								  UBaseType_t uxPriority,
								  StackType_t *const puxStackBuffer,
								  StaticTask_t *const pxTaskBuffer)
{
	return xTaskCreateStatic(pxTaskCode, pcName, ulStackDepth, pvParameters, uxPriority, puxStackBuffer, pxTaskBuffer);
}