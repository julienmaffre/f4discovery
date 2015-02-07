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
#define __GPIOA_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOAEN)
#define __GPIOB_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOBEN)
#define __GPIOC_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOCEN)
#define __GPIOD_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIODEN)
#define __GPIOE_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOEEN)
#define __GPIOF_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOFEN)
#define __GPIOG_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOGEN)
#define __GPIOH_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOHEN)
#define __GPIOI_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOIEN)
#define __GPIOJ_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOJEN)
#define __GPIOK_CLK_ENABLE() 			(RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOKEN)

/* Clock enable for TIMx */
#define __TIM2_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM2EN)
#define __TIM3_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM3EN)
#define __TIM4_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM4EN)
#define __TIM5_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM5EN)
#define __TIM6_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM6EN)
#define __TIM7_CLK_ENABLE()				(RCC->APB1ENR |= RCC_APB1ENR_TIM7EN)

/* Clock enable for SYSCFG - System Configuration */
#define __SYSCFG_CLK_ENABLE()			(RCC->APB2ENR |= 0x00004000)


#endif
