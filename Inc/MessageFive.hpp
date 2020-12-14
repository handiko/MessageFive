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

#define NRZI_BENCHMARK_BIT_LEN	(964/2)
#define HDLC_BENCHMARK_BIT_LEN	(964/2)

#define MODE_NRZI_BENCHMARK 0
#define MODE_HDLC_BENCHMARK 1
#define MODE_RANDOM_BITS 2

#define STOP 0
#define START 1

#define ENABLE_NRZI	1
#define DISABLE_NRZI 0

#define MESSAGE_DEFAULT	0

#define MESSAGE_5_BIT_LEN 424

#define MESSAGE_ID_BIT_LEN	6
#define MESSAGE_REPIND_BIT_LEN	2
#define MESSAGE_MMSI_BIT_LEN 30
#define MESSAGE_VERIND_BIT_LEN 2
#define MESSAGE_IMO_BIT_LEN 30
#define MESSAGE_CALLSIGN_BIT_LEN 42
#define MESSAGE_NAME_BIT_LEN 120
#define MESSAGE_TYPEOFSHIP_BIT_LEN 8
#define MESSAGE_DIMENSION_BIT_LEN 30
#define MESSAGE_NAVDEV_BIT_LEN 4
#define MESSAGE_ETA_BIT_LEN 20
#define MESSAGE_DRAUGHT_BIT_LEN 8
#define MESSAGE_DEST_BIT_LEN 120

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

struct MSG5_InputData_t {
	uint8_t repInd = MESSAGE_DEFAULT;
	uint32_t mmsi = 525777777;
	uint8_t verInd = MESSAGE_DEFAULT;
	uint32_t imo = MESSAGE_DEFAULT;
	char callsign[MESSAGE_CALLSIGN_BIT_LEN/6] = "YD1SDL";
	char name[MESSAGE_NAME_BIT_LEN/6] = "MV.HANDIKO \(^*^)/";
	uint8_t typeOfShip = MILITARY_OPS;
	uint16_t dimA = 53;
	uint16_t dimB = 15;
	uint8_t dimC = 15;
	uint8_t dimD = 15;
	uint8_t navdev = NAV_GPS_GLONASS;
	uint8_t etaMonth = JANUARY;
	uint8_t etaDay = 18;
	uint8_t etaHour = 21;
	uint8_t etaMinute = 12;
	uint8_t draught = 48;
	char dest[MESSAGE_DEST_BIT_LEN/6] = "Ayo kita kemana?";
	bool dte = MESSAGE_DEFAULT;
	bool spare = MESSAGE_DEFAULT;
};

class MessageFive {
private:
	const bool NrziBenchmarkMessage5[NRZI_BENCHMARK_BIT_LEN] = {
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
			1,0
	};
	const bool HdlcBenchmarkMessage5[HDLC_BENCHMARK_BIT_LEN] = {
			1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,
			1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,0,0,1,0,1,1,0,1,0,1,0,1,
			1,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,1,1,
			1,0,0,1,1,0,0,1,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,
			1,0,0,1,1,0,1,0,1,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,
			0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1,1,1,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
			0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,
			0,0,1,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,1,1,0,0,0,0,0,0,
			1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,0,1,0,0,0,0,0,1,1,1,1,1,
			1,0
	};
	uint8_t mode = MODE_NRZI_BENCHMARK;
	MSG5_OutputPorts_t outputPorts;
	bool startStopFlag = STOP;
	MSG5_NrziCoding_t nrzi;

	struct MSG5_Ticks_t {
		uint16_t nrziBenchmark = 0;
		uint16_t hdlcBenchmark = 0;
		uint16_t randomBits = 0;
	} Ticks;

	MSG5_InputData_t InputShipData;

	struct MSG5_InnerData_t {
		const bool messageId[MESSAGE_ID_BIT_LEN] = {0,0,0,1,0,1};
		bool repInd[MESSAGE_REPIND_BIT_LEN];
		bool mmsi[MESSAGE_MMSI_BIT_LEN];
		bool verInd[MESSAGE_VERIND_BIT_LEN];
		bool imo[MESSAGE_IMO_BIT_LEN];
		bool callsign[MESSAGE_CALLSIGN_BIT_LEN];
		bool name[MESSAGE_NAME_BIT_LEN];
		bool typeOfShip[MESSAGE_TYPEOFSHIP_BIT_LEN];
		bool dim[MESSAGE_DIMENSION_BIT_LEN];
		bool navdev[MESSAGE_NAVDEV_BIT_LEN];
		bool eta[MESSAGE_ETA_BIT_LEN];
		bool draught[MESSAGE_DRAUGHT_BIT_LEN];
		bool dest[MESSAGE_DEST_BIT_LEN];
		bool dte;
		bool spare;
	} shipData;

	void runNrziBenchmark(void);
	void runHdlcBenchmark(void);
	void runRandomBits(void);
	void sendBit(bool bit);

	void processInputData(void);

public:
	MessageFive();

	void setOutputPorts(MSG5_OutputPorts_t outputPorts);
	void setMode(uint8_t mode);
	void setNRZICoding(bool nrziFlag);
	void tick(void);
	void start(void);
	void stop(void);

	void setMessage(MSG5_InputData_t InputShipData);

	virtual ~MessageFive();
};

#endif /* INC_MESSAGEFIVE_HPP_ */
