#ifndef __UI__GENERIC_WINDOW__
#define __UI__GENERIC_WINDOW__

#include "UIComponent.h"
#include "UIDecorations.h"
#include "UIDimensions.h"
#include "dataContainer.h"
#include "Arduino_GFX.h"

typedef void (*RenderDelegate)(UIElement* caller, UIDimensions dims);

class UIGenericWindow : public UIElement {
  private:
    IDataContainer* data;

  public:
    RenderDelegate renderer;

    UIGenericWindow(Arduino_GFX* d, void* data, RenderDelegate r, IDataContainer* vp,
                    UIDimensions dims, UIDecorations decor, char* title);

    void Draw(bool forceRedraw);
    void Update(const char *data, bool forceRedraw) override;
    void Redraw() override;
};

#endif
