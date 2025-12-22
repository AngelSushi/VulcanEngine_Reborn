#pragma once

#include "ImportRequestDatas/ImportData.h"

namespace VUI {

    enum UIRequestType {
        ImportAsset
    };

    struct UIRequest {
        UIRequestType RequestType;
        std::variant<std::unique_ptr<ImportData>> Data;
    };
}
