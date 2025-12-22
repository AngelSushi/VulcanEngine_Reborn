#pragma once
#include <string>
#include <vector>
#include <any>

#include "Entry.h"
#include <TreeEntry.vht.h>

namespace VUI {
    
    VCLASS()
    class TreeEntry : public Entry {

        VCLASS_BODY()
    public:
        
        std::string EntryName{};
        VulcanEngine::TVector<TreeEntry> Children{};
        std::any Payload; // Use to point the real asset if needed (path,asset ptr,component ref...)
        bool IsDirectory{};
        bool IsSelected{};
        bool IsDirty{};
        TreeEntry* Parent{nullptr};

        std::function<void(TreeEntry*,bool)> OnSelectedChanged;

        void SetSelected(bool InSelected) {
            IsSelected = InSelected;
            if (OnSelectedChanged) {
                OnSelectedChanged(this,IsSelected);
            }
        }

        TreeEntry& Root() {
            TreeEntry* cur = this;
            while (cur->Parent)
                cur = cur->Parent;

            return *cur;
        }


    };
}
