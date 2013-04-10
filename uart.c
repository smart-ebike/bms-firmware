/*
 * Smart BMS
 *
 * Copyright (C) Jorge Pinto aka Casainho, 2013.
 *
 *   casainho [at] gmail [dot] com
 *     www.casainho.net
 *
 * Released under the GPL License, Version 3
 */

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void uart_init (void)
{
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &USART_InitStructure);

  USART_Cmd(USART3, ENABLE);
}

void uart_send_char (unsigned char c)
{
  /* Send one byte from USARTy to USARTz */
  USART_SendData (USART3, c);

  /* Loop until USARTy DR register is empty */
  while (USART_GetFlagStatus (USART3, USART_FLAG_TXE) == RESET) ;
}

void uart_send_str (unsigned char *data)
{
  unsigned char i = 0, r;

  while ((r = data[i++]))
    uart_send_char (r);
}

void uart_send_buf (unsigned char *buf, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
  {
    /* Send one byte from USARTy to USARTz */
    USART_SendData (USART3, buf[i]);

    /* Loop until USARTy DR register is empty */
    while (USART_GetFlagStatus (USART3, USART_FLAG_TXE) == RESET) ;
  }
}
