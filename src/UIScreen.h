#ifndef __UI_SCREEN__
#define __UI_SCREEN__

#include "UIComponent.h"
#include "UIDecorations.h"
#include "UIDimensions.h"

namespace Curses {
// Entrypoint for our UI. We will have a single screen and this screen can
// have some windows and whatnot
class Screen {
public:
  UIDimensions dims;
  UIDecorations decor;
  Arduino_GFX *display;

  int16_t mainWindowID;
  Screen(Arduino_GFX *d, UIDimensions dims, UIDecorations decor);
};
}; // namespace Curses

#endif
