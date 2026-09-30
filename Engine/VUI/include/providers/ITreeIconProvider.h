#pragma once
#include <CoreAPI/VTexture.h>



namespace VUI {
    struct TreeEntry;
    
    class ITreeIconProvider {

    public:
        virtual std::string GetName() const = 0;
        virtual std::shared_ptr<VTexture> GetIconForEntry(const TreeEntry& InEntry) const = 0;
        virtual ~ITreeIconProvider() = default;
    };
}
