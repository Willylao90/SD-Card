#include <stdbool.h>
#include "PAL_task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
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

static void debug_LED(void* data);

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
	xTaskCreate(debug_LED, "debugLED", 100, NULL, 1, NULL);
	return result;
}

static void debug_LED(void* data)
{
	const TickType_t xFrequency = 10;
	TickType_t xLastWakeTime;

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		// Wait for the next cycle.
		vTaskDelayUntil( &xLastWakeTime, xFrequency );

		// Perform action here.
		gpio_toggle(LEDPORT, LEDPIN);	/* LED on/off */
	}
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
	while(1)
	{
		vTaskStartScheduler();
	}
	return 0;
}