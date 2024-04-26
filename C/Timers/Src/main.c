/* Equipo 1
- Humberto Barrera
- Catalina Muñoz
- Mauricio Zavala
- Erick Campos

main.c */

// Headers and libraries
#include "main.h"

// Enable necessary clock for user-defined functionalities
void USER_RCC_ClockEnable( void ){
	RCC->APB2ENR |= ( 0x1UL << 2U ); // Enable IO port A clock
	RCC->APB1ENR |= ( 0x1UL << 0U ); // Enable clock for TIM2
}

// Initialize GPIO pins
void USER_GPIO_Init( void ){
	GPIOA->BSRR =   ( 0x1UL << 21U ); // Reset pin 5 of port A (LD2)
	GPIOA->CRL 	&= ~( 0x3UL << 22U )  // Configure pin 5 as output
				&  ~( 0x2UL << 20U );
	GPIOA->CRL 	|=  ( 0x1UL << 20U ); // Select pin 5 max speed of 10MHz
}

// Initialize TIM2 for user-defined timing operations
void USER_TIM2_Init( void ) {
	TIM2->SMCR 	&= ~(TIM_SMCR_SMS); // Enable internal clock source
	TIM2->CR1 	&= ~(TIM_CR1_UDIS); // Enable UEV
	TIM2->CR1 	&= ~(TIM_CR1_DIR);  // Counter as upcounter
	TIM2->CR1 	&= ~(TIM_CR1_CMS);  // Edge-aligned mode
	TIM2->SR 	&= ~(TIM_SR_UIF);   // Clear Update Interrupt Flag
	TIM2->CNT 	= TIM_CNT;          // Configure initial count
	TIM2->PSC 	= TIM_PSC;          // Configure prescaler
}

// Implement a 1s delay using TIM2
void USER_TIM2_Delay( void ) {
	TIM2->CR1 	|= TIM_CR1_CEN;       	// Enable TIM2 timer
	while(!( TIM2->SR & TIM_SR_UIF ));  // Wait for UIF
	TIM2->CR1 	&= ~(TIM_CR1_CEN);		// Stop TIM2 timer
	TIM2->SR 	&= ~(TIM_SR_UIF);		// Clear UIF
	TIM2->CNT 	= TIM_CNT;				// Re-charge initial count
}

// Main function
int main( void ){
	// Initialize the created functions for the clock, timer, and GPIOs
	USER_RCC_ClockEnable( );
	USER_GPIO_Init( );
	USER_TIM2_Init( );
	// Infinite loop
	for(;;) {
		GPIOA->ODR ^= 0x1UL << 5U; 	// Inverts the state of the user LED
		USER_TIM2_Delay(); 			// Implement a 1s delay using the timer
	}
}

