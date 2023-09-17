#ifndef stm8_h_
#define stm8_h_



#define GPIOC_ODR   *(unsigned char*)0x500A
#define GPIOC_IDR   *(unsigned char*)0x500B
#define GPIOC_DDR   *(unsigned char*)0x500C
#define GPIOC_CR1   *(unsigned char*)0x500D
#define GPIOC_CR2   *(unsigned char*)0x500E

#define GPIOD_ODR   *(unsigned char*)0x500F
#define GPIOD_DDR   *(unsigned char*)0x5011
#define GPIOD_CR1   *(unsigned char*)0x5012
#define GPIOD_CR2   *(unsigned char*)0x5013

#define GPIOB_ODR   *(unsigned char*)0x5005
#define GPIOB_DDR   *(unsigned char*)0x5007
#define GPIOB_CR1   *(unsigned char*)0x5008
#define GPIOB_CR2   *(unsigned char*)0x5009

#define SPI_CR1 *(unsigned char*)0x5200
#define SPI_DR  *(unsigned char*)0x5204
#define SPI_SR  *(unsigned char*)0x5203

static void delay(unsigned long t)
{
    while(t--);
}

#endif /* stm8_h_ */
