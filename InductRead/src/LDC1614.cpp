#include "../include/LDC1614.h"

Sensors::LDC1614::LDC1614(const byte& addr):address_(addr) {}

void Sensors::LDC1614::sendCW(const byte buffer[][3], size_t size) {
    Wire.beginTransmission(address_);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < sizeof(buffer[i]); j++)
        {
            Wire.write(buffer[i][j]);
        }
    }
    Wire.endTransmission();
}

void Sensors::LDC1614::goSleep() {
    sendCW(sleepword_, 1);
}

void Sensors::LDC1614::awake() {
    sendCW(awakeword_, 1);
}

void Sensors::LDC1614::initialization() {
    goSleep();
    sendCW(initword_, sizeof(initword_)/sizeof(initword_[0]));
    awake();
}

void Sensors::LDC1614::readData() {
    int nChannels = 4, nRegs = 2;
    data_reg_ = 0x00;
    for (int i = 0; i < nChannels; i++)
    {
        for (int j = 0; j < nRegs; j++)
        {
            Wire.beginTransmission(address_);
            Wire.write(data_reg_);
            Wire.endTransmission();
            Wire.requestFrom((uint8_t)address_, (uint8_t)2);
            ch_[i].bits[3 - 2*j] = Wire.read();
            ch_[i].bits[2 - 2*j] = Wire.read();
            ++data_reg_;
        }
    }
}