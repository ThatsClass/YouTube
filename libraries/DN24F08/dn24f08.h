#ifndef DN24F08_H
#define DN24F08_H
#include <Arduino.h>

enum analogInputs {
    I1 = 0,
    I2 = 1,
    I3 = 2,
    I4 = 3,
    V1 = 4,
    V2 = 5,
    V3 = 6,
    V4 = 7
};

enum engineAverageType {
    TIME_MS = 0,
    READINGS = 1
};

enum engineDisplayType {
    IDLE = 0,
    CLEAR = 1,
    ANALOG = 2,
    INTEGER = 3,
    CHARACTERS = 4
};

class dn24f08 {
    public:
        dn24f08();
        void init();
        void setOutputs(uint8_t outputs);
        void setOutput(uint8_t output, bool state);
        void setAnalogCalibration(analogInputs input, float gain, float offset);
        void setAnalogEngineType(engineAverageType type);
        void setDisplayEngineType(engineDisplayType type);
        void setDisplayAnalogPin(analogInputs pin);
        void setDisplayInteger(uint16_t number);
        uint8_t getOutputs();
        bool getOutput(uint8_t output);
        uint8_t getInputs();
        bool getInput(uint8_t input);
        float getAnalog(analogInputs input);
        float getAnalogAverage(analogInputs input);
        void engineAnalogAverage_ms(uint16_t duration_ms);
        void engineAnalogAverage_readings(uint16_t readings);
        void engineDisplay();
        void displayFloat(float number);
        void displayInteger(uint16_t number);
        void displayClear();

    private:
        void setShift(uint8_t number, uint8_t digit, bool useDecimal);

        const uint8_t _rxTxPin = 13;

        const uint8_t _inData = 2;
        const uint8_t _inClock = 3;
        const uint8_t _inLoad = 4;

        const uint8_t _outData = 9;
        const uint8_t _outEnable = 10;
        const uint8_t _outLoad = 11;
        const uint8_t _outClock = 12;

        const uint8_t _segmentCharacters[37] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E, 0x6E, 0x2E, 0x60, 0x20, 0x78, 0x1C, 0x2A, 0xFC, 0x3A, 0xCE, 0xE6, 0x0A, 0xB6, 0x1E, 0x7C, 0x38, 0x76, 0x02, 0x10, 0xC6, 0x00 };
        const uint8_t _digitEnable[4] = { 0x70, 0xB0, 0XD0, 0xE0 };
        const uint8_t _decimalPoint = 0x1;

        static const uint8_t _analogPins = 8;
        const uint8_t _analogInputPins[_analogPins] = { A0, A1, A2, A3, A4, A5, A6, A7 };
        float _gains[_analogPins] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
        float _offsets[_analogPins] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        float _averageAnalog[_analogPins] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        uint32_t _averageSum[_analogPins] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        uint32_t _averageTime_ms[_analogPins] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        uint32_t _averageCounter[_analogPins] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        uint8_t _iterator = 0;

        char _converter[20];
        uint8_t _outputValue = 0;
        uint8_t _inputValue = 0;

        uint8_t _displayType = 0;
        uint8_t _displayAnalogPin = 0;
        uint16_t _displayNumber = 0;
        bool _update = false;
};
#endif