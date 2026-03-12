#ifndef __UI__RENDERERS__
#define __UI__RENDERERS__

#include "UIDimensions.h"
#include "UIComponent.h"
#include "dataContainer.h"

typedef void (*RenderDelegate)(UIElement* caller, UIDimensions dims, IDataContainer* dc);

void RenderString(UIElement* caller, UIDimensions dims, IDataContainer* data);

#endif
