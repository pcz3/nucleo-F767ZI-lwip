/*******************************************************************************
 * @attention Copyright would go here...
 * @file utils.c
 * @author Paul Czeresko
 * @date 26 Oct 2019
 * @brief Utility functions
 *******************************************************************************/

#include "utils.h"
#include "cmsis_os.h"

TaskHandle_t xHeartbeatTask = NULL;

/**
 * @brief Show a sign of life on the Nucleo
 */
static void prvUtilsHeartbeatTask(void *pvParameters)
{
	uint16_t usDelay = 500;

	for (;;)
	{
		WRITE_REG(GPIOB->BSRR, BSRR_ON(LD2_Pin));
		vTaskDelay(pdMS_TO_TICKS(usDelay));
		WRITE_REG(GPIOB->BSRR, BSRR_OFF(LD2_Pin));
		vTaskDelay(pdMS_TO_TICKS(usDelay));
	}
}

/*
 * @brief Do startup stuff and initialize utility tasks
 */
void vUtilsSetup()
{
	xTaskCreate(prvUtilsHeartbeatTask, "hbeat", configMINIMAL_STACK_SIZE, NULL, 1, &xHeartbeatTask);
}
