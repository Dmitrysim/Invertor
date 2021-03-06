#include "main.h"

/******************************************************** Variables ************************************************************************************************/
	
uint16_t sin_data[240] = 
{0,13,26,39,52,65,78,91,104,117,130,143,156,196,182,195,207,220,233,246,258,271,284,296,309,321,333,346,358,370,
382,394,406,418,430,442,453,465,477,488,500,511,522,533,544,555,566,577,587,598,608,619,629,639,649,659,669,678,688,697,
707,716,725,734,743,751,760,768,777,785,793,801,809,816,824,831,838,845,852,859,866,872,878,884,891,896,902,908,913,918,
923,928,933,938,942,946,951,955,958,962,965,969,972,975,978,980,983,985,987,989,991,993,994,995,996,997,998,999,999,999,
999,999,999,998,997,996,995,994,993,991,989,987,985,983,980,978,975,972,969,965,962,958,955,951,946,942,938,933,928,923,
918,913,908,902,896,891,884,878,872,866,859,852,845,838,831,824,816,809,801,793,785,777,768,760,751,743,734,725,716,707,
697,688,678,669,659,649,639,629,619,608,598,587,577,566,555,544,533,522,511,500,488,477,465,453,442,430,418,406,394,382,
370,358,346,333,321,309,296,284,271,258,246,233,220,207,195,182,196,156,143,130,117,104,91,78,65,52,39,26,13,0};
																										
uint16_t sin_step;
uint8_t sin_status;

/***************************************************** Functions and tasks *****************************************************************************************/

void vTask1 (void *argument); 

/************************************************************ Main *************************************************************************************************/

int main(void){

	RCC_Init();	
	GPIO_Init();
	PWM_sin_start();
	
	__enable_irq(); 

	xTaskCreate(vTask1, "LED", 32, NULL, 1, NULL);

	vTaskStartScheduler();
	
	while(1)
	{
		
	}
	
}

/*********************************************************** Use tasks **********************************************************************************************/

void vTask1 (void *argument){

		while(1)
		{	
			GPIOC->ODR ^= GPIO_ODR_ODR8;							
			vTaskDelay(1000);	
		}
}


void TIM6_DAC_IRQHandler(void){
	
	TIM6->SR &= ~TIM_SR_UIF; 	

	if(sin_status == 0){TIM2->CCR1 = sin_data[sin_step];}
	if(sin_status == 1){TIM2->CCR2 = sin_data[sin_step];}
	
	sin_step++;
	
	if(sin_step >= 240){
			
			sin_step=0;
			sin_status = sin_status ? 0 : 1;
		
	}
	
}
















