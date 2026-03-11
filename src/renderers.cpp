#include "Arduino_GFX.h"
#include "UIComponent.h"
#include "UIDimensions.h"
#include "dataContainer.h"
#include "stdlib.h"

void RenderString(UIElement* caller, UIDimensions dims, void* dataContainer) {
  StrContainer* container = (StrContainer*)dataContainer;

  char* oldVal = (char*)container->GetPrevValue();
  char* newVal = (char*)container->GetCurrentValue();

  size_t newValLen = strlen(newVal);
  size_t oldValLen = strlen(oldVal);

  // It crashs somewhere around here
  int16_t x0 = caller->getContentAreaX0();
  int16_t y0 = caller->getContentAreaY0();
  // Before here

  caller->display->setTextSize(caller->decor.textSize);

  // If the new value is shorter, delete the extra in advance
  if (oldValLen > newValLen) {
    // If the old value is longer than the new value, we have to delete the
    // extra of the old value, which is whatever starts at the new value len
    for (std::size_t start = newValLen; start < oldValLen; start++) {
      caller->display->setCursor(x0 + start * (CHR_WIDTH(caller->decor.textSize)),
                               y0);
      caller->display->setTextColor(caller->decor.bgColor);
      caller->display->print(oldVal[start]);
    }
  }

  for (std::size_t k = 0; k < newValLen; k++) {
    if (k <= oldValLen) {
      if (oldVal[k] != newVal[k]) {
        caller->display->setCursor(x0 + k * (CHR_WIDTH(caller->decor.textSize)),
                                 y0 + 0);
        caller->display->setTextColor(caller->decor.bgColor);
        caller->display->print(oldVal[k]);
      }
    }

    caller->display->setCursor(x0 + k * (CHR_WIDTH(caller->decor.textSize)),
                             y0 + 0);
    caller->display->setTextColor(caller->decor.fgColor);
    caller->display->print(newVal[k]);
  }
}

// template <typename T>
// void RenderInt(Arduino_GFX* d, UIDimensions dims, void* data) {
//   static char buf[21];
//
//   T val = *(T*)data;
//
//   ltoa((long)val, buf, 10);
//
//   d->setCursor(dims.x, dims.y);
//   d->print(buf);
// }
