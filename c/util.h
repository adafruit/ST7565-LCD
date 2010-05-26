#include <avr/pgmspace.h>

// Raw constants for the UART to make the bit timing nice

#if (F_CPU == 16000000)
#define BRRL_9600 103    // for 16MHZ
#define BRRL_192 52    // for 16MHZ
#elif (F_CPU == 8000000)
#define BRRL_9600 52
#define BRRL_192 26    
#endif

// Debug printing functions - handy!
#define uart_putc(c) uart_putchar(c)

int uart_putchar(char c);
void uart_init(uint16_t BRR);
char uart_getchar(void);

void uart_putc_hex(uint8_t b);
void uart_putw_hex(uint16_t w);
void uart_putdw_hex(uint32_t dw);

void uart_putw_dec(uint16_t w);
void uart_putdw_dec(uint32_t dw);
void uart_puts(const char* str);

void RAM_putstring(char *str);
void ROM_putstring(const char *str, uint8_t nl);

// by default we stick strings in ROM to save RAM
#define putstring(x) ROM_putstring(PSTR(x), 0)
#define putstring_nl(x) ROM_putstring(PSTR(x), 1)
#define nop asm volatile ("nop\n\t")

// some timing functions

void delay_ms(unsigned char ms);
void delay_10us(uint8_t us);
void delay_s(uint8_t s);

