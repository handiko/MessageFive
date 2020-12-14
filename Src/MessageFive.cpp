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

	initDataAll();
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

void MessageFive::initMessageId(void)
{
	;
	// dummy method
}

void MessageFive::initRepInd(void)
{
	for(int i=0; i<MESSAGE_REPIND_BIT_LEN; i++)
		shipData.repInd[i]=0;
}

void MessageFive::initMmsi(void)
{
	for(int i=0; i<MESSAGE_MMSI_BIT_LEN; i++)
		shipData.mmsi[i] = 0;
}

void MessageFive::initVerInd(void)
{
	for(int i=0; i<MESSAGE_VERIND_BIT_LEN; i++)
		shipData.verInd[i]=0;
}

void MessageFive::initImo(void)
{
	for(int i=0; i<MESSAGE_IMO_BIT_LEN; i++)
		shipData.imo[i]=0;
}

void MessageFive::initCallsign(void)
{
	for(int i=0; i<MESSAGE_CALLSIGN_BIT_LEN; i++)
		shipData.callsign[i]=0;
}

void MessageFive::initName(void)
{
	for(int i=0; i<MESSAGE_NAME_BIT_LEN; i++)
		shipData.name[i]=0;
}

void MessageFive::initTypeOfShip(void)
{
	for(int i=0; i<MESSAGE_TYPEOFSHIP_BIT_LEN; i++)
		shipData.typeOfShip[i]=0;
}

void MessageFive::initDim(void)
{
	for(int i=0; i<MESSAGE_DIMENSION_BIT_LEN; i++)
		shipData.dim[i]=0;
}

void MessageFive::initNavdev(void)
{
	for(int i=0; i<MESSAGE_NAVDEV_BIT_LEN; i++)
		shipData.navdev[i]=0;
}

void MessageFive::initEta(void)
{
	for(int i=0; i<MESSAGE_ETA_BIT_LEN; i++)
		shipData.eta[i]=0;
}

void MessageFive::initDraught(void)
{
	for(int i=0; i<MESSAGE_DRAUGHT_BIT_LEN; i++)
		shipData.draught[i]=0;
}

void MessageFive::initDest(void)
{
	for(int i=0; i<MESSAGE_DEST_BIT_LEN; i++)
		shipData.dest[i]=0;
}

void MessageFive::initDte(void)
{
	;
	// dummy method
}

void MessageFive::initSpare(void)
{
	;
	// dummy method
}

void MessageFive::initDataAll(void)
{
	initMessageId(); //dummy
	initRepInd();
	initMmsi();
	initVerInd();
	initImo();
	initCallsign();
	initName();
	initTypeOfShip();
	initDim();
	initNavdev();
	initEta();
	initDraught();
	initDest();
	initDte();	//dummy
	initSpare(); //dummy
}

void MessageFive::processInputData(void)
{
	processRepInd();
	processMmsi();
	processVerInd();
	processImo();
	processCallsign();
	processName();
	processTypeOfShip();
	processDim();
	processNavdev();
	processEta();
	processDraught();
	processDest();
}

void MessageFive::processRepInd(void)
{
	for(int i = 0; i<MESSAGE_REPIND_BIT_LEN; i++)
	{
		shipData.repInd[i] = ((InputShipData.repInd >> i) & 0x01);
	}
}

void MessageFive::processMmsi(void)
{
	for(int i = 0; i<MESSAGE_MMSI_BIT_LEN; i++)
	{
		shipData.mmsi[i] = ((InputShipData.mmsi >> i) & 0x01);
	}
}

void MessageFive::processVerInd(void)
{
	for(int i = 0; i<MESSAGE_VERIND_BIT_LEN; i++)
	{
		shipData.verInd[i] = ((InputShipData.verInd >> i) & 0x01);
	}
}

void MessageFive::processImo(void)
{
	for(int i = 0; i<MESSAGE_IMO_BIT_LEN; i++)
	{
		shipData.imo[i] = ((InputShipData.imo >> i) & 0x01);
	}
}

void MessageFive::processCallsign(void)
{
	uint8_t idx=0;

	for(int i=0; i<(MESSAGE_CALLSIGN_BIT_LEN/6);i++)
	{
		if((InputShipData.callsign[i] > 32)&&(InputShipData.callsign[i] < 64))
		{
			for(int j=0;j<6;j++)
			{
				shipData.callsign[idx++] = (InputShipData.callsign[i] >> (5 - j)) & 0x01;
			}
		}
		else if((InputShipData.callsign[i] > 63)&&(InputShipData.callsign[i] < 96))
		{
			for(int j=0;j<6;j++)
			{
				shipData.callsign[idx++] = ((InputShipData.callsign[i] - 64) >> (5 - j)) & 0x01;
			}
		}
		else if(InputShipData.callsign[i] == 32)
		{
			for(int j=0;j<6;j++)
			{
				shipData.callsign[idx++] = (32 >> (5 - j)) & 0x01;
			}
		}
		else
		{
			for(int j=0;j<6;j++)
			{
				shipData.callsign[idx++] = 0;
			}
		}
	}
}

void MessageFive::processName(void)
{
	uint8_t idx=0;

	for(int i=0; i<(MESSAGE_NAME_BIT_LEN/6);i++)
	{
		if((InputShipData.name[i] > 32)&&(InputShipData.name[i] < 64))
		{
			for(int j=0;j<6;j++)
			{
				shipData.name[idx++] = (InputShipData.name[i] >> (5 - j)) & 0x01;
			}
		}
		else if((InputShipData.name[i] > 63)&&(InputShipData.name[i] < 96))
		{
			for(int j=0;j<6;j++)
			{
				shipData.name[idx++] = ((InputShipData.name[i] - 64) >> (5 - j)) & 0x01;
			}
		}
		else if(InputShipData.name[i] == 32)
		{
			for(int j=0;j<6;j++)
			{
				shipData.name[idx++] = (32 >> (5 - j)) & 0x01;
			}
		}
		else
		{
			for(int j=0;j<6;j++)
			{
				shipData.name[idx++] = 0;
			}
		}
	}
}

void MessageFive::processTypeOfShip(void)
{
	for(int i = 0; i<MESSAGE_TYPEOFSHIP_BIT_LEN; i++)
	{
		shipData.typeOfShip[i] = ((InputShipData.typeOfShip >> i) & 0x01);
	}
}

void MessageFive::processDim(void)
{
	uint32_t tmp = (InputShipData.dimA << 21)
			+ (InputShipData.dimB << 12)
			+ (InputShipData.dimC << 6)
			+ (InputShipData.dimD);

	for(int i = 0; i<MESSAGE_DIMENSION_BIT_LEN; i++)
	{
		shipData.dim[i] = ((tmp >> i) & 0x01);
	}
}

void MessageFive::processNavdev(void)
{
	for(int i = 0; i<MESSAGE_NAVDEV_BIT_LEN; i++)
	{
		shipData.navdev[i] = ((InputShipData.navdev >> i) & 0x01);
	}
}

void MessageFive::processEta(void)
{
	uint32_t tmp = (InputShipData.etaMonth << 16)
			+ (InputShipData.etaDay << 11)
			+ (InputShipData.etaHour << 6)
			+ (InputShipData.etaMinute);

	for(int i = 0; i<MESSAGE_ETA_BIT_LEN; i++)
	{
		shipData.eta[i] = ((tmp >> i) & 0x01);
	}
}

void MessageFive::processDraught(void)
{
	for(int i = 0; i<MESSAGE_DRAUGHT_BIT_LEN; i++)
	{
		shipData.draught[i] = ((InputShipData.draught >> i) & 0x01);
	}
}

void MessageFive::processDest(void)
{
	uint8_t idx=0;

	for(int i=0; i<(MESSAGE_NAME_BIT_LEN/6);i++)
	{
		if((InputShipData.dest[i] > 32)&&(InputShipData.dest[i] < 64))
		{
			for(int j=0;j<6;j++)
			{
				shipData.dest[idx++] = (InputShipData.dest[i] >> (5 - j)) & 0x01;
			}
		}
		else if((InputShipData.dest[i] > 63)&&(InputShipData.dest[i] < 96))
		{
			for(int j=0;j<6;j++)
			{
				shipData.dest[idx++] = ((InputShipData.dest[i] - 64) >> (5 - j)) & 0x01;
			}
		}
		else if(InputShipData.dest[i] == 32)
		{
			for(int j=0;j<6;j++)
			{
				shipData.dest[idx++] = (32 >> (5 - j)) & 0x01;
			}
		}
		else
		{
			for(int j=0;j<6;j++)
			{
				shipData.dest[idx++] = 0;
			}
		}
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

void MessageFive::setMessage(MSG5_InputData_t InputShipData)
{
	this->InputShipData = InputShipData;

	processInputData();
}

MessageFive::~MessageFive() {
	// TODO Auto-generated destructor stub
}

