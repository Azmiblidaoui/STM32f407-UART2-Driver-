#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000
#define USART2_BASE     0x40004400

#define RCC_AHB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x40))

#define GPIOA_MODER     (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL      (*(volatile unsigned int *)(GPIOA_BASE + 0x20))

#define USART2_SR       (*(volatile unsigned int *)(USART2_BASE + 0x00))
#define USART2_DR       (*(volatile unsigned int *)(USART2_BASE + 0x04))
#define USART2_BRR      (*(volatile unsigned int *)(USART2_BASE + 0x08))
#define USART2_CR1      (*(volatile unsigned int *)(USART2_BASE + 0x0C))

void UART2_Init(void);
void UART2_SendChar(char c);
void UART2_SendString(char *str);

int main(void) {
    UART2_Init(); 
    
    while (1) {
        UART2_SendString("Hello, UART!\r\n");
        for (volatile int i = 0; i < 500000; i++); 
    }
}

void UART2_Init(void) {
    RCC_AHB1ENR |= (1 << 0);   
    RCC_APB1ENR |= (1 << 17);  
    GPIOA_MODER &= ~(0xF << (2 * 2));  
    GPIOA_MODER |= (0xA << (2 * 2));  

    GPIOA_AFRL |= (7 << (2 * 4));  
    GPIOA_AFRL |= (7 << (3 * 4));  

    USART2_BRR = 0x0683; 
    USART2_CR1 = (1 << 13) | (1 << 3); 
}

void UART2_SendChar(char c) {
    while (!(USART2_SR & (1 << 7))); 
    USART2_DR = c; 
}

void UART2_SendString(char *str) {
    while (*str) {
        UART2_SendChar(*str++); 
    }
}

