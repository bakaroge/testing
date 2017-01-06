#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"



#define LED1 GPIOD, GPIO_Pin_12
#define LED2 GPIOD, GPIO_Pin_13
#define LED3 GPIOD, GPIO_Pin_14
#define LED4 GPIOD, GPIO_Pin_15
#define F4Button GPIOA, GPIO_Pin_0
#define LED  GPIOA, GPIO_Pin_5
#define NuButton GPIOC, GPIO_Pin_13

//F4 = F407V Development Board
//Nu = F401 Nucleo Development Board
//10KHz PWM is used for simplicity

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



/*
 *
 * int main(void)
{

	SETUP_LED_LIB();
    while(1)
    {	if(GPIO_ReadInputDataBit(Button == 1)){GPIO_SetBits(LED1);}
    	else GPIO_ResetBits(LED1);

    }
}


*
*/

//by Ivan (bakaroge　バカロゲ)


