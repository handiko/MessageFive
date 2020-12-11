/*
 * MessageFive.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: handiko
 */

#include <MessageFive.hpp>

MessageFive::MessageFive() {
	// TODO Auto-generated constructor stub

}

bool* MessageFive::getBenchmarkMessage(void)
{
	return benchmarkMessage5;
}

void MessageFive::tick(void)
{
	if(getBenchmarkMessage()[msgTick] % 2)
	{
		WAVE_GPIO_Port->BSRR = WAVE_Pin;
		SCOPE_GPIO_Port->BSRR = SCOPE_Pin;
	}
	else
	{
		WAVE_GPIO_Port->BRR = WAVE_Pin;
		SCOPE_GPIO_Port->BRR = SCOPE_Pin;
	}

	msgTick++;

	if(msgTick == MESSAGE_5_BIT_LEN)
	{
		msgTick = 0;
	}
}

MessageFive::~MessageFive() {
	// TODO Auto-generated destructor stub
}

