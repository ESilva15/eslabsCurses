#include "UIGenericWindow.h"
#include "dataContainer.h"

UIGenericWindow::UIGenericWindow(
        Arduino_GFX* d, 
        RenderDelegate r,
        IDataContainer* dc,
        UIDimensions dims,
        UIDecorations decor,
        char* title
        ) 
      : renderer(r), dc(dc), UIElement(d, dims, decor, title) {}

void UIGenericWindow::Draw(bool forceRedraw) {
  if (!this->dc->hasChanged(64) && !forceRedraw) {
    return;
  }

  this->renderer(this, this->dims, this->dc);
}

void UIGenericWindow::SetDataContainer(IDataContainer* container) {
  this->dc = container;
}
