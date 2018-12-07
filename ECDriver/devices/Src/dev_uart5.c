/**
 * @file	dev_uart5.c
 * @brief	Description of UART5 driver file.
 * @author	Eggcar
*/

#include "ec_dev.h"
#include "ec_drv_stm32_usart.h"
#include "ec_file.h"
#include "ec_lock.h"

#include <stdint.h>

static file_opts_t _opts_stm32_uart5 = {
	.open = stm32_usart_open,
	.read = stm32_usart_read,
	.write = stm32_usart_write,
	.ioctl = stm32_usart_ioctl,
	.lseek = stm32_usart_lseek,
	.mmap = NULL,
	.close = stm32_usart_close,
};

static LL_USART_InitTypeDef _init_stm32_uart5 = {
	.BaudRate = 115200,
	.DataWidth = LL_USART_DATAWIDTH_8B,
	.StopBits = LL_USART_STOPBITS_1,
	.Parity = LL_USART_PARITY_NONE,
	.TransferDirection = LL_USART_DIRECTION_TX_RX,
	.HardwareFlowControl = LL_USART_HWCONTROL_NONE,
	.OverSampling = LL_USART_OVERSAMPLING_16,
};

static LL_GPIO_InitTypeDef _init_stm32_uart5_tx = {
	.Pin = LL_GPIO_PIN_12,
	.Mode = LL_GPIO_MODE_ALTERNATE,
	.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
	.OutputType = LL_GPIO_OUTPUT_PUSHPULL,
	.Pull = LL_GPIO_PULL_UP,
	.Alternate = LL_GPIO_AF_8,
};

static LL_GPIO_InitTypeDef _init_stm32_uart5_rx = {
	.Pin = LL_GPIO_PIN_2,
	.Mode = LL_GPIO_MODE_ALTERNATE,
	.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
	.OutputType = LL_GPIO_OUTPUT_PUSHPULL,
	.Pull = LL_GPIO_PULL_UP,
	.Alternate = LL_GPIO_AF_8,
};

static config_stm32_usart_t _conf_stm32_uart5 = {
	.clock_bus = USART_Bus_APB1,
	.clock_ena_bit = LL_APB1_GRP1_PERIPH_UART5,
	.rx_buffer_size = 256,
	.tx_buffer_size = 256,
	.rx_pin_conf = &_init_stm32_uart5_rx,
	.tx_pin_conf = &_init_stm32_uart5_tx,
	.rx_io_port = GPIOD,
	.tx_io_port = GPIOC,
	.irqn = UART5_IRQn,
	.usart_conf = &_init_stm32_uart5,
};

static dev_stm32_usart_t _device_descriptor_stm32_uart5 = {
	.handle = UART5,
	.config = &_conf_stm32_uart5,
};

ec_dev_t device_stm32_uart5 = {
	.dev_name = "uart5",
	.dev_type = e_devt_STREAM,
	.private_data = (void *)(&_device_descriptor_stm32_uart5),
};

file_t driver_stm32_uart5 = {
	.file_name = "/drivers/stm32/uart5",
	.file_refs = 0,
	.file_lock = e_Unlocked,
	.file_opts = &_opts_stm32_uart5,
	.file_content = (void *)(&device_stm32_uart5),
};