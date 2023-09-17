#include "hardware/stm8.h"

// #define CLK 6
// #define DIO 13

#define SCL_TM1637 3
#define SDA_TM1637 4

int pack;

char command1 = 0b01000000; //Команда записи данных в регистр дисплея
char command2 = 0b11000000; //Команда "начальный адрес дисплея"

char symbol_1 = 0x76;//Символ_1
char symbol_2 = 0x79;//Символ_2
char symbol_3 = 0x38;//Символ_3
char symbol_4 = 0x73;//Символ_4

char command3 = 0b10001111; //Яркость и ON/OFF дисплея

void TM1637_init();
void TM1637_start();
void TM1637_stop();
void TM1637_writeByte(char pack);
void TM1637_send();

void setup()
{
TM1637_init();
  while (1)
  {
    TM1637_send();
  }
}

void initTM1637()
{
  GPIOC_DDR |= (1 << SCL_TM1637) | (1 << SDA_TM1637);
  GPIOC_CR1 |= (1 << SCL_TM1637) | (1 << SDA_TM1637);
  GPIOC_CR2 |= (1 << SCL_TM1637) | (1 << SDA_TM1637);
}

void TM1637_start(){
   GPIOC_ODR |= 1<<SCL_TM1637;
   GPIOC_ODR |= 1<<SDA_TM1637;
delay(200);
  GPIOC_ODR &= ~(1<<SDA_TM1637);
}

void TM1637_stop(){
  GPIOC_ODR &= ~(1<<SCL_TM1637);
delay(200);
  GPIOC_ODR &= ~(1<<SDA_TM1637);
delay(200);
  GPIOC_ODR |= 1<<SCL_TM1637;;
delay(200);
  GPIOC_ODR |= 1<<SDA_TM1637;
}


void TM1637_writeByte(char pack){

  char i;
    for(i=0;i<8;i++)  
  {
   GPIOC_ODR &= ~(1<<SCL_TM1637);
    if(pack & 0x01)
  { GPIOC_ODR |= 1<<SDA_TM1637;}
    else {GPIOC_ODR &= ~(1<<SDA_TM1637);}
  delay(3);
    pack = pack >> 1;
    GPIOC_ODR |= 1<<SCL_TM1637;
  delay(3);
  }
  GPIOC_ODR &= ~(1<<SCL_TM1637);
  delay(5);
  GPIOC_DDR &= ~(1<<SDA_TM1637);
  while((GPIOC_IDR & (1<<SDA_TM1637)));
  GPIOC_DDR |= (1<<SDA_TM1637);
  GPIOC_ODR |= 1<<SCL_TM1637;
  delay(2);
  GPIOC_ODR &= ~(1<<SCL_TM1637);
}

void TM1637_init()
{
   GPIOC_ODR |= (1<<SCL_TM1637) | (1<<SDA_TM1637);
}

void TM1637_send(){
TM1637_init();                   //Инициализируем пины SCL и SDA как выходы
TM1637_start();
pack = command1;                    //Команда записи в регистр дисплея
TM1637_writeByte(pack);
TM1637_stop();
TM1637_start();
pack = command2;                   //Команда начального адреса для автоинкремента адреса
TM1637_writeByte(pack);
pack = symbol_1;                   //Символ 1
TM1637_writeByte(pack);
pack = symbol_2;                   //Символ 2
TM1637_writeByte(pack);
pack = symbol_3;                  //Символ 3
TM1637_writeByte(pack);
pack = symbol_4;                   //Символ 4
TM1637_writeByte(pack);
TM1637_stop();
TM1637_start();
pack = command3;                  //Команда, задающая яркость дисплея
TM1637_writeByte(pack);
TM1637_stop();
delay(2000);
}