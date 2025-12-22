#pragma once

#include <fmt/color.h>

#include "LogSystem.h"
#include "TVector.h"
#include "VUIRenderable.h"
#include "Entries/ComboBoolEntry.h"
#include "Entries/ComboEntry.h"

namespace VUI {
    
    constexpr uint8_t LOG_INFO    = 1 << 0;
    constexpr uint8_t LOG_DEBUG    = 1 << 1;
    constexpr uint8_t LOG_WARNING = 1 << 2;
    constexpr uint8_t LOG_ERROR   = 1 << 3;
    
    struct LoggerConfig {
        bool clearOnPlay{false};
        uint8_t loggerFlags{ LOG_INFO | LOG_DEBUG | LOG_WARNING | LOG_ERROR };


        static uint8_t MaskOf(std::string_view name) {
            if (name == "info")    return LOG_INFO;
            if (name == "debug")    return LOG_DEBUG;
            if (name == "warning") return LOG_WARNING;
            if (name == "error")   return LOG_ERROR;
            return 0;
        }

        static uint8_t EnumToMask(VulcanEngine::LogLevel InLevel) {
            switch (InLevel) {
                case VulcanEngine::LogLevel::Info:    return LOG_INFO;
                case VulcanEngine::LogLevel::Debug:    return LOG_DEBUG;
                case VulcanEngine::LogLevel::Warning: return LOG_WARNING;
                case VulcanEngine::LogLevel::Error:   return LOG_ERROR;
                default: return 0;
            }
        }

        std::vector<std::tuple<std::string,bool>> GetFlags() const {
            return {
                {"info",   GetFlag("info")},
                    {"debug",   GetFlag("debug")},
                {"warning", GetFlag("warning")},
                {"error",   GetFlag("error")}
            };
        }

        bool GetFlag(std::string_view name) const {
            uint8_t flagMask = MaskOf(name);
            return flagMask ? (loggerFlags & flagMask) != 0 : false;
        }

        void SetFlag(std::string_view name, bool enabled) {
            uint8_t flagMash = MaskOf(name);
            
            if (!flagMash) return;
            
            if (enabled)
                loggerFlags |=  flagMash;
            else
                loggerFlags &= ~flagMash;
        }
    };

    
    class VUILogger : public VUIRenderable {
    public:
        VUILogger(LoggerConfig& config);
        
        void Render(const VUIElement& e,const UILayout& InParent) override;

    private:
        LoggerConfig Config{};
        std::string Search{};

        void SetSearchText(const std::string& InSearch) { Search = InSearch; }
        const std::string& GetSearchText() const { return Search; }

        VulcanEngine::TVector<std::unique_ptr<VulcanCore::ReflectionBase>>& GetCategories() {
            static VulcanEngine::TVector<std::unique_ptr<VulcanCore::ReflectionBase>> out;
            
            if (out.size() != VulcanEngine::LogCategoryRegistry.GetAll().size()) {
                out.clear();
                out.reserve(VulcanEngine::LogCategoryRegistry.GetAll().size());

                for (auto& category : VulcanEngine::LogCategoryRegistry.GetAll()) {
                    //auto entry = VulcanCore::NewObject<ComboBoolEntry>(category->GetName(),&category->IsEnabled());
                    auto entry = std::make_unique<ComboBoolEntry>(category->GetName(),&category->IsEnabled());
                    out.push_back(std::move(entry));
                }
            }
            
            return out;
        }

        bool FixScroll{true};
        float LastScrollY{-1};
    };
}
