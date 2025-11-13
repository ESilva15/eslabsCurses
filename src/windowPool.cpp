#include "windowPool.h"
#include "UIComponent.h"
#include "UIBar.h"
#include "UIString.h"
#include "UITable.h"
#include "values.h"

namespace WindowPool {
  WindowEntry pool[MAX_WINDOWS];
  bool inUse[MAX_WINDOWS] = {false};

  static inline int16_t getNextIndex() {
    for (int k = 0; k < MAX_WINDOWS; k++) {
      if (!inUse[k]) {
        return k;
      }
    }

    return -1;
  }

  int16_t Allocate(ComponentType t) {
    int16_t nextIndex = getNextIndex();
    if (nextIndex < 0) {
      Serial2.println("Failed to allocate comp: poolIndex exceeds MAX_WINDOWS");
      Serial2.print(  nextIndex);
      Serial2.print(  " >= ");
      Serial2.println(  MAX_WINDOWS);
      return -1;
    }

    pool[nextIndex].type = t;

    switch(pool[nextIndex].type) {
      case BAR:
        pool[nextIndex].bar = new UIBar();
        break;
      case STRING:
        pool[nextIndex].str = new UIString();
        break;
      case TABLE:
        pool[nextIndex].table = new UITable();
        break;
      case BASE:
        pool[nextIndex].base = new UIElement();
        break;
    }

    // Mark it as in use
    inUse[nextIndex] = true;

    return nextIndex;
  }

  void Deallocate(int16_t id) {
    switch(pool[id].type) {
      case BAR:
        break;
      case STRING:
        break;
      case TABLE:
        break;
      case BASE:
        break;
    }

    inUse[id] = false;
  }

  UIElement* GetHandle(int16_t id) {
    switch(pool[id].type) {
      case BAR:
        return pool[id].bar;
        break;
      case STRING:
        return pool[id].str;
        break;
      case TABLE:
        return pool[id].table;
        break;
      case BASE:
        return pool[id].base;
        break;
    }

    return nullptr;
  }

  void PrintInUse() {
    for (int k = 0; k < MAX_WINDOWS; k++) {
      if (inUse[k]) {
        Serial2.print(k);
        Serial2.print(" : ");
        Serial2.println(inUse[k]);
      }
    }
  }
}
