#include "UIComponent.h"
// #include "u8g2.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include "UIDrawing.h"
// #include <U8g2lib.h>
#include <cstdarg>
#include <cstdint>
#include <cstring>

#define DEBUG 1

UIElement::UIElement()
    : display(nullptr), dims(UIDimensions(0, 0, 0, 0)), decor(UIDecorations()) {}

UIElement::UIElement(Arduino_GFX *d, UIDimensions dims, UIDecorations decor,
                     char *title)
    : display(d), dims(dims), decor(decor) {
  strncpy(this->title, title, MAX_TITLE_LEN);
}

int16_t UIElement::getContentAreaX0() {
  if (this->decor.hasBorder) {
    return this->dims.x + DEFAULT_BORDER_THICKNESS + DEFAULT_MARGIN;
  }

  return this->dims.x;
}

int16_t UIElement::getContentAreaY0() {
  if (this->decor.hasBorder) {
    return this->dims.y + this->getTitleAreaHeight() +
           DEFAULT_TITLE_CONTENT_SPACING;
  }

  return this->dims.y;
}

uint16_t UIElement::getContentAreaHeight() {
  return this->dims.height - (DEFAULT_MARGIN * 2) - DEFAULT_BORDER_THICKNESS -
         this->getTitleAreaHeight();
}

uint16_t UIElement::getContentAreaWidth() {
  return this->dims.width - ((DEFAULT_BORDER_THICKNESS + DEFAULT_MARGIN) * 2);
}

int16_t UIElement::getTitleAreaX0() {
  return this->dims.x + DEFAULT_BORDER_THICKNESS + DEFAULT_MARGIN;
}

int16_t UIElement::getTitleAreaY0() { return this->dims.y; }

uint16_t UIElement::getTitleAreaHeight() {
  int16_t x = 0, y = 0;
  uint16_t w = 0, h = 0;

  this->display->setTextSize(this->decor.titleSize);
  this->display->getTextBounds((const char *)this->title, 0, 0, &x, &y, &w, &h);

  return h;
}

uint16_t UIElement::getTitleAreaWidth() {
  int16_t x = 0, y = 0;
  uint16_t w = 0, h = 0;

  this->display->setTextSize(this->decor.titleSize);
  this->display->getTextBounds((const char *)this->title, 0, 0, &x, &y, &w, &h);

  return w;
}

void UIElement::SetTitle(char* format, ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(this->title, MAX_TITLE_LEN, format, args);
  va_end(args);
}

void UIElement::SetUIDecorations(UIDecorations decor) {
  this->decor = decor;
}

void UIElement::SetUIDimensions(UIDimensions dims) {
  this->dims = dims;
}

void UIElement::SetDisplay(Arduino_GFX *d) {
  this->display = d;
}

void UIElement::replaceString(char *oldVal, char *newVal) {
  size_t newValLen = strlen(newVal);
  size_t oldValLen = strlen(oldVal);

  // It crashs somewhere around here
  int16_t x0 = this->getContentAreaX0();
  int16_t y0 = this->getContentAreaY0(); // <- Crashes here
  // Before here

  this->display->setTextSize(this->decor.textSize);

  // If the new value is shorter, delete the extra in advance
  if (oldValLen > newValLen) {
    // If the old value is longer than the new value, we have to delete the
    // extra of the old value, which is whatever starts at the new value len
    for (std::size_t start = newValLen; start < oldValLen; start++) {
      this->display->setCursor(x0 + start * (CHR_WIDTH(this->decor.textSize)),
                               y0);
      this->display->setTextColor(this->decor.bgColor);
      this->display->print(oldVal[start]);
    }
  }

  for (std::size_t k = 0; k < newValLen; k++) {
    if (k <= oldValLen) {
      if (oldVal[k] != newVal[k]) {
        this->display->setCursor(x0 + k * (CHR_WIDTH(this->decor.textSize)),
                                 y0 + 0);
        this->display->setTextColor(this->decor.bgColor);
        this->display->print(oldVal[k]);
      }
    }

    this->display->setCursor(x0 + k * (CHR_WIDTH(this->decor.textSize)),
                             y0 + 0);
    this->display->setTextColor(this->decor.fgColor);
    this->display->print(newVal[k]);
  }
}

bool UIElement::AddChild() {
  if (childrenCount >= MAX_CHILDREN) {
    Serial2.println("Failed to add child: childrenCount exceeds MAX_CHILDREN");
    Serial2.print(  childrenCount);
    Serial2.print(  " >= ");
    Serial2.print(  MAX_CHILDREN);
    return false;
  }

  int16_t newElem = WindowPool::Allocate();
  if (newElem < 0) {
    Serial2.println("Failed to allocate new component");
    return false;
  }

  this->children[this->curChildIndex] = newElem;
  this->childrenCount++;
  this->curChildIndex++;

  return true;
}

UIElement* UIElement::GetChild(int16_t childID) {
  return WindowPool::GetHandle(childID);
}

std::uint8_t UIElement::ChildrenCount() {
  return this->childrenCount;
}

namespace WindowPool {
  UIElement pool[MAX_WINDOWS];
  bool inUse[MAX_WINDOWS] = {false};

  static inline int16_t getNextIndex() {
    for (int k = 0; k < MAX_WINDOWS; k++) {
      if (!inUse[k]) {
        return k;
      }
    }

    return -1;
  }

  int16_t Allocate() {
    int16_t nextIndex = getNextIndex();
    if (nextIndex < 0) {
      Serial2.println("Failed to allocate comp: poolIndex exceeds MAX_WINDOWS");
      Serial2.print(  nextIndex);
      Serial2.print(  " >= ");
      Serial2.println(  MAX_WINDOWS);
      return -1;
    }

    // Mark it as in use
    inUse[nextIndex] = true;

    return nextIndex;
  }

  void Deallocate(int16_t id) {
    pool[id].SetTitle((char*)"");
    pool[id].SetUIDimensions(UIDimensions(0, 0, 0, 0));
    pool[id].SetUIDecorations(UIDecorations());

    inUse[id] = false;
  }

  UIElement* GetHandle(int16_t id) {
    return &pool[id];
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

