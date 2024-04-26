// Humberto Barrera Martínez A00836271
// main.c
/* Libraries, Definitions and Global Declarations */
#include <stdint.h>
#include "main.h"


void USER_RCC_ClockEnable(void){
	// RCC_APB2ENR modified to IO port A clock enable
	RCC->APB2ENR	=	RCC->APB2ENR	//		RCC_APB2ENR actual value
					|					//		to set
					( 0x1UL <<  2U );	//		(mask) IOPAEN bit
}


// Exercise 1: Function to configure and set (to output a high-level) only the PB0 and PB4 pins from the STM32F103
void configForPB0_PB4(void) {
	// Clearing bits to configure as output mode
	GPIOB->CRL &= ~(0x3UL << 2U)   // Clear mode bits for PB0
	    	   &  ~(0x2UL << 0U)   // Clear configuration bits for PB0
			   &  ~(0x3UL << 18U)  // Clear mode bits for PB4
			   &  ~(0x2UL << 16U); // Clear configuration bits for PB4

	// Setting PB0 and PB4 pins to high level
	GPIOB->BSRR = ((0x1UL << 0U) | (0x1UL << 4U));
}


// Exercise 2: Function to configure and clear (to output a low-level) only the PB9 and PB12 pins from the STM32F103
void configForPB9_PB12(void){
	// Clearing bits to configure as output mode
	GPIOB->CRH &= ~(0x3UL << 6U)   // Clear mode bits for PB9
			   &  ~(0x2UL << 4U)   // Clear configuration bits for PB9
			   &  ~(0x3UL << 18U)  // Clear mode bits for PB12
			   &  ~(0x2UL << 16U); // Clear configuration bits for PB12

	// Clearing PB9 and PB12 pins to low level
	GPIOB->BSRR = ((0x1UL << 25U) | (0x1UL << 28U));
}

// Exercise 3: Function to configure and enable the weak internal pull-ups only in the odd pins of Port A
void configForOdd_PA(void){
	// Config for PA1
	GPIOA->CRL &= ~(0x1UL << 6U)  // Clear mode bit for PA1
			   &  ~(0x3UL << 4U); // Clear configuration bits for PA1
	GPIOA->ODR |=  (0x1UL << 1U); // Set PA1 pull-up

	// Config for PA3
	GPIOA->CRL &= ~(0x1UL << 14U)  // Clear mode bit for PA3
			   &  ~(0x3UL << 12U); // Clear configuration bits for PA3
	GPIOA->ODR |=  (0x1UL << 3U);  // Set PA3 pull-up

	// Config for PA5
	GPIOA->CRL &= ~(0x1UL << 22U)  // Clear mode bit for PA5
			   &  ~(0x3UL << 20U); // Clear configuration bits for PA5
	GPIOA->ODR |=  (0x1UL << 5U);  // Set PA5 pull-up

	// Config for PA7
	GPIOA->CRL &= ~(0x1UL << 30U)  // Clear mode bit for PA7
			   &  ~(0x3UL << 28U); // Clear configuration bits for PA7
	GPIOA->ODR |=  (0x1UL << 7U);  // Set PA7 pull-up

	// Config for PA9
	GPIOA->CRH &= ~(0x1UL << 6U)  // Clear mode bit for PA9
			   &  ~(0x3UL << 4U); // Clear configuration bits for PA9
	GPIOA->ODR |=  (0x1UL << 9U); // Set PA9 pull-up

	// Config for PA11
	GPIOA->CRH &= ~(0x1UL << 14U)  // Clear mode bit for PA11
			   &  ~(0x3UL << 12U); // Clear configuration bits for PA11
	GPIOA->ODR |=  (0x1UL << 11U); // Set PA11 pull-up

	// Config for PA13
	GPIOA->CRL &= ~(0x1UL << 22U)  // Clear mode bit for PA13
			   &  ~(0x3UL << 20U); // Clear configuration bits for PA13
	GPIOA->ODR |=  (0x1UL << 13U); // Set PA13 pull-up

	// Config for PA15
	GPIOA->CRH &= ~(0x1UL << 30U)  // Clear mode bit for PA15
			   &  ~(0x3UL << 28U); // Clear configuration bits for PA15
	GPIOA->ODR |=  (0x1UL << 15U); // Set PA15 pull-up

}


// Exercise 4: Function to configure and read the values of PC11 and PC10 pins from the STM32F103
// The 2-bit value is be saved in bits 1 and 0 of an unsigned 16-bit variable
void configForPC11_PC10(void){
	// Clearing and setting bits to configure as input
	GPIOC->CRH &= ~((0x3UL << 10U) // Clear mode bits for PC11
	    	   &  ~(0x3UL << 14U)); // Clear mode bits for PC10
	GPIOC->CRH |=  ((0x3UL << 8U) | (0x3UL << 12U)); // Set input mode for PC11 and PC10

	// Reading values from PC11 and PC10 pins
	uint16_t values = GPIOC->IDR;
	// Extracting values from PC11 and PC10 and saving them into a 16-bit variable
	uint16_t result = 0;
	result |= ((values >> 11) & 0x1) << 1; // Saving PC11 value into bit 1
	result |= ((values >> 10) & 0x1); // Saving PC10 value into bit 0

}


// Exercise 5: function to configure and perform a sweep of ‘1s’ (from bit 0 to bit 15) in Port A of the STM32F103
void configForSweep_PA(void){
	// Configuring all pins of Port A as output mode
	GPIOA->CRL = 0x11111111;
	GPIOA->CRH = 0x11111111;
	// Clearing all pins of Port A
	GPIOA->ODR &= ~(0xFFFF);
	// Sweeping '1s' from bit 0 to bit 15 in Port A
	for (int i = 0; i < 16; ++i) {
		GPIOA->ODR |= (1UL << i);
	}
}



int main(void) {
  /* Declarations and Initializations */
  USER_RCC_ClockEnable();

  configForPB0_PB4();
  configForPB9_PB12();
  configForOdd_PA();
  configForPC11_PC10();
  configForSweep_PA();

  /* Repetitive block */
  for (;;) {
  }
}


