/*
 * MessageFive.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: handiko
 */

#include <MessageFive.hpp>

MessageFive::MessageFive() {
	// TODO Auto-generated constructor stub
	mode = MODE_BENCHMARK;
	startStopFlag = STOP;
}

/*
 * Private methods
 */
uint8_t MessageFive::getMode(void)
{
	return mode;
}

bool* MessageFive::getBenchmarkMessage(void)
{
	return benchmarkMessage5;
}

void MessageFive::runBenchmark(void)
{
	if(getBenchmarkMessage()[msgTick] % 2)
	{
		outputPorts.wavePort->BSRR = outputPorts.wavePin;
		outputPorts.scopePort->BSRR = outputPorts.scopePin;
	}
	else
	{
		outputPorts.wavePort->BRR = outputPorts.wavePin;
		outputPorts.scopePort->BRR = outputPorts.scopePin;
	}
}

void MessageFive::runRandomBits(void)
{
	if(rand() % 2)
	{
		outputPorts.wavePort->BSRR = outputPorts.wavePin;
		outputPorts.scopePort->BSRR = outputPorts.scopePin;
	}
	else
	{
		outputPorts.wavePort->BRR = outputPorts.wavePin;
		outputPorts.scopePort->BRR = outputPorts.scopePin;
	}
}

/*
 * Public methods
 */
void MessageFive::setOutputPorts(MSG5_OutputPorts_t outputPorts)
{
	this->outputPorts = outputPorts;
}

void MessageFive::setMode(uint8_t mode)
{
	this->mode = mode;
}

void MessageFive::tick(void)
{
	if(startStopFlag == START)
	{
		if(mode == MODE_BENCHMARK)
		{
			runBenchmark();
		}
		else if(mode == MODE_RANDOM_BITS)
		{
			runRandomBits();
		}

		msgTick++;

		if(mode == MODE_BENCHMARK)
		{
			if(msgTick == MESSAGE_5_BIT_LEN)
			{
				msgTick = 0;
			}
		}
	}
	else
	{
		msgTick=0;
	}
}

void MessageFive::start(void)
{
	startStopFlag = START;
}

void MessageFive::stop(void)
{
	startStopFlag = STOP;
}

MessageFive::~MessageFive() {
	// TODO Auto-generated destructor stub
}

