/* Equipo 1
- Humberto Barrera
- Catalina Muñoz
- Mauricio Zavala
- Erick Campos

main.h */

// Headers and libraries
#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>

// Reset and Clock Control registers
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
} RCC_TypeDef;

// General Purpose I/O registers
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
} GPIO_TypeDef;

// Timer registers
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RESERVED1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t RESERVED2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
} TIM_TypeDef;

#define RCC_BASE 	0x40021000UL // RCC base address
#define GPIOA_BASE 	0x40010800UL // GPIO Port A base address
#define TIM2_BASE 	0x40000000UL // TIM2 timer base address
#define RCC 		(( RCC_TypeDef *) RCC_BASE)
#define GPIOA 		(( GPIO_TypeDef *) GPIOA_BASE)
#define TIM2 		(( TIM_TypeDef *) TIM2_BASE)

// Config for the timer
#define TIM_SMCR_SMS 	( 0x7UL << 0U ) // Slave Mode Control Register
#define TIM_CR1_UDIS 	( 0x1UL << 1U ) // Disable update
#define TIM_CR1_DIR 	( 0x1UL << 4U ) // Indicate direction (up)
#define TIM_CR1_CMS 	( 0x3UL << 5U ) // Center-aligned mode selection (mode 3)
#define TIM_SR_UIF 		( 0x1UL << 0U ) // Update interrupt flag
#define TIM_CNT 		0x1EF			// Timer Counter initial value (495)
#define TIM_PSC 		0x7A			// Timer Prescaler value (122)
#define TIM_CR1_CEN 	( 0x1UL << 0U ) // Enable the timer

// Functions
void USER_RCC_ClockEnable( void ); 	// Initilize the clock
void USER_GPIO_Init( void );		// Initialize GPIOs
void USER_TIM2_Init( void ); 		// Initialize timer
void USER_TIM2_Delay( void ); 		// Function to implement a delay using the timer

#endif /* MAIN_H_ */
