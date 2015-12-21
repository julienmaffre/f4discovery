/**
* @file 		mems_LIS3DSH.h
* @brief		Header file of MEMS LIS3DSH service.
* @author		Julien
* @version	1.0  
* @details	
*
*	Header file listing the functions required to initialise the MEMS 
* LIS3DSH, set and get particular bits in its registers, set and get
* the value of an entire register and get the X/Y/Z accelerations and
* temperature.
*
*		1. The Timer, interrupts, offset corrections are not supported.
*		2. The initialization of LIS3DSH MEMS goes like this:
*				MEMS_CLK_ENABLE();
*       MEMS_init();
*
*/

#ifndef MEMS_LIS3DSH_H
#define MEMS_LIS3DSH_H

#include <stm32f4xx.h>
#include "spi.h"
#include "gpio.h"
#include "rcc.h"

#define MEMS_SPI					SPI1																///< SPI connected to MEMS

#define MEMS_GPIO_MAIN		GPIOA																///< GPIO used by MEMS
#define MEMS_PIN_SCK			5
#define MEMS_PIN_MISO			6
#define MEMS_PIN_MOSI			7	
#define MEMS_GPIO_CS			GPIOE
#define MEMS_PIN_CS				3

#define MEMS_SPI_AF				5																		///< Mems Alternate Function Number

#define MEMS_GPIO_MAIN_CLK_ENABLE()			GPIOA_CLK_ENABLE();		///< Make sure this is consistent with defines above
#define MEMS_GPIO_CS_CLK_ENABLE()				GPIOE_CLK_ENABLE();

#define MEMS_CLK_ENABLE()								SPI1_CLK_ENABLE()			///< Macro to switch ON the MEMS CLK

// TODO:
// 	- Comments
// 	- Write lists of all registers, bits, etc. (loooooooong)
//  - Test

/*----------------------------------------------------------------------------
   LIS3DSH MEMS Registers Description
 *----------------------------------------------------------------------------*/
 
/* Register addresses */
#define MEMS_INFO_1								0x0D
#define MEMS_INFO_2								0x0E
#define MEMS_WHO_AM_I							0x0F
#define MEMS_CTRL_REG3 						0x23
#define MEMS_CTRL_REG4 						0x20
#define MEMS_CTRL_REG5 						0x24
#define MEMS_CTRL_REG6 						0x25
#define MEMS_STATUS 							0x27

#define MEMS_TEMPERATURE					0x0C
#define MEMS_OFFSET_X							0x10
#define MEMS_OFFSET_Y							0x11
#define MEMS_OFFSET_Z							0x12

#define MEMS_CSHIFT_X							0x13
#define MEMS_CSHIFT_Y							0x14
#define MEMS_CSHIFT_Z							0x15

#define MEMS_LONG_COUNTER_L				0x16
#define MEMS_LONG_COUNTER_H				0x17

#define MEMS_OUT_X_L 							0x28 
#define MEMS_OUT_X_H 							0x29
#define MEMS_OUT_Y_L 							0x2A
#define MEMS_OUT_Y_H 							0x2B 
#define MEMS_OUT_Z_L 							0x2C
#define MEMS_OUT_Z_H 							0x2D

/* Define bits in registers */
#define MEMS_CTRL_REG3_DR_EN 			0x80
#define MEMS_CTRL_REG3_IEA				0x40
#define MEMS_CTRL_REG3_IEL				0x20
#define MEMS_CTRL_REG3_INT2_EN		0x10
#define MEMS_CTRL_REG3_INT1_EN		0x08
#define MEMS_CTRL_REG3_VFILT			0x04
#define MEMS_CTRL_REG3_STRT				0x01

#define MEMS_CTRL_REG4_ODR 				0xF0
#define MEMS_CTRL_REG4_BDU				0x08
#define MEMS_CTRL_REG4_ZEN				0x04       
#define MEMS_CTRL_REG4_YEN				0x02        
#define MEMS_CTRL_REG4_XEN				0x01

#define MEMS_CTRL_REG5_BW 				0xC0
#define MEMS_CTRL_REG5_FSCALE			0x38
#define MEMS_CTRL_REG5_ST					0x06
#define MEMS_CTRL_REG5_SIM				0x01

#define MEMS_CTRL_REG6_BOOT 			0x80
#define MEMS_CTRL_REG6_FIFO_EN		0x40
#define MEMS_CTRL_WTM_EN					0x20
#define MEMS_CTRL_REG6_ADC_IN			0x10
#define MEMS_CTRL_REG6_P1_EMPTY		0x08
#define MEMS_CTRL_REG6_P1_WTM			0x04
#define MEMS_CTRL_REG6_P1_OVERRUN	0x02
#define MEMS_CTRL_REG6_P2_BOOT		0x01

#define MEMS_STATUS_ZYXOR					0x80
#define MEMS_STATUS_ZOR						0x40
#define MEMS_STATUS_YOR						0x20
#define MEMS_STATUS_XOR						0x10
#define MEMS_STATUS_ZYXDA					0x08
#define MEMS_STATUS_ZDA						0x40
#define MEMS_STATUS_YDA						0x20
#define MEMS_STATUS_XDA						0x10


/*----------------------------------------------------------------------------
   LIS3DSH MEMS Methods
 *----------------------------------------------------------------------------*/
 
/**
 * MEMS initialised.
 * This function initialises the MEMS.
 * @par This function must be called after MEMS clock has been enabled.
 */
void MEMS_init(void);

/**
 * MEMS CS set low.
 * This function sets the CS line to low.
 * @par This function is called before communicating with the MEMS.
 */
void MEMS_setCSLow(void);

/**
 * MEMS CS set high.
 * This function sets the CS line to high.
 * @par This function is called after communicating with the MEMS.
 */
void MEMS_setCSHigh(void);

/**
 * MEMS get register value.
 * This function returns the value of the specified MEMS register.
 * @param[in] reg_address Address of the register.
 * @retval uint8_t Value of the 8-bit register.
 */
uint8_t MEMS_getData(uint8_t reg_address);

/**
 * MEMS set register value.
 * This function sets the specified MEMS register to the specified value.
 * @param[in] reg_address Address of the register.
 * @param[in] data Value of the 8-bit register.
 */
void MEMS_setData(uint8_t reg_address, uint8_t data);

/**
 * MEMS get bit(s) value in register.
 * This function gets the value of the specified bit in the specified MEMS register.
 * @param[in] reg_address Address of the register.
 * @param[in] bits Bit(s) to return.
 * @retval uint8_t Value of the bit(s), not shifted.
 * @par Warning: the returned valued needs to be shifted to the right accordingly.
 */
uint8_t MEMS_getBitsInRegister(uint8_t reg_address, uint8_t bits);

/**
 * MEMS set bits value in register.
 * This function sets the specified bits in the specified MEMS register.
 * @param[in] reg_address Address of the register.
 * @param[in] bit Bits to set.
 */
void MEMS_setBitsInRegister(uint8_t reg_address, uint8_t bit);

/**
 * MEMS set bits value in register.
 * This function sets the specified bits in the specified MEMS register to the specified value.
 * @param[in] reg_address Address of the register.
 * @param[in] bit Bits to set.
 * @param[in] data Value to set the Bits to.
 * @par Warning: the called has to shift data to the right accordingly beforehand.
 */
void MEMS_setValueBitsInRegister(uint8_t reg_address, uint8_t bits, uint8_t data);

/**
 * MEMS get X acceleration.
 * This function returns the X-axis acceleration.
 * @retval uint16_t X acceleration.
 */
uint16_t MEMS_getOutX(void);

/**
 * MEMS get Y acceleration.
 * This function returns the Y-axis acceleration.
 * @retval uint16_t Y acceleration.
 */
uint16_t MEMS_getOutY(void);

/**
 * MEMS get Z acceleration.
 * This function returns the Z-axis acceleration.
 * @retval uint16_t Z acceleration.
 */
uint16_t MEMS_getOutZ(void);

/**
 * MEMS get temperature.
 * This function returns the temperature.
 * @retval uint16_t X acceleration.
 */
uint8_t MEMS_getTemperature(void);

#endif
