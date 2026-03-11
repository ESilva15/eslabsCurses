#include "UIGenericWindow.h"

UIGenericWindow::UIGenericWindow(
        Arduino_GFX* d, 
        void* data, 
        RenderDelegate r,
        IDataContainer* vp,
        UIDimensions dims,
        UIDecorations decor,
        char* title
        ) 
      : dataPtr(data), renderer(r), data(vp), UIElement(d, dims, decor, title) {}

void UIGenericWindow::Draw(bool forceRedraw) {
  if (this->data->hasChanged() && !forceRedraw) {
    // Check if this logic is correct
    return;
  }

  this->renderer(this->display, this->dims, this->dataPtr);
}
