#pragma once
#include <optional>
#include <queue>
#include <string>
#include <vector>

#include "VUIElement.h"
#include "ThemeAsset.h"
#include "UIRequest.h"
#include "Vector2.h"

namespace VUI {
    class UIRequests {
    public:
        static UIRequests& Instance() {
            static UIRequests instance;
            return instance;
        }

        void PushRequest(UIRequest InRequest) {
            Requests.push(std::move(InRequest));
        }

        const UIRequest* Current() const {
            if (Requests.empty()) {
                return nullptr;
            }

            return &Requests.front();
        }

        void PopRequest() {
            if (!Requests.empty()) {
                Requests.pop();
            }
        }

    private:
        std::queue<UIRequest> Requests;
    };
}
