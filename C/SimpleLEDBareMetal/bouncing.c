/**
 **************************
 * @file           : bouncing.c
 * @author         : Humberto Barrera, Catalina Muñoz, Erick Campos, Mauricio Zavala
 * @board          : NUCLEO-F103RB
 **************************
 *
 * C code to Turn-ON and Turn-OFF the LD2 Led (w/o delay) in bare metal
 *
 **************************
 */

/* ********** START *************** */
/* Libraries, Definitions and Global Declarations */
#include <stdint.h>

/* Reset and Clock Control registers */
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

/* General Purpose I/O registers */
typedef struct {
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;

#define RCC_BASE 0x40021000UL   //	RCC base address
#define GPIOA_BASE 0x40010800UL //	GPIO Port A base address
#define RCC ((RCC_TypeDef *)RCC_BASE)
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)

void USER_RCC_ClockEnable(void);
void USER_GPIO_Init(void);

/* Superloop structure */
int main(void) {
  /* Declarations and Initializations */
  USER_RCC_ClockEnable();
  USER_GPIO_Init();
  /* Repetitive block */
  for (;;) {
    if (!(GPIOA->IDR & (0x1UL << 10U)))
      GPIOA->ODR ^= (0x1UL << 5U);
  }
}

void USER_RCC_ClockEnable(void) {
  // RCC_APB2ENR modified to IO port A clock enable
  RCC->APB2ENR = RCC->APB2ENR   //		RCC_APB2ENR actual value
                 |              //			to set
                 (0x1UL << 2U); //	(mask) IOPAEN bit
}

void USER_GPIO_Init(void) {
  // GPIOx_BSRR modified to reset pin10 of port A (LD2 is connected to PA5)
  GPIOA->BSRR = (0x1UL << 21U); //	immediate value

  // GPIOx_CRL modified to configure pin5 as output
  GPIOA->CRL = GPIOA->CRL       //		GPIOx_CRL actual value
               &                //			to clear
               ~(0x3UL << 22U)  //	(mask) CNF5[1:0] bits
               &                //			to clear
               ~(0x2UL << 20U); //	(mask) MODE5_1 bi
  GPIOA->CRL = GPIOA->CRL | (0X1UL << 20U);

  // pinPA10 as input floating
  // ESTO ES LO QUE CAMBIA
  GPIOA->CRH &= ~(0x2UL << 10U)   // PIN PA10
                & ~(0x3UL << 8U); // LED
  GPIOA->CRH |= (0x1UL << 10U);
}
