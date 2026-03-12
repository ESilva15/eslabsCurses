#ifndef __DATA__CONTAINER__
#define __DATA__CONTAINER__

#include <cstdint>
#include <stdint.h>
#include <string.h>
#include <Arduino.h>
#include <type_traits>

enum DataType {
    DT_UINT8 = 0, DT_INT8 = 1, DT_UINT16 = 2, DT_INT16 = 3,
    DT_UINT32 = 4, DT_INT32 = 5, DT_UINT64 = 6, DT_INT64 = 7,
    DT_STRING = 8, DT_CHAR = 9
};

class IDataContainer {
  public:
    // hasChanged will take the new data, check if its different from what was
    // set before and update it or not
    virtual bool hasChanged(size_t len) = 0;

    virtual void SetValue(void* data) = 0;
    virtual void* GetPrevValue() = 0;
    virtual void* GetValue() = 0;

    virtual const char* ToString() = 0;

    virtual uint16_t toUint() { return 0; }
};

// Note: need to implement checks for these string operations
class StrContainer : public IDataContainer {
  private:
    bool changed = false;
    DataType type;
    size_t dataSize;
    // NOTE: I'm passing dataSize but the buffers still are fixed size ???
    char prevValue[64] = {0};
    char buffer[64] = {0};

  public:
    StrContainer(DataType type) : type(type) {}

    bool hasChanged(size_t len) override {
      return this->changed;
    }

    const char* ToString() override {
      return buffer;
    }

    void SetValue(void* data) override {
      char* newdata = (char*)data;

      if(strcmp(buffer, newdata) == 0) {
        return;
      }

      strcpy(this->prevValue, this->buffer);
      strcpy(this->buffer, newdata);
      this->changed = true;
    }

    void* GetValue() override {
      return buffer;
    }

    void* GetPrevValue() override {
      return prevValue;
    }
};

template <typename T>
class ValueContainer : public IDataContainer {
  private:
    T currentVal;
    T prevVal;
    DataType type;
    bool changed = false;
    char strBuffer[21] = {0};
    char prevStrBuffer[21] = {0};

    void renderToBuffer() {
        if constexpr (std::is_floating_point<T>::value) {
          dtostrf(currentVal, 4, 2, strBuffer);
        } 
        else if constexpr (sizeof(T) <= 4) {
            if constexpr (std::is_unsigned<T>::value) {
                ultoa((unsigned long)currentVal, strBuffer, 10); // Use ultoa for unsigned
            } else {
                ltoa((long)currentVal, strBuffer, 10);
            }
        } 
        else {
            // 64-bit handling
            if constexpr (std::is_unsigned<T>::value) {
                sprintf(strBuffer, "%llu", (uint64_t)currentVal);
            } else {
                sprintf(strBuffer, "%lld", (int64_t)currentVal);
            }
        }
    }

  public:
    ValueContainer<T>(DataType type) : type(type) {}

    bool hasChanged(size_t len) override {
      return this->changed;
    }

    void SetValue(void* data) override {
      T newValue = *(T*)data;
      if (newValue != currentVal) {
        strcpy(prevStrBuffer, strBuffer);

        prevVal = currentVal;
        currentVal = newValue;
        changed = true;

        // pre-format
        this->renderToBuffer();
      }
    }

    void* GetValue() override {
      return (void*)strBuffer;
    }

    void* GetPrevValue() override {
      return (void*)prevStrBuffer;
    }

    const char* ToString() override {
      return strBuffer;
    }
};

IDataContainer* CreateContainer(DataType type);

#endif
