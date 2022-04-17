#include <stm8s.h>
#include <stm8s_conf.h>
#include "main.h"
#include "mb.h"
#include "mb-link.h"

void delay(uint32_t);

void Tim2OVFI()
{
  GPIO_WriteReverse(LED_GPIO_PORT,LED_GPIO_PIN);
  TIM2_ClearFlag(TIM2_FLAG_UPDATE);
}

void Uart1RXNEI()
{
  uint8_t B;
  B=UART1_ReceiveData8();
}

void Uart1_Putchar(uint8_t Ch)
{
  UART1_SendData8(Ch);
  while(!UART1_GetFlagStatus(UART1_FLAG_TXE));
}

void Uart1_SendNByte(uint8_t* Data,uint8_t Len)
{
  while(Len--)Uart1_Putchar(*Data++);
}

void main(void)
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  GPIO_Init(LED_GPIO_PORT,LED_GPIO_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);

  TIM2_TimeBaseInit(TIM2_PRESCALER_128,0xffff);
  TIM2_ITConfig(TIM1_IT_UPDATE,ENABLE);
  TIM2_Cmd(ENABLE);

  UART1_Init(9600,UART1_WORDLENGTH_8D,UART1_STOPBITS_1,UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,UART1_MODE_TXRX_ENABLE);
  UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);

  enableInterrupts();

  while(1)
  {
    Uart1_SendNByte((uint8_t*)"Hello!\r\n",8);
    mb_link_check_new_data('A');
    delay(1000);
  }
}

void delay(uint32_t time)
{
  int i;
  while (time--)
  {
    for(i=0;i<0xfff;i++)nop();
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)
  {
  }
}
#endif

