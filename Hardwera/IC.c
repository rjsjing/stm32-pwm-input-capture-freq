#include "stm32f10x.h"

void IC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;			    //上拉输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	TIM_InternalClockConfig(TIM3);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1;				   //ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;			  //PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;				//选择配置定时器通道1
	TIM_ICInitStruct.TIM_ICFilter = 0xF ;						//输入滤波器参数，可以过滤信号抖动
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising ;		//极性，选择为上升沿触发捕获
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;			//捕获预分频，选择不分频，每次信号都触发捕获
	TIM_ICInitStruct.TIM_ICSelection =  TIM_ICSelection_DirectTI;  //输入信号交叉，选择直通，不交叉  
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3,ENABLE);
	
}
uint32_t IC_GetFreq(void)
{
	return 1000000 / TIM_GetCapture1(TIM3);
}
