#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include <string.h>

#define UART_RX_BUFFER_SIZE 32U

void UART_Init(void);
void UART_SendChar(char character);
void UART_SendString(const char *text);
void LED_Init(void);
void UART_ProcessReceivedChar(char receivedChar);

int main(void)
{
    SystemCoreClockUpdate();
    LED_Init();
    UART_Init();

    while (1) {
        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
            UART_ProcessReceivedChar((char)USART_ReceiveData(USART1));
        }
    }
}

void UART_Init(void)
{
    GPIO_InitTypeDef gpioConfig;
    USART_InitTypeDef uartConfig;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    /* USART1: TX = PA9, RX = PA10. */
    gpioConfig.GPIO_Pin = GPIO_Pin_9;
    gpioConfig.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioConfig.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpioConfig);

    gpioConfig.GPIO_Pin = GPIO_Pin_10;
    gpioConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioConfig);

    /* 9600 baud, 8 data bits, no parity, 1 stop bit. */
    uartConfig.USART_BaudRate = 9600;
    uartConfig.USART_WordLength = USART_WordLength_8b;
    uartConfig.USART_StopBits = USART_StopBits_1;
    uartConfig.USART_Parity = USART_Parity_No;
    uartConfig.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    uartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &uartConfig);
    USART_Cmd(USART1, ENABLE);
}

void UART_SendChar(char character)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {
    }
    USART_SendData(USART1, (uint8_t)character);
}

void UART_SendString(const char *text)
{
    while (*text != '\0') {
        UART_SendChar(*text);
        text++;
    }
}

void LED_Init(void)
{
    GPIO_InitTypeDef gpioConfig;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    gpioConfig.GPIO_Mode = GPIO_Mode_Out_PP;
		gpioConfig.GPIO_Pin = GPIO_Pin_5  | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
		gpioConfig.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &gpioConfig);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
}

void UART_ProcessReceivedChar(char receivedChar)
{
    static char receivedText[UART_RX_BUFFER_SIZE];
    static uint16_t receivedLength = 0U;
    static uint8_t bufferOverflow = 0U;

    if (receivedChar == '\r' || receivedChar == '\n') {
        if (receivedLength > 0) {
            receivedText[receivedLength] = '\0'; 
            
            if (strcmp(receivedText, "LED1ON") == 0) {
                GPIO_SetBits(GPIOA, GPIO_Pin_1);
                UART_SendString("LED1: ON\r\n");
            } else if (strcmp(receivedText, "LED1OFF") == 0) {
                GPIO_ResetBits(GPIOA, GPIO_Pin_1);
                UART_SendString("LED1: OFF\r\n");
            } else if (strcmp(receivedText, "LED2ON") == 0) {
                GPIO_SetBits(GPIOA, GPIO_Pin_2);
                UART_SendString("LED2: ON\r\n");
            } else if (strcmp(receivedText, "LED2OFF") == 0) {
                GPIO_ResetBits(GPIOA, GPIO_Pin_2);
                UART_SendString("LED2: OFF\r\n");
            } else if (strcmp(receivedText, "LED3ON") == 0) {
                GPIO_SetBits(GPIOA, GPIO_Pin_3);
                UART_SendString("LED3: ON\r\n");
            } else if (strcmp(receivedText, "LED3OFF") == 0) {
                GPIO_ResetBits(GPIOA, GPIO_Pin_3);
                UART_SendString("LED3: OFF\r\n");
            } else if (strcmp(receivedText, "LED4ON") == 0) {
                GPIO_SetBits(GPIOA, GPIO_Pin_4);
                UART_SendString("LED4: ON\r\n");
            } else if (strcmp(receivedText, "LED4OFF") == 0) {
                GPIO_ResetBits(GPIOA, GPIO_Pin_4);
                UART_SendString("LED4: OFF\r\n");
            } else if (strcmp(receivedText, "LED5ON") == 0) {
                GPIO_SetBits(GPIOA, GPIO_Pin_5);
                UART_SendString("LED5: ON\r\n");
            } else if (strcmp(receivedText, "LED5OFF") == 0) {
                GPIO_ResetBits(GPIOA, GPIO_Pin_5);
                UART_SendString("LED5: OFF\r\n");
            } else if (strcmp(receivedText, "LEDONALL") == 0) {
                GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
                UART_SendString("LED ALL: ON\r\n");
            } else if (strcmp(receivedText, "LEDOFFALL") == 0) {
                GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
                UART_SendString("LED ALL: OFF\r\n");
            } else {
                UART_SendString("ERROR\r\n");
            }
            
            receivedLength = 0U;
            bufferOverflow = 0U;
        }
        return;
    }

    if (bufferOverflow != 0U) {
        return;
    }

    if (receivedLength >= UART_RX_BUFFER_SIZE - 1U) {
        receivedLength = 0U;
        bufferOverflow = 1U;
        UART_SendString("lenh qua dai\r\n");
        return;
    }

    receivedText[receivedLength++] = receivedChar;
}
