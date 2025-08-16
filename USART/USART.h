#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include<avr/io.h>

    /*
     * =================
     *   CONFIGURATION 
     * =================
     */
    #define FOSC 16000000UL  // ATmega Clock Speed

    #define PURPOSE 2        
    // USART PURPOSE:
    // 0 - transmitter, 1 - reciver, 2 - ransmitter and reciver, other - ransmitter and reciver
    
    #define BAUD 9600        // Typical values: 1200, 2400, 4800, 9600, ...
    /*
     * =====================
     *   CONFIGURATION END
     * =====================
     */
    
    #define MYUBRR FOSC/16/BAUD-1

    void USART_init(void);
    void USART_transmit(unsigned char data);
    void USART_transmit_str(const char *str);
    unsigned char USART_recive(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */
