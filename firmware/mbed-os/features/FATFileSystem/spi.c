
/**
* \file
*         spi driver
* \author
*         Nguyen Van Hai <blue@ambo.com.vn>
*/
#include "spi.h"

void SPI_InitLowFreq(uint8_t channel)
{
	if(channel == 2)
	{
		RCC->APB1ENR |=  RCC_APB1ENR_SPI2EN;	/*enable clock for SPI2*/
		GPIOB->CRH	 &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13 | 
											GPIO_CRH_MODE14 | GPIO_CRH_CNF14 | 
											GPIO_CRH_MODE15 | GPIO_CRH_CNF15); // Clear PB13, PB14, PB15 
		HAL_SPI1_CS_SET_OUTPUT;
		HAL_SPI1_CS_DEASSERT;							
		GPIOB->CRH   |=   GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1; // PB13 Alternate function output push-pull
		GPIOB->CRH   |=   GPIO_CRH_CNF14_1 | GPIO_CRH_MODE14_0 | GPIO_CRH_MODE14_1; // PB14 Alternate function output push-pull
		GPIOB->CRH   |=   GPIO_CRH_CNF15_1 | GPIO_CRH_MODE15_0 | GPIO_CRH_MODE15_1; // PB15 Alternate function output push-pull
		/* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
		SPI2->CR1 &= SPI_CR1_CLEAR_Mask;
		SPI2->CR1 |= SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_BR_2 | SPI_CR1_SSI | SPI_CR1_SSM;
		/* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
		SPI2->I2SCFGR &= SPI_Mode_Select;		
	/*---------------------------- SPIx CRCPOLY Configuration --------------------*/
		/* Write to SPIx CRCPOLY */
		SPI2->CRCPR = 7;
		/* Enable the selected SPI peripheral */
		SPI2->CR1 |= SPI_CR1_SPE;
	}
	else if(channel == 1)
	{
		
		RCC->APB2ENR |=  RCC_APB2ENR_SPI1EN;	/*enable clock for SPI1*/
		//SPI1 Init
		GPIOA->CRL 	 &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5 | 
											GPIO_CRL_MODE6 | GPIO_CRL_CNF6 | 
											GPIO_CRL_MODE7 | GPIO_CRL_CNF7); // Clear PA5, PA6, PA7 
		HAL_SPI1_CS_SET_OUTPUT;
		SPI_SD_CS_SET_OUTPUT;
		SPI_SD_CS_PIN_SET;
		HAL_SPI1_CS_DEASSERT;							
		GPIOA->CRL   |=   GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1; // PB5 Alternate function output push-pull
		GPIOA->CRL   |=   GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1; // PB6 Alternate function output push-pull
		GPIOA->CRL   |=   GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1; // PB7 Alternate function output push-pull
		
			/* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
		SPI1->CR1 &= SPI_CR1_CLEAR_Mask;
		SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_BR_2 | SPI_CR1_SSI | SPI_CR1_SSM;// | SPI_CR1_CPHA | SPI_CR1_CPOL;
		/* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
		SPI1->I2SCFGR &= SPI_Mode_Select;		
	/*---------------------------- SPIx CRCPOLY Configuration --------------------*/
		/* Write to SPIx CRCPOLY */
		SPI1->CRCPR = 7;
		/* Enable the selected SPI peripheral */
		SPI1->CR1 |= SPI_CR1_SPE;
	}
}

void SPI_InitHighFreq(uint8_t channel)
{
	if(channel == 2)
	{
		RCC->APB1ENR |=  RCC_APB1ENR_SPI2EN;	/*enable clock for SPI1*/
		GPIOB->CRH 	 &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13 | 
											GPIO_CRH_MODE14 | GPIO_CRH_CNF14 | 
											GPIO_CRH_MODE15 | GPIO_CRH_CNF15); // Clear PB13, PB14, PB15 
		HAL_SPI1_CS_SET_OUTPUT;
		HAL_SPI1_CS_DEASSERT;							
		GPIOB->CRH   |=   GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1; // PB13 Alternate function output push-pull
		GPIOB->CRH   |=   GPIO_CRH_CNF14_1 | GPIO_CRH_MODE14_0 | GPIO_CRH_MODE14_1; // PB14 Alternate function output push-pull
		GPIOB->CRH   |=   GPIO_CRH_CNF15_1 | GPIO_CRH_MODE15_0 | GPIO_CRH_MODE15_1; // PB15 Alternate function output push-pull
		/* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
		SPI2->CR1 &= SPI_CR1_CLEAR_Mask;
		SPI2->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM;
		/* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
		SPI2->I2SCFGR &= SPI_Mode_Select;		
	/*---------------------------- SPIx CRCPOLY Configuration --------------------*/
		/* Write to SPIx CRCPOLY */
		SPI2->CRCPR = 7;
		/* Enable the selected SPI peripheral */
		SPI2->CR1 |= SPI_CR1_SPE;
	}
	else if(channel == 1)
	{
		RCC->APB2ENR |=  RCC_APB2ENR_SPI1EN;	/*enable clock for SPI1*/
		//SPI1 Init
		GPIOA->CRL 	 &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5 | 
											GPIO_CRL_MODE6 | GPIO_CRL_CNF6 | 
											GPIO_CRL_MODE7 | GPIO_CRL_CNF7); // Clear PA5, PA6, PA7 
		HAL_SPI1_CS_SET_OUTPUT;
		HAL_SPI1_CS_DEASSERT;							
		GPIOA->CRL   |=   GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1; // PB5 Alternate function output push-pull
		GPIOA->CRL   |=   GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1; // PB6 Alternate function output push-pull
		GPIOA->CRL   |=   GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1; // PB7 Alternate function output push-pull
		
			/* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
		SPI1->CR1 &= SPI_CR1_CLEAR_Mask;
		SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM;// | SPI_CR1_CPHA | SPI_CR1_CPOL;
		/* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
		SPI1->I2SCFGR &= SPI_Mode_Select;		
	/*---------------------------- SPIx CRCPOLY Configuration --------------------*/
		/* Write to SPIx CRCPOLY */
		SPI1->CRCPR = 7;
		/* Enable the selected SPI peripheral */
		SPI1->CR1 |= SPI_CR1_SPE;
	}
}


void SPI_DeInit(void)
{
	//SPI1 Init
	GPIOA->CRL 	 &= ~(
										GPIO_CRL_MODE5 | GPIO_CRL_CNF5 | 
										GPIO_CRL_MODE6 | GPIO_CRL_CNF6 | 
										GPIO_CRL_MODE7 | GPIO_CRL_CNF7); // Clear PB4,PB5, PB6, PB7 
	HAL_SPI1_CS_SET_INPUT;
	RCC->APB2ENR &=  ~RCC_APB2ENR_SPI1EN;	/*enable clock for SPI1*/
}

uint8_t halSpiWriteByte(SPI_TypeDef* SPIx,uint8_t data)
{
	uint32_t timeOut = SPI_TIMEOUT;
	uint8_t rc;
	SPIx->DR = data;
	while((!(SPIx->SR & SPI_SR_RXNE)) && (timeOut--));
	rc = SPIx->DR;
	printf("%02X",rc);
	return rc;
}

void halSpiWriteMutilByte(const unsigned char* buf,uint32_t len)
{
	uint32_t c = len / 2;
	unsigned char rc;
	const unsigned char *p = buf;
	uint32_t timeOut = SPI_TIMEOUT;
	do 
	{
			SPI2->DR = *p++;
			timeOut = SPI_TIMEOUT;
			while((!(SPI2->SR & SPI_SR_RXNE)) && (timeOut--));
			rc = SPI2->DR;
			SPI2->DR = *p++;
			timeOut = SPI_TIMEOUT;
			while((!(SPI2->SR & SPI_SR_RXNE)) && (timeOut--));
			rc = SPI2->DR;
	} 
	while(--c);
}

void halSpiReadMutilByte(unsigned char* buf,uint32_t len)
{
	uint32_t c = len / 2;
	unsigned char *p = buf;
	uint32_t timeOut = SPI_TIMEOUT;
	do 
	{
			SPI2->DR = 0xff;
			timeOut = SPI_TIMEOUT;
			while((!(SPI2->SR & SPI_SR_RXNE)) && (timeOut--));
			*p++ = SPI2->DR;
			SPI2->DR = 0xff;
			timeOut = SPI_TIMEOUT;
			while((!(SPI2->SR & SPI_SR_RXNE)) && (timeOut--));
			*p++ = SPI2->DR;
	} 
	while(--c);
}





