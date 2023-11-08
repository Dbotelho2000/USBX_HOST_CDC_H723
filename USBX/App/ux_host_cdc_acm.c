/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    ux_host_cdc_acm.c
 * @author  MCD Application Team
 * @brief   USBX Host CDC ACM applicative source file
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2020-2021 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "ux_host_cdc_acm.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define APP_RX_DATA_SIZE 1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/* Imported RTOS Resources */
extern UX_HOST_CLASS_CDC_ACM *cdc_acm;
extern TX_EVENT_FLAGS_GROUP cdc_acm_eventflag;
extern TX_MUTEX cdc_acm_uart_mutex;

UX_HOST_CLASS_CDC_ACM_RECEPTION cdc_acm_reception;
uint8_t UserRxBuffer[APP_RX_DATA_SIZE];
ULONG block_reception_count;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
VOID cdc_acm_reception_callback(struct UX_HOST_CLASS_CDC_ACM_STRUCT *cdc_acm,
		UINT status, UCHAR *reception_buffer, ULONG reception_size);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* USER CODE BEGIN 1 */
VOID cdc_acm_send_thread_entry(ULONG thread_input)
{
	/* Local Variables */
	UINT status;
	UCHAR UserTxBuffer[] = "10";
	ULONG tx_actual_length;
	uint8_t nibble = 0;

	/* Infinite Loop */
	while(1)
	{
		/* Check if the CDC Class is available */
		if((cdc_acm != UX_NULL) && (cdc_acm->ux_host_class_cdc_acm_state == UX_HOST_CLASS_INSTANCE_LIVE))
		{
			/* Start sending data and store it results */
			status = _ux_host_class_cdc_acm_write(cdc_acm, &UserTxBuffer[nibble], 1, &tx_actual_length);

			tx_mutex_get(&cdc_acm_uart_mutex, TX_WAIT_FOREVER);
			if (status == UX_SUCCESS)
				printf("Data sent: %c\r\n", UserTxBuffer[nibble]);
			else
				printf("Unable to send data\r\n");
			tx_mutex_put(&cdc_acm_uart_mutex);

			/* Invert the nibble variable */
			nibble ^= 1;

			/* Wait 2 seconds for the next transmission */
			tx_thread_sleep(200);
		}
		else
		{
			tx_thread_sleep(1);
		}
	}
}

VOID cdc_acm_receive_thread_entry(ULONG thread_input)
{
	/* Local Variables */
	UINT status;
	ULONG events;

	/* Infinite Loop */
	while(1)
	{
		/* Check if the CDC Class is available */
		if((cdc_acm != UX_NULL) && (cdc_acm->ux_host_class_cdc_acm_state == UX_HOST_CLASS_INSTANCE_LIVE))
		{
			/* Check if the reception was already started */
			if(cdc_acm_reception.ux_host_class_cdc_acm_reception_state != UX_HOST_CLASS_CDC_ACM_RECEPTION_STATE_STARTED)
			{
				/* Configure the reception parameters */
				cdc_acm_reception.ux_host_class_cdc_acm_reception_block_size = 64;
				cdc_acm_reception.ux_host_class_cdc_acm_reception_data_buffer = (UCHAR *)UserRxBuffer;
				cdc_acm_reception.ux_host_class_cdc_acm_reception_data_buffer_size = APP_RX_DATA_SIZE;
				cdc_acm_reception.ux_host_class_cdc_acm_reception_callback = cdc_acm_reception_callback;

				/* Start the recpetion and store it status */
				status = ux_host_class_cdc_acm_reception_start(cdc_acm, &cdc_acm_reception);

				if (status == UX_SUCCESS)
				{
					tx_mutex_get(&cdc_acm_uart_mutex, TX_WAIT_FOREVER);
					printf("Ready to receive data\r\n");
					tx_mutex_put(&cdc_acm_uart_mutex);
				}
				else
				{
					tx_mutex_get(&cdc_acm_uart_mutex, TX_WAIT_FOREVER);
					printf("Unable to start reception\r\n");
					tx_mutex_put(&cdc_acm_uart_mutex);
					/* Wait 100 ms until try to start the reception again */
					tx_thread_sleep(10);
				}
			}
			/* Reception already started */
			else if(cdc_acm_reception.ux_host_class_cdc_acm_reception_state == UX_HOST_CLASS_CDC_ACM_RECEPTION_STATE_STARTED)
			{
				/* Wait for a data to be received */
				tx_event_flags_get(&cdc_acm_eventflag, 0x01, TX_OR_CLEAR, &events, TX_WAIT_FOREVER);

				/* Print the received data through UART */
				printf("Data received: ");
				for(uint16_t count = 0; count < block_reception_count; count++){
					printf("%c", UserRxBuffer[count]);
				}
			}
		}
		else
			tx_thread_sleep(10);
	}
}

VOID cdc_acm_reception_callback(struct UX_HOST_CLASS_CDC_ACM_STRUCT *cdc_acm,
		UINT status, UCHAR *reception_buffer, ULONG reception_size)
{
	/* Set the reception pointer to the beginning of the Rx Buffer */
	cdc_acm_reception.ux_host_class_cdc_acm_reception_data_head = cdc_acm_reception.ux_host_class_cdc_acm_reception_data_buffer;
	/* Store the reception size in a global variable */
	block_reception_count = reception_size;

	/* Set NEW_RECEIVED_DATA flag */
	if (tx_event_flags_set(&cdc_acm_eventflag, 0x01, TX_OR) != TX_SUCCESS)
	{
		Error_Handler();
	}
}
/* USER CODE END 1 */
