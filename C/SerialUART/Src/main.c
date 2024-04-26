/* Equipo 1
- Humberto Barrera
- Catalina Muñoz
- Mauricio Zavala
- Erick Campos

main.c */


// Include header files
#include "main.h"
#include "uart.h"

void USER_RCC_ClockEnable(void); 	// Enable the board's clock
void USER_GPIO_Init(void);	   		// Initialize the GPIOs' config
volatile uint8_t dataReceived; 		// Variable that stores the received input


void USER_RCC_ClockEnable( void ) {
	RCC->APB2ENR |= ( 0x1UL << 2U ) 	// IO port A clock enable
				 | ( 0x1UL << 14U ); 	// USART 1 clock enable
}

void USER_GPIO_Init( void ) {

	// Configure built-in LED as output
	// GPIOA_BSRR modified to reset pin 5 (LD2 is connected to PA5)
	GPIOA->BSRR = ( 0x1UL << 21U );
	// GPIOA_CRL modified to configure pin 5 as output
	GPIOA->CRL &= ~( 0x3UL << 22U ) // Clear CNF5[1:0] bits
				& ~( 0x2UL << 20U ); // Clear MODE5_1 bit
	// GPIOA_CRL modified to select pin 5 max speed of 10MHz
	GPIOA->CRL |= ( 0x1UL << 20U ); // To set MODE5_0 bit

	// Configure Pin PA9 (TX) as output push-pull, max speed 10MHz
	GPIOA->CRH &= ~( 0x1UL << 6U )
			    & ~( 0x2UL << 4U );
	GPIOA->CRH |= ( 0x2UL << 6U )
				| ( 0x1UL << 4U );

	// Configure Pin PA10 (RX) as input pull-up
	GPIOA->CRL &= ~( 0x1UL << 10U )
				& ~( 0x3UL << 8U );
	GPIOA->CRL |= ( 0x2UL << 10U );
	GPIOA->ODR |= ( 0x1UL << 10U );
}


// main function
int main(void) {
	// Initialize clock, GPIOs and USART protocol
	USER_RCC_ClockEnable();
	USER_GPIO_Init();
	USER_USART1_Init();
	for(;;) {
		printf("Presiona la tecla 't' para encender el LED...\n\r"); 	// Print message in the console
		dataReceived = USER_USART1_Receive(); 							// Receive input and store it
		// Check if the received data is equal to 't'
		if( dataReceived == 't' ) {
			// Alternate LED's state
			GPIOA->ODR ^= ( 0x1UL << 5U );
		}
	}
}




