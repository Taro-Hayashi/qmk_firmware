#pragma once
#define HAL_USE_ADC FALSE
#define HAL_USE_I2C FALSE
#define HAL_USE_SPI TRUE

#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
#define SERIAL_USB_BUFFERS_SIZE 256

#include_next <halconf.h>
