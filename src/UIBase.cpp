#include "UIBase.h"
#include "HardwareSerial.h"
#include "UIComponent.h"
#include <Arduino_GFX.h>

UIBase::UIBase() : UIElement(nullptr, {0, 0, 0, 0}, UIDecorations(), (char *)"") {
  this->type = STRING;
  memset(this->value, 0, this->bufferSize);
}

UIBase::UIBase(Arduino_GFX *d, UIDimensions dims, UIDecorations decor,
                   char *title)
    : UIElement(d, dims, decor, title) {
  this->type = BASE;
  memset(this->value, 0, this->bufferSize);
}

void UIBase::Update(const char* data, bool forceRedraw) {}
void UIBase::Redraw() {}
