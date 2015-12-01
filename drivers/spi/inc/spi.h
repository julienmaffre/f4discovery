#ifndef SPI_H
#define SPI_H

#include <stm32f4xx.h>
#include <stdbool.h>

#define SPI_BaudRatePrescaler_2         ((uint8_t)0x0000)
#define SPI_BaudRatePrescaler_4         ((uint8_t)0x0001)
#define SPI_BaudRatePrescaler_8         ((uint8_t)0x0002)
#define SPI_BaudRatePrescaler_16        ((uint8_t)0x0003)
#define SPI_BaudRatePrescaler_32        ((uint8_t)0x0004)
#define SPI_BaudRatePrescaler_64        ((uint8_t)0x0005)
#define SPI_BaudRatePrescaler_128       ((uint8_t)0x0006)
#define SPI_BaudRatePrescaler_256       ((uint8_t)0x0007)

/*----------------------------------------------------------------------------
  SPI control register 1 (SPI_CR1)
 *----------------------------------------------------------------------------*/

void SPI_initUnidirectionalData2LineUni(SPI_TypeDef * SPI); 
void SPI_initBidirectionalData2LineUni(SPI_TypeDef * SPI); 

void SPI_initBidirectionalOutputDisabled(SPI_TypeDef * SPI); 
void SPI_initBidirectionalOutputEnabled(SPI_TypeDef * SPI); 

void SPI_initUnidirectionalFullDuplex(SPI_TypeDef * SPI); 
void SPI_initUnidirectionalOutputDisabled(SPI_TypeDef * SPI); 

void SPI_initHardwareCRCDisabled(SPI_TypeDef * SPI); 
void SPI_initHardwareCRCEnabled(SPI_TypeDef * SPI); 

void SPI_initCRCDataPhase(SPI_TypeDef * SPI); 
void SPI_initCRCTransferNext(SPI_TypeDef * SPI); 

void SPI_initDataFrameFormat8b(SPI_TypeDef * SPI); 
void SPI_initDataFrameFormat16b(SPI_TypeDef * SPI); 

void SPI_initSoftwareSlaveMgmtDisabled(SPI_TypeDef * SPI); 
void SPI_initSoftwareSlaveMgmtEnabled(SPI_TypeDef * SPI); 

void SPI_initSetInternalSlaveSelectLow(SPI_TypeDef * SPI); 
void SPI_initSetInternalSlaveSelectHigh(SPI_TypeDef * SPI); 

void SPI_initFrameFormatMSBFirst(SPI_TypeDef * SPI); 
void SPI_initFrameFormatLSBFirst(SPI_TypeDef * SPI);

void SPI_initBaudRate(SPI_TypeDef * SPI, uint8_t SPI_BaudRatePrescaler); 

void SPI_initMasterConfiguration(SPI_TypeDef * SPI);
void SPI_initSlaveConfiguration(SPI_TypeDef * SPI);

void SPI_initClockPolarityIdleLow(SPI_TypeDef * SPI);
void SPI_initClockPolarityIdleHigh(SPI_TypeDef * SPI);

void SPI_initClockPhaseEdgeOne(SPI_TypeDef * SPI);
void SPI_initClockPhaseEdgeTwo(SPI_TypeDef * SPI);

void SPI_disable(SPI_TypeDef * SPI); 
void SPI_enable(SPI_TypeDef * SPI);

uint16_t SPI_readData(SPI_TypeDef * SPI);
void SPI_writeData(SPI_TypeDef * SPI, uint16_t data);

/* Status Register */
bool SPI_hasDataToReceive(SPI_TypeDef * SPI);
bool SPI_hasDataToSend(SPI_TypeDef * SPI);
bool SPI_isBusy(SPI_TypeDef * SPI);


// TODO:
// 	- Comments
// 	- Status register checks: done. A number of status are not supported. see ref p.907
//  - See CR2: interrupts 
// 	- I2S and CRC and DMA not supported

#endif
