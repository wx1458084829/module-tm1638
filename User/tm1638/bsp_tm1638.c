#include "bsp_tm1638.h"

//微秒级的延时
void delay_us(uint32_t delay_us)
{    
  volatile unsigned int num;
  volatile unsigned int t;
 
  
  for (num = 0; num < delay_us; num++)
  {
    t = 11;
    while (t != 0)
    {
      t--;
    }
  }
}

//毫秒级的延时
void delay_ms(uint16_t delay_ms)
{    
  volatile unsigned int num;
  for (num = 0; num < delay_ms; num++)
  {
    delay_us(1000);
    }
}


void Bsp_Key_Init(void)
{
    RCC_APB2PeriphClockCmd(BSP_TM1638_RCC_CLK, ENABLE);
}

// 设置输出模式
void Bsp_Key_Write_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitTypeStruct;
    GPIO_InitTypeStruct.GPIO_Pin =  BSP_TM1638_STB | BSP_TM1638_CLK |BSP_TM1638_DIO;

    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(BSP_TM1638_PORT,&GPIO_InitTypeStruct);
}

// 设置输入模式
void Bsp_Key_Read_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitTypeStruct;
    GPIO_InitTypeStruct.GPIO_Pin = BSP_TM1638_DIO | BSP_TM1638_STB | BSP_TM1638_CLK;
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(BSP_TM1638_PORT,&GPIO_InitTypeStruct);
}


void write_data(uint8_t data)
{
    uint8_t i;
    // 设置CLK为高电平
    GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_CLK);
    // 设置STB为高电平
    GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
    // 设置STB为低电平
    GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_STB);

    // 准备写入数据完成
    for (i = 0; i < 8; i++)
    {
        // 设置CLK为低电平
        GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_CLK);
        if (((data) & (1 << i)) == 0)
        {
            // 设置低电平
            GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_DIO);
        }
        else
        {
            GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_DIO);
        }
        // 设置CLK为高电平
        GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_CLK);
    }
    // 设置STB为低电平
    GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
    // 设置STB为高电平
    GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
    delay_ms(1);
}

void Write_COM(uint8_t cmd)
{
     // 设置STB为低电平
    GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
    write_data(cmd);
    // 设置STB为高电平
    GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
}

