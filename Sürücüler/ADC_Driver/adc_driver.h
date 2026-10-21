/*
 * adc_driver.h
 *
 *  Created on: 16 Eki 2026
 *      Author: ASUS
 */

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include "main.h"


#define NUM_OF_ADC_CHANNELS  5         //Kanal sayısı

#define VDDA                3300      //mV cinsinden

#define DIGITAL_SCALE_6BITS    0x3F    //63
#define DIGITAL_SCALE_8BITS    0xFF   //255
#define DIGITAL_SCALE_10BITS   0x3FF  //1023
#define DIGITAL_SCALE_12BITS   0xFFF  //4095

#define DIGITAL_SCALE           DIGITAL_SCALE_12BITS


typedef enum
{

	DMA_Transfer_Not_Completed   = 0,
	DMA_Transfer_Completed       = 1,
	DMA_Transfer_Not_Yet_Started = 2

}DMA_Transfer_Status_t;


typedef enum
{

	ADC_Error                    = 0,
	ADC_Init_Start_Error         = 1

}ADC_Error_Status_t;


typedef struct
{

	ADC_HandleTypeDef              *hadc;

	uint16_t                       adcConvertedData[NUM_OF_ADC_CHANNELS];
	float                          adcVoltageData[NUM_OF_ADC_CHANNELS];

	uint8_t                        pot1Percentage;

	DMA_Transfer_Status_t          dmaTransferStatus;

	ADC_Error_Status_t             adcErrorStatus;

}ADC_Info_t;


void ADC_Initialization(ADC_Info_t *adcInfo, ADC_HandleTypeDef *hadc);
void ADC_DMA_Conversion(ADC_Info_t *adcInfo);

uint16_t MAP_Voltage_To_Percentage(float voltage, float inMin, float inMax, uint8_t outMin,uint8_t outMax);



#endif /* ADC_DRIVER_H_ */
