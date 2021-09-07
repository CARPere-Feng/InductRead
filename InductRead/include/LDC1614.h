#ifndef _LDC1614_H_
#define _LDC1614_H_

#include <Wire.h>
#include <Arduino.h>
#include <math.h>

#define INT8 char
#define INT16 short
#define INT32 long
#define UINT8 unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned long
#define PI 3.1415926535

namespace Sensors {
class LDC1614 {
public:
	LDC1614() = default;
	explicit LDC1614(const byte& addr);
	~LDC1614() = default;

	union ChannelData
	{
		byte bits[4];
		UINT32 number = 0;
	};

	void sendCW(const byte buffer[][3], size_t size);
	void goSleep();
	void awake();
	virtual void initialization();
	void readData();
	ChannelData* returnChannelData() { return ch_; }
private:
	const byte address_;
	ChannelData ch_[4];
	const byte sleepword_[1][3] = { {0x1C, 0x80, 0x00} };
	const byte awakeword_[1][3] = { {0x1A, 0x56, 0x81} };
	const byte initword_[6][3] = { {0x1B, 0xC2, 0x0D},
									{0x17, 0x10, 0x01},
									{0x21, 0xC8, 0x00},
									{0x13, 0x00, 0x0A},
									{0x0B, 0x10, 0x00},
									{0x0F, 0x00, 0x00} };
	const byte init2ch_[6][3] = { {0x1B, 0x82, 0x0D},
								{0x15, 0x10, 0x01},
								{0x1F, 0xC8, 0x00},
								{0x11, 0x00, 0x0A},
								{0x09, 0x10, 0x00},
								{0x0D, 0x00, 0x00} };
	byte data_reg_ = 0x00;
};	// class LDC1614
}	// namespace Sensors

#endif