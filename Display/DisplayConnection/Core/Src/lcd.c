#include "lcd.h"

void delay(void)//небольшая задержка
{
 uint16_t i;
 for(i=0;i<1000;i++)
{
	
}
}
	
void LCD_WriteData(uint8_t dt) //функция записи данных в память дисплея
{
 if(((dt >> 3)&0x01)==1) {d7_set();} 
else {d7_reset();}
 if(((dt >> 2)&0x01)==1) {d6_set();} 
else {d6_reset();}
 if(((dt >> 1)&0x01)==1) {d5_set();} 
else {d5_reset();}
 if((dt&0x01)==1) {d4_set();} 
else {d4_reset();}
}

void LCD_Command(uint8_t dt) //функия для команд
{
 rs0;
 LCD_WriteData(dt>>4);
 e1;
 delay();
 e0;
 LCD_WriteData(dt);
 e1;
 delay();
 e0;
}

void LCD_Data(uint8_t dt)
{
 rs1;
 LCD_WriteData(dt>>4);
 e1;
 delay();
 e0;
 LCD_WriteData(dt);
 e1;
 delay();
 e0;
}

void LCD_SendChar(char ch) //вывод символа на дисплей
{
   LCD_Data((uint8_t) ch);
   delay();
}

void LCD_String(char* st)//вывод СТРОКИ на дисплей
{
  uint8_t i=0;
  while(st[i]!=0)
  {
  LCD_Data(st[i]);
  delay();
  i++;
  }
}
void LCD_SetPos(uint8_t x, uint8_t y) //функция позиционирования по столбцу и строке
{
 switch(y)
{
 case 0:
 LCD_Command(x|0x80);
 HAL_Delay(1);
 break;
 case 1:
 LCD_Command((0x40+x)|0x80);
 HAL_Delay(1);
 break;
 case 2:
 LCD_Command((0x14+x)|0x80);
 HAL_Delay(1);
 break;
 case 3:
 LCD_Command((0x54+x)|0x80);
   HAL_Delay(1);
   break;
}
}


void LCD_Clear(void) //очистка дисплея
{
 LCD_Command(0x01);
 HAL_Delay(2);
}

void LCD_ini(void) //функцию инициализации дисплея
{
	HAL_Delay(40); //задержка
 rs0;
 LCD_WriteData(3);
 e1;
 delay();
 e0;
 HAL_Delay(1);
 LCD_WriteData(3);
 e1;
 delay();
 e0;
 HAL_Delay(1);
 LCD_WriteData(3);
 e1;
 delay();
 e0;
 HAL_Delay(1);
  LCD_Command(0x28);//режим 4 бит, 2 линии (для нашего большого дисплея это 4 линии), шрифт 5х8
  HAL_Delay(1);
  LCD_Command(0x28);//еще раз для верности
  HAL_Delay(1);
  LCD_Command(0x0F);//дисплей включаем (D=1), также включаем пока все курсоры, чтобы убрать курсор = LCD_Command(0x0C);
  HAL_Delay(1);
  LCD_Command(0x01);//уберем мусор
  HAL_Delay(2);
  LCD_Command(0x06);//пишем влево
  HAL_Delay(1);
  LCD_Command(0x02);//возврат курсора в нулевое положение
  HAL_Delay(2);
}
