#ifndef __WINDOW_POOL__
#define __WINDOW_POOL__

#include <cstdint>
#include <stdint.h>
#include "values.h"

struct UIElement;
struct UIString;
struct UIBar;
struct UITable;

namespace WindowPool {
  struct WindowEntry {
    ComponentType type;
    union {
      UIElement* base;
      UIString* str;
      UIBar* bar;
      UITable* table;
    };
  };

  extern WindowEntry pool[MAX_WINDOWS];
  extern bool inUse[MAX_WINDOWS];

  int16_t Allocate(ComponentType t);
  // I will finish this later on, still have to figure out how to properly
  // destroy the UIComponent
  void Deallocate(int16_t childID);
  UIElement* GetHandle(int16_t index);
  
  // Debugging
  void PrintInUse();
};

#endif
