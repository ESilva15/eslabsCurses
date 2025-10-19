#ifndef __UI_COMPONENT
#define __UI_COMPONENT

#include "Arduino_GFX.h"
#include "UIDecorations.h"
#include <stdint.h>

enum ComponentType {
  STRING,
  TABLE,
};

struct UIDimensions {
  uint16_t x = 0, y = 0;
  uint16_t width = 0, height = 0;

  UIDimensions(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
};

struct UIElement {
  Arduino_GFX *display;
  UIDimensions dims;
  UIDecorations *decor;
  char *title;
  uint64_t lastUpdate = 0;
  uint16_t refreshRate = 0;
  ComponentType type;

  UIElement(Arduino_GFX *d, UIDimensions dims, UIDecorations *decor,
            char *Title);

  // Getters
  int16_t getContentAreaX0();
  int16_t getContentAreaY0();
  uint16_t getContentAreaHeight();
  uint16_t getContentAreaWidth();
  int16_t getTitleAreaX0();
  int16_t getTitleAreaY0();
  uint16_t getTitleAreaHeight();
  uint16_t getTitleAreaWidth();

  // Positioning
  void horizontalCenter(UIElement *reference);
  void verticalCenter(UIElement *reference);
  void placeBelow(UIElement *reference);
  void placeRight(UIElement *reference);
  void placeLeft(UIElement *reference);

  // Drawing
  void drawBox();
  void noBox();
  void replaceString(char *oldVal, char *newVal);
};

#endif
