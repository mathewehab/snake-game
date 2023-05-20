#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include "UART.h"
#include "bsp.h"
#include "game.h"
#include "semphr.h"

extern int gameOver,record,score,start,Level, LevelUp;
xSemaphoreHandle xBinarySemaphore;


void vUserInputTask(void *pvParameters)
{
// Establish the task's period.
const TickType_t xDelay = pdMS_TO_TICKS(100);
TickType_t xLastWakeTime = xTaskGetTickCount();
		for(;;){
			xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
			GPIOF->DATA ^= RED_LED;
			input(uart0_Receivechar());   // Block until the next release time.
			vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}



void vGameTask(void *pvParameters)
{
	// Establish the task's period.
	TickType_t xDelay = pdMS_TO_TICKS(350);
	TickType_t xLastWakeTime = xTaskGetTickCount();
	print("***WELCOME***\r\n");
	print("KEY SHORTCUTS: \r\n press 'w' for UP \r\n press 's' for DOWN \r\n press 'a' for LEFT \r\n press 'd' for RIGHT \r\n press 'z' to quit the game \r\n");
	print("***PLEASE PRESS t TO START***\r\n");
	while(start != 1);
		
	while(1) {		
		
		    
        while(gameOver != 1){
                logic();
                map_draw();
								if(Level <= 6){ /* to speed up the snake */
									
								xDelay = pdMS_TO_TICKS(350-Level*50);
								vTaskDelay(xDelay);
									
								} 
								else{
								xDelay = pdMS_TO_TICKS(50);
								vTaskDelay(xDelay);
								}

            }
				mainloop();
				if(gameOver==1){
					break;
				}
	}
	print("***GOODBYE***\r\n");
  vTaskDelete(NULL);
}

void UART0_Handler( void ){
	//UART0->ICR &= ~(0x010); // Clear receive interrupt
	UART0->ICR |= (1<<4);
	//variable that will be updated by the semaphore API to indicate a context switch is needed so ISR call schedule 
	BaseType_t contextRequst;
	//initialize it to fals which means no context required now 
	contextRequst=pdFALSE;
	//give semaphore by incrementing it to indicate ISR occured 
	xSemaphoreGiveFromISR(xBinarySemaphore,&contextRequst);
	//If higher priority task is unblocked due to giving the semaphore then do a context switch by calling the scheduler
	portYIELD_FROM_ISR(contextRequst);
}
	
int main()
{
	xBinarySemaphore = xSemaphoreCreateBinary();
	if( xBinarySemaphore != NULL ){
		//init portF
		PORTF_init();	
		PORTA_init();
		UART_init();
		
		xTaskCreate(vUserInputTask, "User input Task ",200, NULL, 2, NULL);
		xTaskCreate(vGameTask, "Game Task ",200, NULL, 1, NULL);
		// Startup of the FreeRTOS scheduler.  The program should block here.
		vTaskStartScheduler();
	}
	// The following line should never be reached.  Failure to allocate enough
	//	memory from the heap would be one reason.
	for (;;);
	
}

