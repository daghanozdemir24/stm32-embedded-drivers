/*
 * adc_driver.c
 *
 *  Created on: 16 Eki 2026
 *      Author: ASUS
 */


#include "adc_driver.h"

DMA_Transfer_Status_t globalDmaTransferStatus = DMA_Transfer_Not_Yet_Started ;


void ADC_Initialization(ADC_Info_t *adcInfo, ADC_HandleTypeDef *hadc)
{
	adcInfo->hadc  = hadc;

	for(int i=0;i<NUM_OF_ADC_CHANNELS;i++)
	{
		adcInfo->adcConvertedData[i] = 0;
		adcInfo->adcVoltageData[i]   = 0;
	}

	adcInfo->dmaTransferStatus       = globalDmaTransferStatus;

	if(HAL_ADC_Start_DMA(adcInfo->hadc,(uint32_t*)adcInfo->adcConvertedData,NUM_OF_ADC_CHANNELS) != HAL_OK)
	{
		adcInfo->adcErrorStatus = ADC_Init_Start_Error;
	}

}
void ADC_DMA_Conversion(ADC_Info_t *adcInfo)
{
	adcInfo->dmaTransferStatus       = globalDmaTransferStatus;

	if(adcInfo->dmaTransferStatus  == DMA_Transfer_Completed)
	{

		globalDmaTransferStatus = DMA_Transfer_Not_Completed;

		for(int i=0;i<NUM_OF_ADC_CHANNELS;i++)
		{

			adcInfo->adcVoltageData[i] = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA,
																	  adcInfo->adcConvertedData[i],
																	  DIGITALSCALE / 1000.0
																	  ); //mV cisnine cevirme
		}

		adcInfo->pot1Percentage    = MAP_Voltage_To_Percentage(adcInfo->adcVoltageData[0],
				0.0,
				3.3,
				0,
				100
				);

	}


}

uint16_t MAP_Voltage_To_Percentage(float voltage, float inMin, float inMax, uint8_t outMin,uint8_t outMax)
{
	
	uint8_t percentage = 0;
	
	if (voltage <= inMin) return outMin;
	    if (voltage >= inMax) return outMax;
	
	percentage = (voltage - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
	
	return percentage;
	
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	//DMA Tranfer Status Completed
	globalDmaTransferStatus = DMA_Transfer_Completed;

}


void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	//DMA Transfer Status is Not Completed
	globalDmaTransferStatus = DMA_Transfer_Not_Completed;

}
