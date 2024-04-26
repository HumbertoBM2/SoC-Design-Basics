/* Equipo 1
- Humberto Barrera
- Catalina Muñoz
- Mauricio Zavala
- Erick Campos

main.c */

// Headers and libraries
#include "main.h"
#include <stdint.h>

// Enable clk
void USER_RCC_ClockEnable( void ){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // clk for GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // clk for GPIOC
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // clk for USART1
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // clk for TIM2 timer
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // clk for TIM3 timer
}

// Initialize GPIOs
void USER_GPIO_Init( void ){
	// User LED
	GPIOA->BSRR = ( 0x1UL << 21U ); // Reset PA5 (user LED)
	GPIOA->CRL &= ~( 0x3UL << 22U )
			   & ~( 0x2UL << 20U ); // Configure PA5 as output
	GPIOA->CRL |= ( 0x1UL << 20U ); // PA5 Max speed = 10MHz
	// User button
	GPIOC->CRH &= ~( 0x1UL << 22U ) // Set PC13 as input pull-up
			   & ~( 0x3UL << 20U );
	GPIOC->CRH |= ( 0x2UL << 22U );
	GPIOC->ODR |= ( 0x1UL << 13U );
	// USART1_TX
	GPIOA->CRH &= ~( 0x1UL << 6U ) // Set PA9 as output push-pull
			   & ~( 0x2UL << 4U ); // Max speed = 10 MHz
	GPIOA->CRH |= ( 0x2UL << 6U )
			   |  ( 0x1UL << 4U );
}

// Initialize TIM2 timer (2s)
void USER_TIM2_Init( void ) {
	TIM2->SMCR &= ~(TIM_SMCR_SMS); // Enable clk
	TIM2->CR1 &= ~(TIM_CR1_UDIS); // Enable UEV
	TIM2->CR1 &= ~(TIM_CR1_DIR); // Configure as upcounter
	TIM2->CR1 &= ~(TIM_CR1_CMS); // Edge-aligned mode
	TIM2->SR &= ~(TIM_SR_UIF); // Clear UIF
	TIM2->CNT = TIM_2S_CNT; // Initial count config
	TIM2->PSC = TIM_2S_PSC; // Prescaler config
	TIM2->DIER |= TIM_DIER_UIE; // Enable Update Interrupt
	NVIC->ISER[0] |= NVIC_ISER_28; // Enable interrupt in NVIC
	TIM2->CR1 |= TIM_CR1_CEN; // Enable TIM2 timer
}

// Initialize TIM3 timer (10ms)
void USER_TIM3_Init( void ) {
	TIM3->SMCR &= ~(TIM_SMCR_SMS); // Enable clk
	TIM3->CR1 &= ~(TIM_CR1_UDIS); // Enable UEV
	TIM3->CR1 &= ~(TIM_CR1_DIR); // Configure as upcounter
	TIM3->CR1 &= ~(TIM_CR1_CMS); // Edge-aligned mode
	TIM3->SR &= ~(TIM_SR_UIF); // Clear UIF
	TIM3->CNT = TIM_10MS_CNT; // Initial count config
	TIM3->PSC = TIM_10MS_PSC; // Prescaler config
}

// Interrupt routine for TIM2 timer
void TIM2_IRQHandler( void ) {
	if( TIM2->SR & TIM_SR_UIF ) { // Wait for UIF
		TIM2->CR1 &= ~(TIM_CR1_CEN); // Stop TIM2 timer
		GPIOA->ODR ^= ( 0x1UL << 5U ); // Toggle user LED (PA5)
		TIM2->SR &= ~(TIM_SR_UIF); // Clear UIF
		TIM2->CNT = TIM_2S_CNT; // Reset initial count
		TIM2->CR1 |= TIM_CR1_CEN; // Enable TIM2 timer again
	}
}

//Config function for the 10ms delay
void USER_TIM3_Delay( void ) {
	TIM3->CR1 |= TIM_CR1_CEN; // Enable TIM3 timer
	while(!( TIM3->SR & TIM_SR_UIF )); // Wait for UIF
	TIM3->CR1 &= ~(TIM_CR1_CEN); // Stop TIM3 timer
	TIM3->SR &= ~(TIM_SR_UIF); // Clear UIF
	TIM3->CNT = TIM_10MS_CNT; // Reset initial count
}


// USART initialization
void USER_USART1_Init( void ) {
	USART1->CR1 |= USART_CR1_UE; // Enable USART
	USART1->CR1 &= ~USART_CR1_M; // 8 bit data width
	USART1->CR2 &= ~USART_CR2_STOP; // Configure 1 stop bit
	USART1->BRR = USARTDIV; // 115200 baud rate
	USART1->CR1 |= USART_CR1_TE; // Enable transmitter
}

// Function to send output via USART1
int _write(int file, char *ptr, int len) {
	int DataIdx;
	for( DataIdx = 0 ; DataIdx < len; DataIdx++ ) {
		while(!( USART1->SR & USART_SR_TXE ));
		USART1->DR = *ptr++;
	}
	return len;
}


// Main function
int main( void ){
	// Initialize clock, GPIOs, Timers and USART
	USER_RCC_ClockEnable( );
	USER_GPIO_Init( );
	USER_USART1_Init();
	USER_TIM2_Init( );
	USER_TIM3_Init( );
	// For loop
	for(;;){
		if( !B1_USER ){ // Check if the button is pressed
			USER_TIM3_Delay(); // 10ms delay for debouncing
			if( !B1_USER ){ // Double check for the button
				printf("Test message\r\n"); // Print the message in the serial monitor
				while( !B1_USER ); // Wait until the button is no longer pressed
				USER_TIM3_Delay(); // 10ms delay for debouncing
			}
		}
	}
}
