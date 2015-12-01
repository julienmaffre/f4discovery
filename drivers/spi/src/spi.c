#include "spi.h"

void SPI_initUnidirectionalData2LineUni(SPI_TypeDef * SPI) 
{
	SPI->CR1 &= ~SPI_CR1_BIDIMODE;
}

void SPI_initBidirectionalData2LineUni(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_BIDIMODE;
}

// Receive-only mode
void SPI_initBidirectionalOutputDisabled(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_BIDIOE;
}	

void SPI_initBidirectionalOutputEnabled(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_BIDIOE;
}

// Transmit and Receive
void SPI_initUnidirectionalFullDuplex(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_RXONLY;
}

// Receive-only mode
void SPI_initUnidirectionalOutputDisabled(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_RXONLY;
}

void SPI_initHardwareCRCDisabled(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_CRCEN;
}
	
void SPI_initHardwareCRCEnabled(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_CRCEN;
}

void SPI_initCRCDataPhase(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_CRCNEXT;
}

void SPI_initCRCTransferNext(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_CRCNEXT;
}

void SPI_initDataFrameFormat8b(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_DFF;
}

void SPI_initDataFrameFormat16b(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_DFF;
}

void SPI_initSoftwareSlaveMgmtDisabled(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_SSM;
}

void SPI_initSoftwareSlaveMgmtEnabled(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_SSM;
}	

void SPI_initSetInternalSlaveSelectLow(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_SSI;
}

void SPI_initSetInternalSlaveSelectHigh(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_SSI;
}

void SPI_initFrameFormatMSBFirst(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_LSBFIRST;
}

void SPI_initFrameFormatLSBFirst(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_LSBFIRST;
}

void SPI_initBaudRate(SPI_TypeDef * SPI, uint8_t SPI_BaudRatePrescaler)
{
	SPI->CR1 &= ~SPI_CR1_BR;
	SPI->CR1 |= (SPI_BaudRatePrescaler << 3);
}

void SPI_initSlaveConfiguration(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_MSTR;
}

void SPI_initMasterConfiguration(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_MSTR;	
}

void SPI_initClockPolarityIdleLow(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_CPOL;	
}

void SPI_initClockPolarityIdleHigh(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_CPOL;
}

void SPI_initClockPhaseEdgeOne(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_CPHA;	
}
void SPI_initClockPhaseEdgeTwo(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_CPHA;	
}

void SPI_disable(SPI_TypeDef * SPI)
{
	SPI->CR1 &= ~SPI_CR1_SPE;
}

void SPI_enable(SPI_TypeDef * SPI)
{
	SPI->CR1 |= SPI_CR1_SPE;
}

uint16_t SPI_readData(SPI_TypeDef * SPI)
{
	return SPI->DR;
}

void SPI_writeData(SPI_TypeDef * SPI, uint16_t data) 
{
	SPI->DR = data;
}

bool SPI_hasDataToReceive(SPI_TypeDef * SPI)
{
	if ((SPI->SR & SPI_SR_RXNE) == 0x0)
		return false;
	else 
		return true;
}

bool SPI_hasDataToSend(SPI_TypeDef * SPI)
{
	if ((SPI->SR & SPI_SR_TXE) == 0x0)
		return true;
	else 
		return false;
}

bool SPI_isBusy(SPI_TypeDef * SPI)
{
	if ((SPI->SR & SPI_SR_BSY) == 0x0)
		return false;
	else 
		return true;
}

