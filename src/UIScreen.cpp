#include "UIScreen.h"
#include "UIDecorations.h"
#include "UIDimensions.h"

Curses::Screen::Screen(Arduino_GFX *d, UIDimensions dims, UIDecorations decor) 
  : display(d), dims(dims), decor(decor) {};
