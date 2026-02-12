#ifndef __UI_DECORATIONS
#define __UI_DECORATIONS

#include "UIDrawing.h"
#include <cstdint>
#include <stdint.h>

struct UIDecorations {
  uint16_t bgColor = MAIN_BG_COLOR;
  uint16_t fgColor = MAIN_FG_COLOR;
  uint16_t titleColor = MAIN_FG_COLOR;
  uint16_t borderColor = RED;
  uint8_t titleSize = 2;
  uint8_t textSize = 4;
  uint8_t hasBorder = true;

  UIDecorations();
  UIDecorations(uint16_t bg, uint16_t fg, uint16_t title, uint16_t border,
                uint8_t titleSize, uint8_t textSize);
  UIDecorations& operator=(const UIDecorations& other);
};

#endif
