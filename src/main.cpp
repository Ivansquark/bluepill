#include "main.h"

volatile uint32_t ticks_delay;

extern void delay(uint32_t ms);
static __IO uint32_t s_timer;

extern "C" void SysTick_Handler(void)
{
        ticks_delay++;
}

void delay_ms(__IO uint32_t milisec) {
    // ------- SysTick CONFIG --------------
    if (SysTick_Config(24000)) // set 1ms
    {
        while(1); // error
    }
    uint32_t start = ticks_delay;
	while((ticks_delay - start) < milisec);
    //SysTick->LOAD &= ~(SysTick_CTRL_ENABLE_Msk);    // disable SysTick
}

int main()
{
	rcc_ini();
	gpioc_ini();
	//usart1_ini();
	__enable_irq();		
	Spi2_master master;
	I2C1_master I2Cmast;	
	//uint8_t byteRead=0;
	//GPIOC->BSRR|=GPIO_BSRR_BR13;
	//GPIOC->BSRR|=GPIO_BSRR_BS13;
	//GPIOC->BSRR=GPIO_BSRR_BR13;
	master.cs_idle();
	master.cs_set();
	I2Cmast.writeBytes(0x0000,I2Cmast.arrDefault,20);
	//for(volatile int i=0;i<32;i++)
	//{
	//	I2Cmast.writeByte(0x0100+8*i,i);
	//	delay_ms(10);
	//}
	delay_ms(10);
	//I2Cmast.writeByte(0x0088,99);
	//I2Cmast.writeByte(0x0000,12);
	delay_ms(10);
	//for(volatile int i=0;i<32;i++)
	//{
	//	I2Cmast.arr[i]=I2Cmast.readByte(0x0000+i);
	//	delay_ms(10);
	//}
	I2Cmast.readBytes(0x0000,20);
	//I2Cmast.arr[0]=I2Cmast.readByte(0x004A);
	//I2Cmast.arr[1]=I2Cmast.readByte(0x0052);
	
	while(1)
	{
		//I2Cmast.writeByte(0x0000,0x07);
		for(uint8_t i=0;i<20;i++)
		{
			delay_ms(100);
			//master.sendByte(I2Cmast.readByte(0x0000));
			master.sendByte(I2Cmast.arr[i]);
			delay_ms(100);
			GPIOC->ODR^=GPIO_ODR_ODR13;
		}
		//char* str="opa\n";
		//usart1_send(c);
		//usart1_sendSTR(str);
		//delay(0xfffff);
	}
    return 0;
}
