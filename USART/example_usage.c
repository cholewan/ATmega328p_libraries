#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"

/*
* ===============
*   CONNECT LED  
* ===============
*/
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED 0

volatile unsigned char toggle_led = '0';
volatile uint8_t usart_flag = 0;
volatile uint8_t s5_counter = 0;

// show hello world every 5 seconds
ISR(TIMER1_COMPA_vect) { 
    s5_counter++;
}

// handle usart recive
ISR(USART_RX_vect) {
    const char c = UDR0;
    if(c == '1' || c == '0') {
        toggle_led = c;
        usart_flag = 1;
    }
}

int main(void) {
    // init
    USART_init();
    LED_DDR |= (1<<LED);
    LED_PORT |= (1<<LED);
    
    /*
    * =======================================
    *   INTERRUPTS SET FOR YOUR CLOCK SPEED
    * =======================================
    */
    TCCR1B |= (1<<WGM12) | (1<<CS12); // CTC, prescaler 256
    TIMSK1 |= (1<<OCIE1A);          
    OCR1A |= 62500;
    sei();
     
    while (1) {
        
        // led on/off
        if(usart_flag) {
            if(toggle_led == '1') {
                LED_PORT &= ~(1<<LED);
            } else if (toggle_led == '0') {
                LED_PORT |= (1<<LED);
            }
            usart_flag = 0;
        }
        
        // transmit hello world text and state
        if(s5_counter==5) {
            USART_transmit_str("Hello World! ");
            USART_transmit(toggle_led);
            USART_transmit('\n');

            s5_counter = 0;
        }
    }
}
