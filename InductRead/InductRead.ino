/*
 Name:		InductRead.ino
 Created:	8/31/2021 8:31:05 PM
 Author:	jdhuang
*/

#include "include/LDC1614.h"

#define COMBINE(a,b) a##b

int nDevices = 0;
byte addr[128];

Sensors::LDC1614 plate1(0x2A);
Sensors::LDC1614 plate2(0x2B);

int i = 0;

void addressEnabled(int& nDevices, byte* addr) {
    Serial.println("Scanning...");

    for (byte address = 1; address < 127; ++address) {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            addr[nDevices] = address;
            Serial.print(address, HEX);
            Serial.println("  !");

            ++nDevices;
        }
        else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
    }
    else {
        Serial.print(nDevices);
        Serial.println("done\n");
    }

    delay(5000); // Wait 5 seconds for next scan
}

void setup() {
    Wire.begin();
    addressEnabled(nDevices, addr);

    Serial.begin(9600);
    while (!Serial); // Leonardo: wait for serial monitor

    plate1.initialization();
}

void loop() {
    Sensors::LDC1614::ChannelData ch0,ch1,ch2,ch3;

    plate1.readData();
    ch0 = plate1.returnChannelData()[0];
    ch1 = plate1.returnChannelData()[1];
    ch2 = plate1.returnChannelData()[2];

    double invL, f, L;
    f = 1 * 40 * pow(10, 6) * (ch0.number & (0x0fffffff)) / pow(2, 28);
    invL = (4 * PI * PI * 140 * pow(10, -12) * f * f);
    L = 1000000.0 / invL;
    Serial.print(L);
    Serial.write(13);
    Serial.write(10);

    f = 1 * 40 * pow(10, 6) * (ch1.number & (0x0fffffff)) / pow(2, 28);
    invL = (4 * PI * PI * 140 * pow(10, -12) * f * f);
    L = 1000000.0 / invL;
    Serial.print(L);
    Serial.write(13);
    Serial.write(10);

    f = 1 * 40 * pow(10, 6) * (ch2.number & (0x0fffffff)) / pow(2, 28);
    invL = (4 * PI * PI * 140 * pow(10, -12) * f * f);
    L = 1000000.0 / invL;
    Serial.print(L);
    Serial.write(13);
    Serial.write(10);

    delay(500);
}