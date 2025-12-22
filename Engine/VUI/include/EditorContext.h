#pragma once
#include <string>
#include <vector>
#include <any>
#include <set>

#include <Reflection/ReflectionBase.h>
#include <Entries/TreeEntry.h>
#include <Entries/HeaderEntry.h>

#include "Entity.h"
#include "Reflection/VMacros.h"
#include "TVector.h"

#include <EditorContext.vht.h>



namespace VUI {

    VCLASS()
    class EditorContext : public VulcanCore::ReflectionBase {

        VCLASS_BODY()

    public:

        VFUNCTION()
        static VUI::EditorContext& Instance() {
            static EditorContext instance;
            return instance;
        }

        bool HasEntitySelected() {
            return !SelectedEntities.empty();
        }

        void AddSelectedEntity(TreeEntry* Node);
        void RemoveSelectedEntity(TreeEntry* Node);

        VulcanEngine::TVector<std::unique_ptr<ReflectionBase>>&  GetAvailableComponents();

        void MarkComponentAdd(std::any Value);
        void AddComponent();
    private:
        EditorContext();

        void OnPreFrame();
        void BuildTree();

        bool TreeDirty{};
        
        VulcanEngine::TVector<VulcanEngine::Entity*> SelectedEntities;
        VulcanEngine::TVector<HeaderEntry> HeadersEntry;
        VulcanEngine::ComponentType* MarkAdd;
    };
}
