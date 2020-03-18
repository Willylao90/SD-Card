#include <stdbool.h>
#include "PAL_task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/scb.h>
#ifdef STM32L1
#define RCCLEDPORT (RCC_GPIOB)
#define LEDPORT (GPIOB)
#define LEDPIN (GPIO6)
#elif STM32F1
#define RCCLEDPORT (RCC_GPIOC)
#define LEDPORT (GPIOC)
#define LEDPIN (GPIO13)
#define GPIO_MODE_OUTPUT GPIO_MODE_OUTPUT_2_MHZ
#define GPIO_PUPD_NONE GPIO_CNF_OUTPUT_PUSHPULL
#elif STM32F3
#define RCCLEDPORT (RCC_GPIOE)
#define LEDPORT (GPIOE)
#define LEDPIN (GPIO8)
#elif STM32F4
#define RCCLEDPORT (RCC_GPIOD)
#define LEDPORT (GPIOD)
#define LEDPIN (GPIO12)
#else
#error "This example doesn't support this target!"
#endif

#define DEBUGLED_STACKSIZE 100
static StackType_t debugLED_stack[DEBUGLED_STACKSIZE];
static StaticTask_t debugLED_taskBuff;
static void debug_LED(void *data);

static void gpio_setup(void)
{
	/* Enable GPIO clock. */
	/* Using API functions: */
	rcc_periph_clock_enable(RCCLEDPORT);
	/* Set pin to 'output push-pull'. */
	/* Using API functions: */
#ifdef STM32F1
	gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
#else
	gpio_mode_setup(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
#endif
}

/**
 * @brief init
 * Initialise the Hardware
 * 
 * @return true - Success
 * @return false - Failed
 */
static bool init(void)
{
	bool result = false;

	gpio_setup();
	PAL_TaskCreateStatic(debug_LED, "debugLED", DEBUGLED_STACKSIZE, NULL, tskIDLE_PRIORITY + 1, debugLED_stack, &debugLED_taskBuff);
	return result;
}

static void debug_LED(void *data)
{
	const TickType_t xFrequency = 10;
	TickType_t xLastWakeTime;

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	for (;;)
	{
		// Wait for the next cycle.
		vTaskDelayUntil(&xLastWakeTime, xFrequency);

		// Perform action here.
		gpio_toggle(LEDPORT, LEDPIN); /* LED on/off */
	}
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
								   StackType_t **ppxIdleTaskStackBuffer,
								   uint32_t *pulIdleTaskStackSize)
{
	/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle task’s
    state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task’s stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*———————————————————–*/

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
									StackType_t **ppxTimerTaskStackBuffer,
									uint32_t *pulTimerTaskStackSize)
{
	/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

	/* Pass out a pointer to the StaticTask_t structure in which the Timer
    task’s state will be stored. */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task’s stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/**
 * @brief Main
 * Execute init and main loop
 * 
 * @return int 
 */
int main(void)
{
	init();
	vTaskStartScheduler();
	while (1)
		;
	return 0;
}