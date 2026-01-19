#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/UIValue.h>

// Maybe error with tthis include, circular dependency ? 
#include <Systems/EditorSystem.h>


// Struct used to read data from ui to engine 
struct UIContextValue {
    
    UIValue Get(const std::string& InKey) const {
        if (Has(InKey)) {
            auto it = Values.find(InKey);
            return it->second;
        }

        return UIValue();
    }

    
    void Set(const std::string& InKey, const UIValue& InValue) {
        if (Has(InKey)) {
            VLOG_WARN(EditorUI,"[EditorUI] The value {} already exist in view model.",InKey);
            return;
        }

        Values[InKey] = InValue;
    }

    bool Has(const std::string& InKey) const {
        return Values.find(InKey) != Values.end();
    }
    
    void Remove(const std::string& InKey) {
        Values.erase(InKey);
    }
    
private:
    std::unordered_map<std::string, UIValue> Values;
};