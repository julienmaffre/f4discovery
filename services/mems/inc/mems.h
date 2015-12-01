#ifndef MEMS_H
#define MEMS_H

#include <stm32f4xx.h>
#include "spi.h"
#include "gpio.h"
#include "rcc.h"

#define MEMS_SPI			SPI1				///< SPI connected to Mems

#define MEMS_GPIO_MAIN		GPIOA
#define MEMS_PIN_SCK			5
#define MEMS_PIN_MISO			6
#define MEMS_PIN_MOSI			7	
#define MEMS_GPIO_CS			GPIOE
#define MEMS_PIN_CS				3

#define MEMS_SPI_AF				5				///< Mems Alternate Function Number


#define MEMS_GPIO_MAIN_CLK_ENABLE()			GPIOA_CLK_ENABLE();				///< Make sure this is consistent with defines above
#define MEMS_GPIO_CS_CLK_ENABLE()				GPIOE_CLK_ENABLE();

#define MEMS_CLK_ENABLE()					SPI1_CLK_ENABLE()		///< Macro to switch ON the MEMS CLK

void MEMS_init(void);

void MEMS_setCSLow(void);
void MEMS_setCSHigh(void);

uint8_t MEMS_getData(uint8_t address);
void MEMS_setData(uint8_t address, uint8_t data);

// TODO:
// 	- Comments
//  - Make everything looks nice
// 	- Set particular bits in registers (huge work but make it elegant with a template function that sets bits x..x' in
//		register y (then create one function per register/bit pair that call this template function)

#endif




