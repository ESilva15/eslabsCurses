#ifndef __UI_COMPONENT__
#define __UI_COMPONENT__

#include "Arduino_GFX.h"
#include "values.h"
#include "UIDecorations.h"
#include "UIDimensions.h"
#include <cstdint>
#include <stdint.h>

class UIElement {
private:
  uint8_t childrenCount = 0;
  int8_t curChildIndex = -1; // Start at -1, have no children

public:
  Arduino_GFX *display;
  UIDimensions dims;
  UIDecorations decor;
  char title[MAX_TITLE_LEN];
  uint64_t lastUpdate = 0;
  uint16_t refreshRate = 0;
  ComponentType type;

  UIElement();
  UIElement(Arduino_GFX *d, UIDimensions dims, UIDecorations decor,
            char *Title);

  // Children
  int16_t children[MAX_CHILDREN];

  // Children Handling
  bool AddChild(ComponentType t);
  UIElement* GetChild(int16_t childID);
  uint8_t ChildrenCount();

  // Getters
  int16_t getContentAreaX0();
  int16_t getContentAreaY0();
  uint16_t getContentAreaHeight();
  uint16_t getContentAreaWidth();
  int16_t getTitleAreaX0();
  int16_t getTitleAreaY0();
  uint16_t getTitleAreaHeight();
  uint16_t getTitleAreaWidth();

  // Setters
  void SetTitle(char* format, ...);
  void SetUIDecorations(UIDecorations decor);
  void SetUIDimensions(UIDimensions dims);
  void SetDisplay(Arduino_GFX *d);

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
