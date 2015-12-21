#include "mems_lis3dsh.h"

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

uint8_t MEMS_getData(uint8_t reg_address)
{
	uint8_t read_address = 0x80 | reg_address;
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

void MEMS_setData(uint8_t reg_address, uint8_t data)
{
	uint8_t write_address = reg_address;
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

uint8_t MEMS_getBitsInRegister(uint8_t reg_address, uint8_t bits)
{
	return (MEMS_getData(reg_address) & bits);
}

void MEMS_setBitsInRegister(uint8_t reg_address, uint8_t bit)
{
	uint8_t reg_value = MEMS_getData(reg_address);
	reg_value |= bit;
	MEMS_setData(reg_address, reg_value);	
}

void MEMS_setValueBitsInRegister(uint8_t reg_address, uint8_t bits, uint8_t data)
{
	uint8_t reg_value =  MEMS_getData(reg_address);
	reg_value &= ~bits;
	reg_value |= data; // caller has to shift data to the left accordingly to bits
	MEMS_setData(reg_address, reg_value);		
}

uint16_t MEMS_getOutX(void)
{
	uint16_t rcvd_x = 0x0000;
	rcvd_x = MEMS_getData(MEMS_OUT_X_H);
	rcvd_x = (rcvd_x << 8) | MEMS_getData(MEMS_OUT_X_L);
	
	return rcvd_x;
}

uint16_t MEMS_getOutY(void)
{
	uint16_t rcvd_y = 0x0000;
	rcvd_y = MEMS_getData(MEMS_OUT_Y_H);
	rcvd_y = (rcvd_y << 8) | MEMS_getData(MEMS_OUT_Y_L);
	
	return rcvd_y;
}

uint16_t MEMS_getOutZ(void)
{
	uint16_t rcvd_z = 0x0000;
	rcvd_z = MEMS_getData(MEMS_OUT_Z_H);
	rcvd_z = (rcvd_z << 8) | MEMS_getData(MEMS_OUT_Z_L);
	
	return rcvd_z;
}

uint8_t MEMS_getTemperature(void)
{
	return MEMS_getData(MEMS_TEMPERATURE);
}

