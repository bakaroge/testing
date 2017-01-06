#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "led.h"




void F407_LED_setup(void);
void F407_PWM_LED_setup(float *percentages);
void F407_PWM_LED_Timer(float *percentages);//percentages = size 4 array of float (4 LED in F407)
void F407_Duty_Cycle(float* percentages);
void NUCLEO_LED_setup(void);
void NUCLEO_PMW_LED_setup(float percentage);
void NUCLEO_LED_Timer(float percentage );
void NUCLEO_Duty_Cycle(float percentage);
void F407_Button_setup(void);
void NUCLEO_Button_setup(void);
void F407_SETUP_LED_LIB(void);
void NUCLEO_SETUP_LED_LIB(void);


void F407_LED_setup(void){
	 GPIO_InitTypeDef GPIO_InitStruct;

	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12; // we want to configure all LED GPIO pins
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	// this sets the GPIO modules clock speed
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	// this sets the pin type to push / pull (as opposed to open drain)
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// this sets the pullup / pulldown resistors to be inactive

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void F407_PWM_LED_setup(float *percentages){

 GPIO_InitTypeDef GPIO_InitStruct;

    /* Clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);



    /* Alternating functions for pins */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

    /* Set pins */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    
	GPIO_Init(GPIOD, &GPIO_InitStruct);	
	
}

void F407_PWM_LED_Timer(float *percentages){ //percentages = size 4 array of float (4 LED in F407)
	float max=8399;
	
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_TimeBaseInitTypeDef TIM_BaseStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_BaseStruct.TIM_Prescaler = 0;
	TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseStruct.TIM_Period = 8399; /* 10kHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
   
	TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);
    TIM_Cmd(TIM4, ENABLE);
	
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
	//clear on comparematch
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OCStruct.TIM_Pulse = percentages[0]/100*max;
    TIM_OC1Init(TIM4, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
    TIM_OCStruct.TIM_Pulse = percentages[1]/100*max; /* 50% duty cycle */
    TIM_OC2Init(TIM4, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCStruct.TIM_Pulse = percentages[2]/100*max; /* 75% duty cycle */
    TIM_OC3Init(TIM4, &TIM_OCStruct);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OCStruct.TIM_Pulse = percentages[3]/100*max; /* 100% duty cycle */
    TIM_OC4Init(TIM4, &TIM_OCStruct);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
}

void F407_Duty_Cycle(float* percentages){
	TIM_SetCompare1(TIM4,percentages[0]);
	TIM_SetCompare2(TIM4,percentages[1]);
	TIM_SetCompare3(TIM4,percentages[2]);
	TIM_SetCompare4(TIM4,percentages[3]);

}

void NUCLEO_LED_setup(void){
	 GPIO_InitTypeDef GPIO_InitStruct;
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 ;
	    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void NUCLEO_PMW_LED_setup(float percentage){
	 GPIO_InitTypeDef GPIO_InitStruct;
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	 GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 ;
	    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	 
	 GPIO_Init(GPIOA, &GPIO_InitStruct);
	 NUCLEO_LED_Timer(percentage);
}

void NUCLEO_LED_Timer(float percentage ){ //duty cycle
	float max=8399;
	float sent=percentage*max/100;
	
	TIM_OCInitTypeDef TIM_OCStruct;
	TIM_TimeBaseInitTypeDef TIM_BaseStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_BaseStruct.TIM_Prescaler = 0;
	TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseStruct.TIM_Period = 8399; /* 10kHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
   
	TIM_TimeBaseInit(TIM2, &TIM_BaseStruct);
    TIM_Cmd(TIM2, ENABLE);
	
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OCStruct.TIM_Pulse = sent; /* 25% duty cycle */
    TIM_OC1Init(TIM2, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
}

void NUCLEO_Duty_Cycle(float percentage){
	TIM_SetCompare1(TIM2,percentage/100*8399);
}

void F407_Button_setup(void){
	 GPIO_InitTypeDef GPIO_InitStruct;

	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;		  // we want to configure PA0
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; 	  // we want it to be an input
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // this sets the pin type to push / pull (as opposed to open drain)
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;   // this enables the pulldown resistor --> we want to detect a high level
		GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void NUCLEO_Button_setup(void){
	 GPIO_InitTypeDef GPIO_InitStruct;
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 ;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStruct);

}

void F407_SETUP_LED_LIB(void){
	F407_LED_setup();
	F407_Button_setup();
}

void NUCLEO_SETUP_LED_LIB(void){
	NUCLEO_LED_setup();
	NUCLEO_Button_setup();
}

//by Ivan (bakaroge　バカロゲ)

