/* Equipo 1
- Humberto Barrera
- Catalina Muñoz
- Mauricio Zavala
- Erick Campos

uart.c */


#include "main.h"
#include "uart.h"


static void USER_USART1_Send_8bit( uint8_t Data );


void USER_USART1_Init( void ) {
	USART1->CR1 |= USART_CR1_UE; 	// Step 1 - USART enabled
	USART1->CR1 &= ~USART_CR1_M; 	// Step 2 - 8 Data bits
	USART1->CR2 &= ~USART_CR2_STOP; // Step 3 - 1 Stop bit
	USART1->BRR  = USARTDIV; 		// Step 5 - Desired baud rate
	USART1->CR1 |= USART_CR1_TE; 	// Step 6 - Transmitter enabled
	USART1->CR1 |= USART_CR1_RE; 	// Step 7 - Receiver enabled
}

// Function to transmit data via USART1's TX
void USER_USART1_Transmit( uint8_t *pData, uint16_t size ){
	for( int i = 0; i < size; i++ ){
		USER_USART1_Send_8bit( *pData++ );
	}
}

static void USER_USART1_Send_8bit(uint8_t Data){
	while(!( USART1->SR & USART_SR_TXE ));	// Wait until next data can be written
	USART1->DR = Data;						// Step 7 Data to send
}


int _write(int file, char *ptr, int len) {
	int DataIdx;
	for( DataIdx = 0 ; DataIdx < len; DataIdx++ ) {
		while(!( USART1->SR & USART_SR_TXE )); // Wait until USART_DR is empty
		USART1->DR = *ptr++; // Transmit data
	}
	return len;
}

// Function to receive data via USART1's RX
uint8_t USER_USART1_Receive(void) {
	while(!( USART1->SR & USART_SR_RXNE )); // Wait until USART_DR is not empty
	return USART1->DR; 						// Return received data
}
