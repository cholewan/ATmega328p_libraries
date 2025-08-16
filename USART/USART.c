#include "USART.h"

void USART_init(void) {
    // Set baud rate 
    uint16_t ubrr = MYUBRR;
    UBRR0H = (uint8_t) (ubrr >> 8);
    UBRR0L = (uint8_t) ubrr;
    
#if PURPOSE == 0                                             // Enable transmitter
    UCSR0B = (1 << TXEN0);
#elif PURPOSE == 1                                           // Enable reciver
    UCSR0B = (1 << RXEN0) | (1 << RXCIE0); 
#else
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1<< RXCIE0);     // Enable reciver and ransmitter
#endif

    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);                        // 8data, 1stop bit
}

void USART_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_transmit_str(const char *str) {
    while(*str) USART_transmit(*str++);
}

unsigned char USART_recive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}
