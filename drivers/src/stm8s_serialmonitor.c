#include "stm8s.h"
#include "stm8s_serialmonitor.h"

void Serial_Begin(uint32_t BaudRate)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, ENABLE);
    UART1_Init(BaudRate, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    UART1_Cmd(ENABLE);
    delay.ms(50);
}

int putchar(int c)
{
    UART1->DR = c;

    while (!UART1_GetFlagStatus(UART1_FLAG_TC))
        ;

    delay.ms(1);

    return c;
}

const Serial_Module Serial = {
    .begin = Serial_Begin,
};