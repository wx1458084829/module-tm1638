#include "stm32f10x.h"
#include "bsp_tm1638.h"
//共阴数码管显示代码
extern uint8_t  tab[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                           0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

int main(void)
{
    uint8_t i;
    Bsp_Key_Init();
   
    Write_COM(0x88); // 设置数据命令：写数据，固定地址，普通模式
    Write_COM(0x44); //设置数码管开，设置亮度为最低
    for (i = 0; i < 8; i++)
        Write_DATA(i << 1, tab[0]); //初始化寄存器

    Write_DATA(2, tab[9]); //第二个数码管显示9
    return 0;
}
