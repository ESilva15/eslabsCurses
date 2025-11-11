#include "UIDecorations.h"

namespace Curses {
};

UIDecorations::UIDecorations() {}
UIDecorations::UIDecorations(uint16_t bg, uint16_t fg, uint16_t title,
                             uint16_t border, uint8_t titleSize,
                             uint8_t textSize) {}

UIDecorations& UIDecorations::operator=(const UIDecorations& other) {
  this->textSize = other.textSize;
  this->titleSize = other.titleSize;
  this->titleColor = other.titleColor;
  this->borderColor = other.borderColor;
  this->bgColor = other.bgColor;
  this->fgColor = other.fgColor;
  this->hasBorder = other.hasBorder;

  return *this;
}
