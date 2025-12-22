#pragma once
#include <Export.h>

namespace VulcanEngine {
    class VULCAN_ENGINE_API VSystem {
    public:
        VSystem();
        VSystem(bool IsActive, bool IsEditorSystem);
        VSystem(const VSystem&) = delete;
        VSystem(VSystem&&) noexcept;

        VSystem& operator=(const VSystem&) = delete;
        VSystem& operator=(VSystem&&) noexcept;

        virtual ~VSystem();

        virtual void InitSystem() = 0;
        virtual void StartSystem();
        virtual void Iterate(float DeltaTime);
        virtual void Shutdown();

        virtual void OnPreFrame() {}
        virtual void OnPostFrame() {}

        bool IsActive() const { return _IsActive; }
        bool IsEditorSystem() const { return _IsEditorSystem; }
        void SetActive(bool IsActive);

    protected:
        bool _IsActive;
        bool _LastActive;
        bool _IsEditorSystem;
    };
}