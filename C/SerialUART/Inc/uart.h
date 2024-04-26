/* Equipo 1
- Humberto Barrera
- Catalina Muñoz
- Mauricio Zavala
- Erick Campos

uart.h */

#ifndef UART_H_
#define UART_H_

#define USART_CR1_UE 	(0x1UL << 13U) 	// Enable USART
#define USART_CR1_M 	(0x1UL << 12U) 	// Set word lenght to 8 bits
#define USART_CR2_STOP 	(0x3UL << 12U) 	// Set the number of stop bits to 1
#define USARTDIV 		 0x45 			// Set baudrate to 115200

#define USART_CR1_TE 	(0x1UL << 3U) // Transmitter enable bit
#define USART_SR_TXE 	(0x1UL << 7U) // Transmit data register empty flag

#define USART_CR1_RE 	(0x1UL << 2U) // Receiver enable bit
#define USART_SR_RXNE 	(0x1UL << 5U) // Receive data register not empty flag

void USER_USART1_Init(void); 		  // Initialize USART1
int _write( int file, char *ptr, int len );
// Transmit and receive functions
void USER_USART1_Transmit(uint8_t *pData, uint16_t size);
uint8_t USER_USART1_Receive(void);

#endif
