/**
* @file 		rcc.h
* @brief		Header file of RCC drivers.
* @author		Julien
* @date			26/01/2015
* @version	0.1 
* @details	
*
*	Header file listing the functions required to initialize the different
* clocks of the system.
*
* /!\ So far, only the clocks of the GPIOs are enabled
*/

#ifndef RCC_H
#define RCC_H

/* Clock enable for GPIOx */
#define GPIOA_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOAEN)
#define GPIOB_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOBEN)
#define GPIOC_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOCEN)
#define GPIOD_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIODEN)
#define GPIOE_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOEEN)
#define GPIOF_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOFEN)
#define GPIOG_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOGEN)
#define GPIOH_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOHEN)
#define GPIOI_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOIEN)
#define GPIOJ_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOJEN)
#define GPIOK_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOKEN)

/* Clock enable for TIMx */
#define TIM2_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM2EN)
#define TIM3_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM3EN)
#define TIM4_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM4EN)
#define TIM5_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM5EN)
#define TIM6_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM6EN)
#define TIM7_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM7EN)

/* Clock enable for SPI1 */
#define SPI1_CLK_ENABLE() 			(RCC->APB2ENR |= RCC_APB2ENR_SPI1EN)

/* Clock enable for SYSCFG - System Configuration */
#define SYSCFG_CLK_ENABLE()			(RCC->APB2ENR |= 0x00004000)


#endif
