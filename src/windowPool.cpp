#include "windowPool.h"
#include "logger.h"
#include "UIComponent.h"
#include "UIBar.h"
#include "UIString.h"
#include "UIBase.h"
#include "UITable.h"
#include "values.h"
#include "logger.h"

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
      LOG_ERROR(F("Failed to allocate comp: poolIndex exceeds MAX_WINDOWS\r\n"));
      LOG_ERROR(F("    %d >= %d\r\n"), nextIndex, MAX_WINDOWS);
      return -1;
    }

    pool[nextIndex].type = t;

    switch(pool[nextIndex].type) {
      case BAR:
        LOG_DEBUG(F("PRE allocing\r\n"));
        pool[nextIndex].bar = new UIBar();
        LOG_DEBUG(F("POST allocing type: \r\n"), pool[nextIndex].type);
        break;
      case STRING:
        pool[nextIndex].str = new UIString();
        break;
      case TABLE:
        pool[nextIndex].table = new UITable();
        break;
      case BASE:
        pool[nextIndex].base = new UIBase();
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
        delete pool[id].str;
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
        LOG_TRACE(F("Window in use: %d : %d\n"), k, inUse[k]);
      }
    }
  }
}
