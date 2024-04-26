/* Equipo 1
- Humberto Barrera
- Catalina Muñoz
- Mauricio Zavala
- Erick Campos

main.h */

#ifndef MAIN_H_
#define MAIN_H_

// Headers and libraries
#include <stdio.h>
#include <stdint.h>

// Reset and Clock Control registers
typedef struct {
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
typedef struct {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
} GPIO_TypeDef;

// USART Registers
typedef struct {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_TypeDef;

// Timer registers
typedef struct {
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

// Interrupt Controller registers
typedef struct {
	volatile uint32_t ISER[3U];
	volatile uint32_t RESERVED0[29U];
	volatile uint32_t ICER[3U];
	volatile uint32_t RESERVED1[29U];
	volatile uint32_t ISPR[3U];
	volatile uint32_t RESERVED2[29U];
	volatile uint32_t ICPR[3U];
	volatile uint32_t RESERVED3[29U];
	volatile uint32_t IABR[3U];
	volatile uint32_t RESERVED4[61U];
	volatile uint32_t IPR[84U];
	volatile uint32_t RESERVED5[683U];
	volatile uint32_t STIR;
} NVIC_TypeDef;

// Clock, timers, GPIOs and interrupt definition
#define RCC_BASE 0x40021000UL //RCC base address
#define GPIOA_BASE 0x40010800UL //GPIO Port A base address
#define GPIOC_BASE 0x40011000UL //GPIO Port C base address
#define USART1_BASE 0x40013800UL // USART1 base address
#define TIM2_BASE 0x40000000UL // TIM2 timer base address
#define TIM3_BASE 0x40000400UL // TIM3 timer base address
#define NVIC_BASE 0xE000E100UL // NVIC base address
#define RCC (( RCC_TypeDef *) RCC_BASE)
#define GPIOA (( GPIO_TypeDef *) GPIOA_BASE)
#define GPIOC (( GPIO_TypeDef *) GPIOC_BASE)
#define USART1 (( USART_TypeDef *) USART1_BASE)
#define TIM2 (( TIM_TypeDef *) TIM2_BASE)
#define TIM3 (( TIM_TypeDef *) TIM3_BASE)
#define NVIC (( NVIC_TypeDef *) NVIC_BASE)
#define RCC_APB2ENR_IOPAEN ( 0x1UL << 2U )
#define RCC_APB2ENR_IOPCEN ( 0x1UL << 4U )
#define RCC_APB2ENR_USART1EN ( 0x1UL << 14U )
#define RCC_APB1ENR_TIM2EN ( 0x1UL << 0U )
#define RCC_APB1ENR_TIM3EN ( 0x1UL << 1U )
#define B1_USER (GPIOC->IDR & (0x1UL << 13U))

// Config and definitions for the timers
#define TIM_SMCR_SMS ( 0x7UL << 0U )
#define TIM_CR1_UDIS ( 0x1UL << 1U )
#define TIM_CR1_DIR ( 0x1UL << 4U )
#define TIM_CR1_CMS ( 0x3UL << 5U )
#define TIM_SR_UIF ( 0x1UL << 0U )
#define TIM_2S_CNT 0xE6 // Initial count for the 2s timer (230)
#define TIM_2S_PSC 0xF4 // Prescaler value for the 2s timer (244)
#define TIM_10MS_CNT 0x63C0 // Initial count for the 10ms timer (25536)
#define TIM_10MS_PSC 0x1 // Prescaler value for the 10ms timer (1)
#define TIM_CR1_CEN ( 0x1UL << 0U )
#define TIM_DIER_UIE ( 0x1UL << 0U )
#define NVIC_ISER_28 ( 0x1UL << 28U )

// Config and definitions for USART1
#define USART_CR1_UE ( 0x1UL << 13U ) // Enable USART
#define USART_CR1_M ( 0x1UL << 12U ) // Set data width to 8
#define USART_CR2_STOP ( 0x3UL << 12U ) // Configure 1 stop bit
#define USARTDIV 0x45 // Baud rate (115200)
#define USART_CR1_TE ( 0x1UL << 3U ) // Enable Transmission
#define USART_SR_TXE ( 0x1UL << 7U ) // Transmit data register empty flag


// Functions

// USART1
void USER_USART1_Init( void ); // Funtion to initialize USART1
int _write( int file, char *ptr, int len ); // Function to transmit output data via USART1

// CLK and GPIOs
void USER_RCC_ClockEnable( void ); // Initialize clks
void USER_GPIO_Init( void ); // Initialize GPIOs

// Timers
void USER_TIM2_Init( void ); // Initialize TIM2 timer
void USER_TIM3_Init( void ); // Initialize TIM3 timer
void TIM2_IRQHandler( void ); // TIM2 interrupt routine
void USER_TIM3_Delay( void ); // 1s delay using TIM3 timer



#endif /* MAIN_H_ */
