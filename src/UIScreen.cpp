#include "UIScreen.h"
#include "UIComponent.h"
#include "UIDecorations.h"
#include "UIDimensions.h"

Curses::Screen::Screen(Arduino_GFX *d, UIDimensions dims, 
                       UIDecorations decor) 
  : display(d), dims(dims), decor(decor) {
}

void Curses::Screen::Setup(const char* title) {
  // This should always return the first available component
  this->mainWindowID = WindowPool::Allocate();
  if (this->mainWindowID != 0) {
    // Something wrong happened
    Serial2.print("Unexpected ID for main window: ");
    Serial2.println(this->mainWindowID);
    for (;;) {
      delay(1000);
      Serial2.println("Program interrupted due to setup failure");
    }
  }

  this->mainWindowHandle = WindowPool::GetHandle(this->mainWindowID);
  this->mainWindowHandle->SetDisplay(this->display);
  this->mainWindowHandle->SetTitle((char*)"%s [%2d]", title, this->mainWindowID);
  this->mainWindowHandle->SetUIDecorations(this->decor);
  this->mainWindowHandle->SetUIDimensions(this->dims);
}
