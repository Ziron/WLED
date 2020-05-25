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
      return true;
    }
    
    void Initialize()
    {
      
    }

    void Update(bool)
    {
        Serial.print(';');
        for (int i = 0; i < _sizeData; i++) {
          Serial.print(_data[i], HEX);
        }
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
    const size_t  _sizeData;   // Size of '_data' buffer below
    uint8_t* _data;       // Holds LED color values
};
