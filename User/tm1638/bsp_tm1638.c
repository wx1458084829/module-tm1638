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



/**
* @brief  设置为输出模式
* @param  void
* @retval void
*/
void Bsp_Key_Write_Mode(void)
{
  GPIO_InitTypeDef GPIO_InitTypeStruct;
  GPIO_InitTypeStruct.GPIO_Pin = BSP_TM1638_STB | BSP_TM1638_CLK | BSP_TM1638_DIO;
  GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(BSP_TM1638_PORT, &GPIO_InitTypeStruct);
}

/**
* @brief  设置为输出模式
* @param  void
* @retval void
*/
void Bsp_Key_Read_Mode(void)
{
  GPIO_InitTypeDef GPIO_InitTypeStruct;
  GPIO_InitTypeStruct.GPIO_Pin = BSP_TM1638_DIO | BSP_TM1638_STB | BSP_TM1638_CLK;
  GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(BSP_TM1638_PORT, &GPIO_InitTypeStruct);
}

/**
* @brief 写数据
* @param  data：写的数据
* @retval 无
*/
void TM1638_Write(uint8_t data)
{
  // 设置写模式
  Bsp_Key_Write_Mode();
  uint8_t i;
  // 准备写入数据完成
  for (i = 0; i < 8; i++)
  {
    // 设置CLK为低电平
    GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_CLK);
    if (data & 0x01)
    {
      // 设置高电平
      GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_DIO);
    }
    else
    { // 设置低电平
      GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_DIO);
    }
    data >>= 1;
    // 设置CLK为高电平
    GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_CLK);
  }
}

/**
* @brief 写命令
* @param  cmd：命令
* @retval 无
*/
void Write_COM(uint8_t cmd)
{
  // 设置STB为低电平
  GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
  TM1638_Write(cmd);
  // 设置STB为高电平
  GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
}

/**
* @brief 在指定地址写数据
* @param  add: 地址
* @param  data: 数据
* @retval 无
*/
void Write_DATA(uint8_t add, uint8_t data)
{
  Write_COM(0x44);
  // 设置STB为低电平
  GPIO_ResetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
  TM1638_Write(0xc0 | add);
  TM1638_Write(data);
  // 设置STB为高电平
  GPIO_SetBits(BSP_TM1638_PORT, BSP_TM1638_STB);
}
/**
* @brief  初始化函数
*/
void Bsp_Key_Init(void)
{
  RCC_APB2PeriphClockCmd(BSP_TM1638_RCC_CLK, ENABLE);
  // 设置写模式
  Bsp_Key_Write_Mode();
}
