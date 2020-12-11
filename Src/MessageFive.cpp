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
	nrzi.flag = DISABLE_NRZI;
}

/*
 * Private methods
 */
uint8_t MessageFive::getMode(void)
{
	return mode;
}

void MessageFive::runBenchmark(void)
{
	bool tmp = benchmarkMessage5[msgTick];

	if(tmp)
	{
		if(nrzi.flag == DISABLE_NRZI)
		{
			sendBit(tmp);
		}
	}
	else
	{
		if(nrzi.flag == ENABLE_NRZI)
		{
			// stay
			nrzi.transmitBit = !(nrzi.transmitBit);
			sendBit(nrzi.transmitBit);
		}
		else
		{
			// send bit
			sendBit(tmp);
		}
	}
}

void MessageFive::runRandomBits(void)
{
	sendBit(rand() % 2);
}

void MessageFive::sendBit(bool bit)
{
	if(bit)
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

void MessageFive::setNRZICoding(bool bit)
{
	this->nrzi.flag = bit;
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

