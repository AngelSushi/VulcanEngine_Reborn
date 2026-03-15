#pragma once

#include <CoreAPI/precomp.h>
#include "UIRequest.h"

namespace VUI {
    
    class IRequestRenderer {
    public:
        virtual void Render(const UIRequest& InRequest) = 0;
        virtual ~IRequestRenderer() = default;
    };
}
