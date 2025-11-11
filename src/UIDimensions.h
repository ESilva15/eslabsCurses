#ifndef __UI_DIMENSIONS__
#define __UI_DIMENSIONS__

#include <stdint.h>

struct UIDimensions {
  uint16_t x = 0, y = 0;
  uint16_t width = 0, height = 0;

  UIDimensions(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  UIDimensions& operator=(const UIDimensions& other);
};

#endif
