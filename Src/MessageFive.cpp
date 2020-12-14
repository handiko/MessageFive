/*
 * MessageFive.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: handiko
 */

#include <MessageFive.hpp>

MessageFive::MessageFive() {
	// TODO Auto-generated constructor stub
	mode = MODE_NRZI_BENCHMARK;
	startStopFlag = STOP;
	nrzi.flag = DISABLE_NRZI;
}

/*
 * Private methods
 */
void MessageFive::runNrziBenchmark(void)
{
	sendBit(NrziBenchmarkMessage5[Ticks.nrziBenchmark++]);

	if(Ticks.nrziBenchmark == NRZI_BENCHMARK_BIT_LEN)
	{
		Ticks.nrziBenchmark = 0;
	}
}

void MessageFive::runHdlcBenchmark(void)
{
	bool tmp = HdlcBenchmarkMessage5[Ticks.hdlcBenchmark++];

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

	if(Ticks.hdlcBenchmark == HDLC_BENCHMARK_BIT_LEN)
	{
		Ticks.hdlcBenchmark = 0;
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
		outputPorts.soundPort->BSRR = outputPorts.soundPin;
	}
	else
	{
		outputPorts.wavePort->BRR = outputPorts.wavePin;
		outputPorts.scopePort->BRR = outputPorts.scopePin;
		outputPorts.soundPort->BRR = outputPorts.soundPin;
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
		if(mode == MODE_NRZI_BENCHMARK)
		{
			runNrziBenchmark();
		}
		else if(mode == MODE_HDLC_BENCHMARK)
		{
			runHdlcBenchmark();
		}
		else if(mode == MODE_RANDOM_BITS)
		{
			runRandomBits();
		}
	}
	else
	{
		Ticks.nrziBenchmark = 0;
		Ticks.hdlcBenchmark = 0;
		Ticks.randomBits = 0;
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

