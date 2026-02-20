#ifndef __UI_BASE__
#define __UI_BASE__

#include "UIComponent.h"

// Representation of single line strings
struct UIBase : UIElement {
  static const std::size_t bufferSize = 64;
  char value[bufferSize];

  UIBase();
  UIBase(Arduino_GFX *d, UIDimensions dims, UIDecorations decor, char *title);
  void Update(const char *value, bool forceRedraw) override;
  void Redraw() override;
};

#endif
