#ifndef __DATA__CONTAINER__
#define __DATA__CONTAINER__

#include <stdint.h>
#include <string.h>

class IDataContainer {
  public:
    virtual bool hasChanged() = 0;

    virtual void SetValue(void* data) = 0;
    virtual void* GetPrevValue() = 0;
    virtual void* GetCurrentValue() = 0;

    virtual const char* toString() = 0;

    virtual uint16_t toUint() { return 0; }
};

// Note: need to implement checks for these string operations
class StrContainer : public IDataContainer {
  private:
    char prevBuffer[64];
    char buffer[64];

  public:
    StrContainer() {}

    bool hasChanged() override {
      return strcmp(prevBuffer, buffer) != 0;
    }

    const char* toString() override {
      return buffer;
    }

    void SetValue(void* data) override {
      char* str = (char*)data;
      strcpy(buffer, str);
    }

    void* GetPrevValue() override {
      return prevBuffer;
    }

    void* GetCurrentValue() override {
      return buffer;
    }
};

template <typename T>
class NumContainer : public IDataContainer {
  private:
    T* source;
    T lastValue;
    char buffer[64];
    char oldBuffer[64];

  public:
    NumContainer() {}
    NumContainer(T* src) : source(src), lastValue(*src) {}

    bool hasChanged() override {
      return *source != lastValue;
    }
    
    const char* toString() override {
      ltoa((long)*source, buffer, 10);
      return buffer;
    }

    void SetValue(void* data) override {
      *source = *(T*)data;
    }
};

#endif
