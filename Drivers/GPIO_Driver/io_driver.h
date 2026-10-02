/*
 * io_driver.h
 *
 *  Created on: 1 Eki 2026
 *      Author: ASUS
 */

#ifndef IO_DRIVER_H_
#define IO_DRIVER_H_

#include "main.h"

#define DEBOUNCE_TIME    100

typedef enum{
	Input_Status_Low       = 0,
	Input_Status_High        
}Input_Status_t;

typedef struct
{
	GPIO_TypeDef    *GPIOx;                
	uint16_t        GPIO_Pin;
	uint16_t        numOfInput;
	
	GPIO_PinState   currentState;
	GPIO_PinState   lastState;
	
	Input_Status_t   InputStatus;
	
	
	uint32_t         currentTime;
	uint32_t         deobunceTime;	
}Input_State_t;


typedef struct
{
	Input_State_t userButton;

}Input_Info_t;


typedef struct
{
	GPIO_TypeDef   *GPIOx;
	uint16_t       GPIO_Pin;
	GPIO_PinState  pinState;
	
}Output_State_t;


typedef struct
{
	Output_State_t      ledGreen;
	Output_State_t      ledRed;
	Output_State_t      ledOrange;
	Output_State_t      ledBlue;
	
}Output_Info_t;

typedef struct
{
	Input_Info_t        inputsInfo;	
	Output_Info_t       outputsInfo;
}IO_Info_t;


void IO_Initialization(IO_Info_t *ioInfo);
void IO_Status_Control(IO_Info_t *ioInfo);
void IO_Input_Control_With_Debounce(Input_State_t *inputsInfo);
void IO_Output_Control(Output_State_t *outputsInfo);


#endif /* IO_DRIVER_H_ */
