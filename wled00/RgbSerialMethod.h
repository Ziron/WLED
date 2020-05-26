#pragma once

class RgbSerialMethod
{
public:
  RgbSerialMethod(uint16_t pixelCount, size_t elementSize, size_t settingsSize) :
        _sizeData(pixelCount * elementSize + settingsSize)
    {
        _data = static_cast<uint8_t*>(malloc(_sizeData));
        memset(_data, 0, _sizeData);
    }

    ~RgbSerialMethod()
    {
        free(_data);
    }


    bool IsReadyToUpdate()
    {
      uint32_t delta = micros() - _endTime;
      return (delta >= 10000); // Max 100 Hz
    }
    
    void Initialize()
    {
      _endTime = micros();
    }
    
    void Update(bool)
    {
        while (!IsReadyToUpdate())
        {
#if !defined(ARDUINO_TEEONARDU_LEO) && !defined(ARDUINO_TEEONARDU_FLORA)
            yield(); // allows for system yield if needed
#endif
        }
      
        Serial.print(';');
        for (int i = 0; i < _sizeData; i++) {
          this->printHex(_data[i]);
        }

         // save EOD time for latch on next call
        _endTime = micros();
    }

    uint8_t* getData() const
    {
        return _data;
    };

    size_t getDataSize() const
    {
        return _sizeData;
    };

private:
    void printHex(uint8_t value) {
      uint8_t upper = value >> 4;

      if (upper < 10) {
        Serial.print((char)('0'+upper));
      } else {
        Serial.print((char)(('A'-10)+upper));
      }

      value &= 0x0F;

      if (value < 10) {
        Serial.print((char)('0'+value));
      } else {
        Serial.print((char)(('A'-10)+value));
      }
    }

    uint32_t _endTime;       // Latch timing reference
    const size_t  _sizeData;   // Size of '_data' buffer below
    uint8_t* _data;       // Holds LED color values
};
