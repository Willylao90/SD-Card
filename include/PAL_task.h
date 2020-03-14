/**
 * @file PAL_task.h
 * @author William Lowther (william.e.lowther@gmail.com)
 * @brief PAL Task wrapper
 * @version 0.1
 * @date 2020-03-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _PAL_TASK_H_
#define _PAL_TASK_H_

#include "PAL.h"
#include "task.h"

BaseType_t PAL_TaskCreate(TaskFunction_t pxTaskCode,
						  const char *const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
						  const configSTACK_DEPTH_TYPE usStackDepth,
						  void *const pvParameters,
						  UBaseType_t uxPriority,
						  TaskHandle_t *const pxCreatedTask) PRIVILEGED_FUNCTION;

#endif // _PAL_TASK_H_
