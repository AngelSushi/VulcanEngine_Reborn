#pragma once
#include <string>
#include <vector>
#include <any>
#include <set>

#include <Reflection/ReflectionBase.h>

#include "Entity.h"
#include "Reflection/VMacros.h"
#include "TVector.h"

#include <EditorContext.vht.h>



VCLASS()
class VUI_API EditorContext : public VulcanCore::ReflectionBase {

    VCLASS_BODY()

public:

    VFUNCTION()
    static EditorContext& Instance() {
        static EditorContext instance;
        return instance;
    }

    bool HasEntitySelected() {
        return !SelectedEntities.empty();
    }

    TVector<std::unique_ptr<ReflectionBase>>&  GetAvailableComponents();

    void MarkComponentAdd(std::any Value);
    void AddComponent();
private:
    EditorContext();

    void OnPreFrame();
    void BuildTree();

    bool TreeDirty{};
    
    TVector<Entity*> SelectedEntities;
    ComponentType* MarkAdd;
};

