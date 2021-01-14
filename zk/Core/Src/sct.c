/*
 * sct.c
 *
 *  Created on: 24. 10. 2020
 *      Author: 435736
 */
#include "stm32f0xx.h"
#include "sct.h"
#include "main.h"

void sct_led(uint32_t value)
{
	for (uint8_t j = 0; j < 32; j++)
	{
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, (value & 1));
		value >>= 1;
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}

	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}

void sct_init(void)
{
	HAL_GPIO_WritePin(SCT_NOE_GPIO_Port, SCT_NOE_Pin, 0);
	sct_led(0);
}

void sct_value(uint16_t value)
{
	static const uint32_t reg_values[10] = {
		//PCDE--------GFAB @ DIS1
		//----PCDEGFAB---- @ DIS2
		//PCDE--------GFAB @ DIS3
		0b0000000000000010 << 16, //A DIS1
		0b0000000000100000 << 0, //A DIS2
		0b0000000000000010 << 0, //A DIS3
		0b0000000000000001 << 0, //B DIS3
		0b0100000000000000 << 0, //C DIS3
		0b0010000000000000 << 0, //D DIS3
		0b0000001000000000 << 0, //D DIS2
		0b0010000000000000 << 16, //D DIS1
		0b0001000000000000 << 16, //E DIS1
		0b0000000000000100 << 16, //F DIS1
	};

	uint32_t reg = 0;
	reg |= reg_values[value];
	sct_led(reg);
}
