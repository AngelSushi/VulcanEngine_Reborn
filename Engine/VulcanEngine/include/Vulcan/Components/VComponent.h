#pragma once
#include <Export.h>
#include "Reflection/VMacros.h"
#include "Reflection/VObject.h"
#include <nlohmann/json.hpp>
#include <entt/entity/fwd.hpp>
#include <VComponent.vht.h>


namespace VulcanEngine {

    class Entity;

    struct ComponentType {
        std::string Name;
        std::type_index Type;
        std::function<void(Entity*, const nlohmann::json&)> Creator;
        
        ComponentType(std::string InName, std::type_index InType, std::function<void(Entity*, const nlohmann::json&)> InCreator)
            : Name(std::move(InName)), Type(InType), Creator(InCreator) {}
    };

    VCLASS()
    class VULCAN_ENGINE_API VComponent : public VulcanCore::ReflectionBase {
        
        VCLASS_BODY()
        
    public:
        VComponent() = default;
        VComponent(const VComponent& Component);
        VComponent(VComponent&& Component) noexcept;

        VComponent& operator=(const VComponent& Component) = delete;
        VComponent& operator=(VComponent&& Component) noexcept;

        virtual std::string GetComponentName() { return "##"; }

        virtual void Init() {}
        virtual void LoadComponent(const nlohmann::json& json) = 0;
        virtual void SaveComponent(std::vector<std::uint8_t>& ByteArray) = 0;

        virtual ~VComponent() = default;

    protected:
        bool NodeOpen{};
    };

}
