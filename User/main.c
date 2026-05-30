#include "stm32f10x.h"
#include "Delay.h"
#include "PWM.h"
#include "OLED.h"
#include "IC.h"


int main(void)
{
	IC_Init();
    OLED_Init();
	PWM_Init();
	PWM_SetPrescaler(720-1);				//Fre=72M/(psc+1)/100
	PWM_SetCompare1(50);					//Duty = CCP/(ARR+1)
	OLED_ShowString(1,1,"Ferq:00000Hz");

    while (1)
    {
     OLED_ShowNum(1,6,IC_GetFreq(),5);
    }
}
