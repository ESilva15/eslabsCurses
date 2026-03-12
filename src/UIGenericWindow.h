#ifndef __UI__GENERIC_WINDOW__
#define __UI__GENERIC_WINDOW__

class UIElement; // Forward declaration
struct UIDimensions;
class IDataContainer;

#include "UIComponent.h"
#include "UIDecorations.h"
#include "UIDimensions.h"
#include "dataContainer.h"
#include "renderers.h"
#include "Arduino_GFX.h"


// NOTE: at this point I can just use UIElement for everything and not have
// this I reckon


class UIGenericWindow : public UIElement {
  private:
    IDataContainer* dc;

  public:
    RenderDelegate renderer;

    UIGenericWindow(Arduino_GFX* d, RenderDelegate r, IDataContainer* dc,
                    UIDimensions dims, UIDecorations decor, char* title);

    void SetDataContainer(IDataContainer* container);
    void Draw(bool forceRedraw);
    void Update(const char *data, bool forceRedraw) override {};
    void Redraw() override {};
};

#endif
