#include "stm8s.h"
#include "stm8s_conf.h"
#include "main.h"
#include "mb.h"

void TimOutTimer_OVF()
{
  mb_rx_timeout_handler();
  TIM2_ClearFlag(TIM2_FLAG_UPDATE);
  TIM2_Cmd(DISABLE);
}

void TimeOutTimer_Reset()
{
  TIM2_SetCounter(0);
  TIM2_Cmd(ENABLE);
  TIM2_ClearFlag(TIM2_FLAG_UPDATE);
  TIM2_ClearITPendingBit(TIM2_IT_UPDATE);
}

void Uart1_RXIntrrupt()
{
  mb_rx_new_data(UART1_ReceiveData8());
  TimeOutTimer_Reset();
}

void Uart1_Putchar(uint8_t Ch)
{
  UART1_SendData8(Ch);
  while(!UART1_GetFlagStatus(UART1_FLAG_TXE));
}

void Uart1_SendNByte(uint8_t* Data,uint8_t Len)
{
  GPIO_WriteReverse(LED_GPIO_PORT,LED_GPIO_PIN);
  while(Len--)Uart1_Putchar(*Data++);
}

void main(void)
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  GPIO_Init(LED_GPIO_PORT,LED_GPIO_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);

  TIM2_TimeBaseInit(TIM2_PRESCALER_128,0xffff);
  TIM2_ITConfig(TIM1_IT_UPDATE,ENABLE);

  UART1_Init(9600,UART1_WORDLENGTH_8D,UART1_STOPBITS_1,UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,UART1_MODE_TXRX_ENABLE);
  UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);

  mb_set_tx_handler(&Uart1_SendNByte);

  enableInterrupts();

  while(1)
  {
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

