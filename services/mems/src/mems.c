#include "mems.h"

void MEMS_init(void) 
{
	MEMS_GPIO_MAIN_CLK_ENABLE();
	MEMS_GPIO_CS_CLK_ENABLE();
	
	GPIO_initAlternate(MEMS_GPIO_MAIN, MEMS_PIN_SCK);
	GPIO_initAlternate(MEMS_GPIO_MAIN, MEMS_PIN_MISO);
	GPIO_initAlternate(MEMS_GPIO_MAIN, MEMS_PIN_MOSI);
	GPIO_initOutputMediumspeed(MEMS_GPIO_MAIN, MEMS_PIN_SCK);
	GPIO_initOutputMediumspeed(MEMS_GPIO_MAIN, MEMS_PIN_MISO);
	GPIO_initOutputMediumspeed(MEMS_GPIO_MAIN, MEMS_PIN_MOSI);
	GPIO_initOutputPushpull(MEMS_GPIO_MAIN, MEMS_PIN_SCK);
	GPIO_initOutputPushpull(MEMS_GPIO_MAIN, MEMS_PIN_MISO);
	GPIO_initOutputPushpull(MEMS_GPIO_MAIN, MEMS_PIN_MOSI);
	GPIO_initNopull(MEMS_GPIO_MAIN, MEMS_PIN_SCK);
	GPIO_initNopull(MEMS_GPIO_MAIN, MEMS_PIN_MISO);
	GPIO_initNopull(MEMS_GPIO_MAIN, MEMS_PIN_MOSI);
	
	GPIO_initOutput(MEMS_GPIO_CS, MEMS_PIN_CS);
	GPIO_initOutputMediumspeed(MEMS_GPIO_CS, MEMS_PIN_CS);
	GPIO_initOutputPushpull(MEMS_GPIO_CS, MEMS_PIN_CS);
	GPIO_initPullup(MEMS_GPIO_CS, MEMS_PIN_CS);
	GPIO_setPin(MEMS_GPIO_CS, MEMS_PIN_CS);	
	
	// Assigns GPIO Alternate Function to SPI
	MEMS_GPIO_MAIN->AFR[0] |= (MEMS_SPI_AF << MEMS_PIN_SCK*4);
	MEMS_GPIO_MAIN->AFR[0] |= (MEMS_SPI_AF << MEMS_PIN_MISO*4);
	MEMS_GPIO_MAIN->AFR[0] |= (MEMS_SPI_AF << MEMS_PIN_MOSI*4);
	
	SPI_initUnidirectionalData2LineUni(MEMS_SPI); 							// essential
	SPI_initBaudRate(MEMS_SPI, SPI_BaudRatePrescaler_2);
	SPI_initClockPolarityIdleHigh(MEMS_SPI);
	SPI_initClockPhaseEdgeTwo(MEMS_SPI);
	SPI_initDataFrameFormat8b(MEMS_SPI);
	SPI_initFrameFormatMSBFirst(MEMS_SPI);
	SPI_initSoftwareSlaveMgmtEnabled(MEMS_SPI);
	SPI_initSetInternalSlaveSelectHigh(MEMS_SPI);
	SPI_initMasterConfiguration(MEMS_SPI);
	SPI_enable(MEMS_SPI);
	
	GPIO_resetPin(MEMS_GPIO_CS, MEMS_PIN_CS);
}

void MEMS_setCSLow(void)
{
	GPIO_resetPin(MEMS_GPIO_CS, MEMS_PIN_CS);
}

void MEMS_setCSHigh(void)
{
	GPIO_setPin(MEMS_GPIO_CS, MEMS_PIN_CS);
}

uint8_t MEMS_getData(uint8_t address)
{
	uint8_t read_address = 0x80 | address;
	uint8_t tmp_rcvd;
	
	MEMS_setCSLow();
	
	while (SPI_hasDataToSend(MEMS_SPI)); 							// While there is something in Tx Reg...
	SPI_writeData(MEMS_SPI, read_address);
	while (!SPI_hasDataToReceive(MEMS_SPI)); 					// While there is nothing in Rx Reg...
	tmp_rcvd = (uint8_t) SPI_readData(MEMS_SPI);
	while (SPI_hasDataToSend(MEMS_SPI)); 							// While there is something in Tx Reg...
	SPI_writeData(MEMS_SPI, 0x0);		
	while (!SPI_hasDataToReceive(MEMS_SPI)); 					// While there is nothing in Rx Reg...

	MEMS_setCSHigh();	
	
	return ((uint8_t) SPI_readData(MEMS_SPI));
}

void MEMS_setData(uint8_t address, uint8_t data)
{
	uint8_t write_address = address;
	uint8_t tmp_rcvd;
	
	MEMS_setCSLow();
	
	while (SPI_hasDataToSend(MEMS_SPI)); 							// While there is something in Tx Reg...
	SPI_writeData(MEMS_SPI, write_address);
	while (!SPI_hasDataToReceive(MEMS_SPI)); 					// While there is nothing in Rx Reg...
	tmp_rcvd = (uint8_t) SPI_readData(MEMS_SPI);
	while (SPI_hasDataToSend(MEMS_SPI)); 							// While there is something in Tx Reg...
	SPI_writeData(MEMS_SPI, data);		
	while (!SPI_hasDataToReceive(MEMS_SPI)); 					// While there is nothing in Rx Reg...
	tmp_rcvd = (uint8_t) SPI_readData(MEMS_SPI);

	MEMS_setCSHigh();	
}

