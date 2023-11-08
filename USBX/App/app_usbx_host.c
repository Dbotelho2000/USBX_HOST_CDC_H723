/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    app_usbx_host.c
 * @author  MCD Application Team
 * @brief   USBX host applicative file
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
#include "app_usbx_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "usb_otg.h"
#include "usart.h"
#include "ux_hcd_stm32.h"
#include "ux_host_cdc_acm.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

static TX_THREAD ux_host_app_thread;

/* USER CODE BEGIN PV */
static TX_THREAD cdc_acm_send_thread;
static TX_THREAD cdc_acm_receive_thread;

TX_EVENT_FLAGS_GROUP cdc_acm_eventflag;
TX_MUTEX cdc_acm_uart_mutex;
UX_HOST_CLASS_CDC_ACM *cdc_acm;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static VOID app_ux_host_thread_entry(ULONG thread_input);
static UINT ux_host_event_callback(ULONG event, UX_HOST_CLASS *current_class, VOID *current_instance);
static VOID ux_host_error_callback(UINT system_level, UINT system_context, UINT error_code);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
 * @brief  Application USBX Host Initialization.
 * @param  memory_ptr: memory pointer
 * @retval status
 */
UINT MX_USBX_Host_Init(VOID *memory_ptr)
{
	UINT ret = UX_SUCCESS;
	UCHAR *pointer;
	TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

	/* USER CODE BEGIN MX_USBX_Host_Init0 */

	/* USER CODE END MX_USBX_Host_Init0 */

	/* Allocate the stack for USBX Memory */
	if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
			USBX_HOST_MEMORY_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
	{
		/* USER CODE BEGIN USBX_ALLOCATE_STACK_ERORR */
		return TX_POOL_ERROR;
		/* USER CODE END USBX_ALLOCATE_STACK_ERORR */
	}

	/* Initialize USBX Memory */
	if (ux_system_initialize(pointer, USBX_HOST_MEMORY_STACK_SIZE, UX_NULL, 0) != UX_SUCCESS)
	{
		/* USER CODE BEGIN USBX_SYSTEM_INITIALIZE_ERORR */
		return UX_ERROR;
		/* USER CODE END USBX_SYSTEM_INITIALIZE_ERORR */
	}

	/* Install the host portion of USBX */
	if (ux_host_stack_initialize(ux_host_event_callback) != UX_SUCCESS)
	{
		/* USER CODE BEGIN USBX_HOST_INITIALIZE_ERORR */
		return UX_ERROR;
		/* USER CODE END USBX_HOST_INITIALIZE_ERORR */
	}

	/* Register a callback error function */
	ux_utility_error_callback_register(&ux_host_error_callback);

	/* Initialize the host cdc acm class */
	if ((ux_host_stack_class_register(_ux_system_host_class_cdc_acm_name,
			ux_host_class_cdc_acm_entry)) != UX_SUCCESS)
	{
		/* USER CODE BEGIN USBX_HOST_CDC_ACM_REGISTER_ERORR */
		return UX_ERROR;
		/* USER CODE END USBX_HOST_CDC_ACM_REGISTER_ERORR */
	}

	/* Allocate the stack for host application main thread */
	if (tx_byte_allocate(byte_pool, (VOID **) &pointer, UX_HOST_APP_THREAD_STACK_SIZE,
			TX_NO_WAIT) != TX_SUCCESS)
	{
		/* USER CODE BEGIN MAIN_THREAD_ALLOCATE_STACK_ERORR */
		return TX_POOL_ERROR;
		/* USER CODE END MAIN_THREAD_ALLOCATE_STACK_ERORR */
	}

	/* Create the host application main thread */
	if (tx_thread_create(&ux_host_app_thread, UX_HOST_APP_THREAD_NAME, app_ux_host_thread_entry,
			0, pointer, UX_HOST_APP_THREAD_STACK_SIZE, UX_HOST_APP_THREAD_PRIO,
			UX_HOST_APP_THREAD_PREEMPTION_THRESHOLD, UX_HOST_APP_THREAD_TIME_SLICE,
			UX_HOST_APP_THREAD_START_OPTION) != TX_SUCCESS)
	{
		/* USER CODE BEGIN MAIN_THREAD_CREATE_ERORR */
		return TX_THREAD_ERROR;
		/* USER CODE END MAIN_THREAD_CREATE_ERORR */
	}

	/* USER CODE BEGIN MX_USBX_Host_Init1 */
	/* Create the CDC Receive Thread */
	tx_byte_allocate(byte_pool, (VOID **)&pointer, 1024, TX_NO_WAIT);
	tx_thread_create(&cdc_acm_receive_thread, "CDC Receive Thread", cdc_acm_receive_thread_entry, 0, pointer, 1024, 30, 30, TX_NO_TIME_SLICE, TX_AUTO_START);

	/* Create the CDC Send Thread */
	tx_byte_allocate(byte_pool, (VOID **)&pointer, 1024, TX_NO_WAIT);
	tx_thread_create(&cdc_acm_send_thread, "CDC Send Thread", cdc_acm_send_thread_entry, 0, pointer, 1024, 15, 15, TX_NO_TIME_SLICE, TX_AUTO_START);

	/* Create the Event Flags and the UART Mutex */
	tx_event_flags_create(&cdc_acm_eventflag, "Event Flag");
	tx_mutex_create(&cdc_acm_uart_mutex, "UART Mutex", TX_INHERIT);

	/* USER CODE END MX_USBX_Host_Init1 */

	return ret;
}

/**
 * @brief  Function implementing app_ux_host_thread_entry.
 * @param  thread_input: User thread input parameter.
 * @retval none
 */
static VOID app_ux_host_thread_entry(ULONG thread_input)
{
	/* USER CODE BEGIN app_ux_host_thread_entry */
	/* Initialize the USB Peripheral */
	MX_USB_OTG_HS_HCD_Init();

	/* Link the USB Peripheral to the USBX Host Controller Driver */
	ux_host_stack_hcd_register(_ux_system_host_hcd_stm32_name, _ux_hcd_stm32_initialize, USB_OTG_HS_PERIPH_BASE, (ULONG)&hhcd_USB_OTG_HS);

	/* Start the Peripheral */
	HAL_HCD_Start(&hhcd_USB_OTG_HS);

	/* USER CODE END app_ux_host_thread_entry */
}

/**
 * @brief  ux_host_event_callback
 *         This callback is invoked to notify application of instance changes.
 * @param  event: event code.
 * @param  current_class: Pointer to class.
 * @param  current_instance: Pointer to class instance.
 * @retval status
 */
UINT ux_host_event_callback(ULONG event, UX_HOST_CLASS *current_class, VOID *current_instance)
{
	UINT status = UX_SUCCESS;

	/* USER CODE BEGIN ux_host_event_callback0 */
	UX_PARAMETER_NOT_USED(current_class);
	UX_PARAMETER_NOT_USED(current_instance);
	/* USER CODE END ux_host_event_callback0 */

	switch (event)
	{
		case UX_DEVICE_INSERTION:

			/* USER CODE BEGIN UX_DEVICE_INSERTION */
			if(current_class->ux_host_class_entry_function == ux_host_class_cdc_acm_entry)
			{
				/* Check if the CDC class is empty */
				if(cdc_acm == UX_NULL)
				{
					/* Save the Class */
					cdc_acm = (UX_HOST_CLASS_CDC_ACM *)current_instance;

					/* Check if this is CDC DATA instance */
					if(cdc_acm->ux_host_class_cdc_acm_bulk_in_endpoint == UX_NULL)
					{
						cdc_acm = UX_NULL;
					}
					else
					{
						tx_mutex_get(&cdc_acm_uart_mutex, TX_WAIT_FOREVER);
						printf("Device Connected \r\n");
						printf("PID: %#x ", (UINT)cdc_acm -> ux_host_class_cdc_acm_device -> ux_device_descriptor.idProduct);
						printf("VID: %#x \r\n", (UINT)cdc_acm -> ux_host_class_cdc_acm_device -> ux_device_descriptor.idVendor);
						tx_mutex_put(&cdc_acm_uart_mutex);
					}
				}
			}
			/* USER CODE END UX_DEVICE_INSERTION */

			break;

		case UX_DEVICE_REMOVAL:

			/* USER CODE BEGIN UX_DEVICE_REMOVAL */
			if((VOID*)cdc_acm == current_instance)
			{
				/* Clear the cdc instance */
				cdc_acm = UX_NULL;
				tx_mutex_get(&cdc_acm_uart_mutex, TX_WAIT_FOREVER);
				printf("Device Disconnected \r\n");
				tx_mutex_put(&cdc_acm_uart_mutex);

				tx_event_flags_set(&cdc_acm_eventflag, 0x01, TX_OR);
			}
			/* USER CODE END UX_DEVICE_REMOVAL */

			break;

		case UX_DEVICE_CONNECTION:

			/* USER CODE BEGIN UX_DEVICE_CONNECTION */

			/* USER CODE END UX_DEVICE_CONNECTION */

			break;

		case UX_DEVICE_DISCONNECTION:

			/* USER CODE BEGIN UX_DEVICE_DISCONNECTION */

			/* USER CODE END UX_DEVICE_DISCONNECTION */

			break;

		default:

			/* USER CODE BEGIN EVENT_DEFAULT */

			/* USER CODE END EVENT_DEFAULT */

			break;
	}

	/* USER CODE BEGIN ux_host_event_callback1 */

	/* USER CODE END ux_host_event_callback1 */

	return status;
}

/**
 * @brief ux_host_error_callback
 *         This callback is invoked to notify application of error changes.
 * @param  system_level: system level parameter.
 * @param  system_context: system context code.
 * @param  error_code: error event code.
 * @retval Status
 */
VOID ux_host_error_callback(UINT system_level, UINT system_context, UINT error_code)
{
	/* USER CODE BEGIN ux_host_error_callback0 */
	UX_PARAMETER_NOT_USED(system_level);
	UX_PARAMETER_NOT_USED(system_context);
	/* USER CODE END ux_host_error_callback0 */

	switch (error_code)
	{
		case UX_DEVICE_ENUMERATION_FAILURE:

			/* USER CODE BEGIN UX_DEVICE_ENUMERATION_FAILURE */

			/* USER CODE END UX_DEVICE_ENUMERATION_FAILURE */

			break;

		case  UX_NO_DEVICE_CONNECTED:

			/* USER CODE BEGIN UX_NO_DEVICE_CONNECTED */

			/* USER CODE END UX_NO_DEVICE_CONNECTED */

			break;

		default:

			/* USER CODE BEGIN ERROR_DEFAULT */

			/* USER CODE END ERROR_DEFAULT */

			break;
	}

	/* USER CODE BEGIN ux_host_error_callback1 */

	/* USER CODE END ux_host_error_callback1 */
}

/* USER CODE BEGIN 1 */
int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFF);
	return ch;
}

/* USER CODE END 1 */
