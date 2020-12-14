/*
 * MessageFive.hpp
 *
 *  Created on: Dec 11, 2020
 *      Author: handiko
 */

#ifndef INC_MESSAGEFIVE_HPP_
#define INC_MESSAGEFIVE_HPP_

#include "main.h"

#include "stdlib.h"

#define MESSAGE_5_BIT_LEN	424
#define MESSAGE_5_BYTE_LEN	53

#define HDLC_BENCHMARK_BIT_LEN	(964/2)

#define MODE_BENCHMARK 0
#define MODE_HDLC_BENCHMARK 1
#define MODE_RANDOM_BITS 2

#define STOP 0
#define START 1

#define ENABLE_NRZI	1
#define DISABLE_NRZI 0

struct MSG5_OutputPorts_t {
	GPIO_TypeDef* wavePort;
	GPIO_TypeDef* scopePort;
	GPIO_TypeDef* soundPort;
	uint16_t wavePin;
	uint16_t scopePin;
	uint16_t soundPin;
};

struct MSG5_NrziCoding_t {
	bool flag = DISABLE_NRZI;
	bool transmitBit = 0;
};

class MessageFive {
private:
	const bool benchmarkMessage5[MESSAGE_5_BIT_LEN] = {
			0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
			1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,
			1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0,
			0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
			0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1,
			0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0,
			0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1,
			1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0,
			0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
			1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0
	};
	const bool HdlcBenchmarkMessage5[HDLC_BENCHMARK_BIT_LEN] = {
			0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,
			1,0,1,0,0,1,1,0,1,0,0,1,1,1,1,1,1,0,1,0,0,1,1,1,0,0,1,1,0,0,
			0,1,1,1,1,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
			0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,
			0,1,0,0,0,1,0,0,1,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0,1,1,0,0,
			0,1,0,0,0,1,1,0,0,0,1,0,1,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,1,0,
			1,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,0,
			1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
			1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,
			0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
			0,1,0,1,0,1,1,0,0,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,0,0,1,0,1,0,
			1,0,0,0,0,0,1,1,1,0,1,0,0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,
			1,0,0,1,1,0,0,1,0,1,1,0,1,1,0,1,0,1,1,0,0,1,1,1,0,1,0,1,0,1,
			1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
			0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
			0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,1,1,0,0,1,0,1,0,1,1,1,1,1,1,
			1,0,
	};
	uint8_t mode = MODE_BENCHMARK;
	uint16_t msgTick = 0;
	MSG5_OutputPorts_t outputPorts;
	bool startStopFlag = STOP;
	MSG5_NrziCoding_t nrzi;
	struct MSG5_Ticks_t {
		uint16_t benchmark = 0;
		uint16_t hdlcBenchmark = 0;
		uint16_t randomBits = 0;
	} Ticks;

	uint8_t getMode(void);
	void runBenchmark(void);
	void runHdlcBenchmark(void);
	void runRandomBits(void);
	void sendBit(bool bit);

public:
	MessageFive();

	void setOutputPorts(MSG5_OutputPorts_t outputPorts);
	void setMode(uint8_t mode);
	void setNRZICoding(bool nrziFlag);
	void tick(void);
	void start(void);
	void stop(void);

	virtual ~MessageFive();
};

#endif /* INC_MESSAGEFIVE_HPP_ */
