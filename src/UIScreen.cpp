#include "UIScreen.h"
#include "UIComponent.h"
#include "UIDecorations.h"
#include "UIDimensions.h"

Curses::Screen::Screen(Arduino_GFX *d, UIDimensions dims, UIDecorations decor) 
  : display(d), dims(dims), decor(decor) {
  // This should always return the first available component
  this->mainWindowID = WindowPool::Allocate();
  if (this->mainWindowID != 0) {
    // Something wrong happened
    Serial2.print("Unexpected ID for main window: ");
    Serial2.println(this->mainWindowID);
  }
};
