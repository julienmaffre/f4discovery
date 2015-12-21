/**
* @file 		spi.h
* @brief		Header file of SPI drivers.
* @author		Julien
* @version	1.0  
* @details	
*
*	Header file listing the functions required to initialise the SPI,
* read the Tx, Rx and isBusy status and read and write data in the
* data registers.
*
*		1. The I2S mode, the CRC, the interrupts and the DMA functions 
*		are not supported.
*		2. Use the function defined in the RCC drivers to set the SPI 
*		clocks.
*				ex: SPI1_CLK_ENABLE();
*		3. The initialization of the SPI for the LIS3DSH MEMS goes like this:
*				SPI1_CLK_ENABLE();
*				// Init GPIO corresponding to SPI lines (clock gpio, init gpio)
*				// Set desired GPIO to Alternate Functions
*				SPI_initUnidirectionalData2LineUni(MEMS_SPI); 							
*				SPI_initBaudRate(MEMS_SPI, SPI_BaudRatePrescaler_2);
*				SPI_initClockPolarityIdleHigh(MEMS_SPI);
*				SPI_initClockPhaseEdgeTwo(MEMS_SPI);
*				SPI_initDataFrameFormat8b(MEMS_SPI);
*				SPI_initFrameFormatMSBFirst(MEMS_SPI);
*				SPI_initSoftwareSlaveMgmtEnabled(MEMS_SPI);
*				SPI_initSetInternalSlaveSelectHigh(MEMS_SPI);
*				SPI_initMasterConfiguration(MEMS_SPI);
*				SPI_enable(MEMS_SPI);
*/

#ifndef SPI_H
#define SPI_H

#include <stm32f4xx.h>
#include <stdbool.h>

/* Define the different values of SPI Baud Rate Prescaler */
#define SPI_BaudRatePrescaler_2         ((uint8_t)0x00)
#define SPI_BaudRatePrescaler_4         ((uint8_t)0x01)
#define SPI_BaudRatePrescaler_8         ((uint8_t)0x02)
#define SPI_BaudRatePrescaler_16        ((uint8_t)0x03)
#define SPI_BaudRatePrescaler_32        ((uint8_t)0x04)
#define SPI_BaudRatePrescaler_64        ((uint8_t)0x05)
#define SPI_BaudRatePrescaler_128       ((uint8_t)0x06)
#define SPI_BaudRatePrescaler_256       ((uint8_t)0x07)

/*----------------------------------------------------------------------------
  SPI control register 1 (SPI_CR1)
 *----------------------------------------------------------------------------*/
 
/**
 * SPI disabled.
 * This function resets the SPE bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 * @par This function must be called after SPI has been initialised.
 */
void SPI_disable(SPI_TypeDef * SPI); 

/**
 * SPI enabled.
 * This function resets the SPE bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 * @par This function must be called after SPI has been initialised.
 */
void SPI_enable(SPI_TypeDef * SPI);

/**
 * SPI set as unidirectional.
 * This function resets the BIDIMODE bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initUnidirectionalData2LineUni(SPI_TypeDef * SPI);

/**
 * SPI set as bidirectional.
 * This function sets the BIDIMODE bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initBidirectionalData2LineUni(SPI_TypeDef * SPI); 

/**
 * SPI output disabled (in bidirectional mode).
 * This function resets the BIDIOE bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initBidirectionalOutputDisabled(SPI_TypeDef * SPI); 

/**
 * SPI output enabled (in bidirectional mode).
 * This function sets the BIDIOE bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initBidirectionalOutputEnabled(SPI_TypeDef * SPI); 

/**
 * SPI full duplex (in unidirectional mode).
 * This function resets the RXONLY bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initUnidirectionalFullDuplex(SPI_TypeDef * SPI); 

/**
 * SPI output disabled (in unidirectional mode).
 * This function sets the RXONLY bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initUnidirectionalOutputDisabled(SPI_TypeDef * SPI); 

/**
 * SPI hardware CRC disabled.
 * This function resets the CRCEN bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initHardwareCRCDisabled(SPI_TypeDef * SPI); 

/**
 * SPI hardware CRC enabled.
 * This function sets the CRCEN bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initHardwareCRCEnabled(SPI_TypeDef * SPI); 

/**
 * SPI no CRC phase.
 * This function resets the CRCNEXT bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initCRCDataPhase(SPI_TypeDef * SPI);

/**
 * SPI next transfer is CRC.
 * This function sets the CRCNEXT bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initCRCTransferNext(SPI_TypeDef * SPI); 

/**
 * SPI 8-bit data frame format.
 * This function resets the DFF bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initDataFrameFormat8b(SPI_TypeDef * SPI); 

/**
 * SPI 16-bit data frame format.
 * This function sets the DFF bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initDataFrameFormat16b(SPI_TypeDef * SPI); 

/**
 * SPI software slave management disabled.
 * This function resets the SSM bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initSoftwareSlaveMgmtDisabled(SPI_TypeDef * SPI); 

/**
 * SPI software slave management enabled.
 * This function sets the SSM bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initSoftwareSlaveMgmtEnabled(SPI_TypeDef * SPI); 

/**
 * SPI internal slave select low state.
 * This function resets the SSI bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initSetInternalSlaveSelectLow(SPI_TypeDef * SPI); 

/**
 * SPI internal slave select high state.
 * This function sets the SSI bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initSetInternalSlaveSelectHigh(SPI_TypeDef * SPI); 

/**
 * SPI MSB transmitted first.
 * This function resets the LSBFIRST bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initFrameFormatMSBFirst(SPI_TypeDef * SPI); 

/**
 * SPI LSB transmitted first.
 * This function sets the LSBFIRST bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initFrameFormatLSBFirst(SPI_TypeDef * SPI);

/**
 * SPI baud rate set as desired value.
 * This function sets the BR[2:0] bits of the SPI CR1 register based on the SPI_BaudRatePrescaler argument.
 * @param[in]	SPI SPI to initialize.
 * @param[in]	SPI_BaudRatePrescaler Value of the baud rate prescaler (see SPI_BaudRatePrescaler_{2~256} defines)
 */
void SPI_initBaudRate(SPI_TypeDef * SPI, uint8_t SPI_BaudRatePrescaler); 

/**
 * SPI set as master.
 * This function resets the MSTR bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initMasterConfiguration(SPI_TypeDef * SPI);

/**
 * SPI set as slave.
 * This function sets the MSTR bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initSlaveConfiguration(SPI_TypeDef * SPI);

/**
 * SPI clock set to 0 when idle.
 * This function resets the CPOL bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initClockPolarityIdleLow(SPI_TypeDef * SPI);

/**
 * SPI clock set to 1 when idle.
 * This function sets the CPOL bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initClockPolarityIdleHigh(SPI_TypeDef * SPI);

/**
 * SPI first clock transition captured.
 * This function resets the CPHA bit of the SPI CR1 register (0b0).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initClockPhaseEdgeOne(SPI_TypeDef * SPI);

/**
 * SPI second clock transition captured.
 * This function sets the CPHA bit of the SPI CR1 register (0b1).
 * @param[in]	SPI SPI to initialize.
 */
void SPI_initClockPhaseEdgeTwo(SPI_TypeDef * SPI);


/*----------------------------------------------------------------------------
  SPI status register (SPI_SR)
 *----------------------------------------------------------------------------*/

/**
 * SPI has data to receive.
 * This function returns true if the SPI has data to receive (based on RXNE bit in SPI SR register).
 * @param[in]	SPI SPI to read.
 * @retval true SPI has data to receive.
 * @retval false SPI hasn't got data to receive.
 */
bool SPI_hasDataToReceive(SPI_TypeDef * SPI);

/**
 * SPI has data to send.
 * This function returns true if the SPI has data to send (based on TXE bit in SPI SR register).
 * @param[in]	SPI SPI to read.
 * @retval true SPI has data to send.
 * @retval false SPI hasn't got data to send.
 */
bool SPI_hasDataToSend(SPI_TypeDef * SPI);

/**
 * SPI is busy.
 * This function returns true if the SPI is busy (based on BSY bit in SPI SR register).
 * @param[in]	SPI SPI to read.
 * @retval true SPI is busy or Tx buffer is not empty.
 * @retval false SPI is idle.
 */
bool SPI_isBusy(SPI_TypeDef * SPI);


/*----------------------------------------------------------------------------
  SPI data register (SPI_DR)
 *----------------------------------------------------------------------------*/

/**
 * Read data from SPI Rx register.
 * This function returns the value of the SPI Rx data register.
 * @param[in]	SPI SPI to read.
 * @retval uint16_t Value of the SPI Rx data register.
 */
uint16_t SPI_readData(SPI_TypeDef * SPI);

/**
 * Write and Send data in SPI Tx register.
 * This function writes the desired value in the SPI Tx register.
 * @param[in]	SPI SPI to write.
 * @param[in]	data Data to write in the SPI Tx register.
 */
void SPI_writeData(SPI_TypeDef * SPI, uint16_t data);

#endif
