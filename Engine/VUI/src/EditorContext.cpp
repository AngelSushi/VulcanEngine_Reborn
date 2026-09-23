#include <EditorContext.h>

#include "IRegistry.h"
#include "Components/ComponentRegistry.h"
#include <Reflection/VObject.h>

#include "Game.h"
#include "TVector.h"
#include "VCast.h"
#include "World.h"


using namespace VulcanCore;

EditorContext::EditorContext() {
   /* VulcanEngine::BindingRegistry.Register(Binding::Register("Editor::HasEntitySelected", this, &EditorContext::HasEntitySelected));
    VulcanEngine::BindingRegistry.Register(Binding::Register("Editor::ListComponents", HeadersEntry));
    VulcanEngine::BindingRegistry.Register(Binding::Register("Editor::GetAvailableComponents", this, &EditorContext::GetAvailableComponents));
    VulcanEngine::BindingRegistry.Register(VUI::Binding::Register("Editor::MarkComponentAdd",this,&EditorContext::MarkComponentAdd));
	VulcanEngine::BindingRegistry.Register(Binding::Register("Editor::AddComponent", this, &EditorContext::AddComponent));
*/
    Game::GetFrameBeginEvent().Register(this, &EditorContext::OnPreFrame);
}

void EditorContext::OnPreFrame() {
    if (TreeDirty) {
        BuildTree();
        TreeDirty = false;
    }
}


TVector<std::unique_ptr<ReflectionBase>>&  EditorContext::GetAvailableComponents() {
    static TVector<std::unique_ptr<ReflectionBase>> AvailableComponents;
    
    if (SelectedEntities.size() == 1) {
        auto& entity = *SelectedEntities.begin();
        auto availableComps = World::GetWorld().GetAvailableComponentsFor(entity);

        if (availableComps.size() != AvailableComponents.size()) {
            AvailableComponents.clear();
            AvailableComponents.reserve(availableComps.size());

            for (auto& compStr : availableComps) {
                /*auto entry = std::make_unique<ComboEntry>();
                entry->EntryName = compStr;
                AvailableComponents.push_back(std::move(entry));
*/
            }
        }
    }

    return AvailableComponents;
}

void EditorContext::MarkComponentAdd(std::any Value) {
    if (Value.type() == typeid(std::string)) {
        MarkAdd = ComponentRegistry::Instance().Find(std::any_cast<std::string>(Value));
    }
}

void EditorContext::AddComponent() {
    if (SelectedEntities.size() == 1 && MarkAdd) {
        fmt::print("Adding component lol\n");
        MarkAdd->Creator(SelectedEntities[0], nlohmann::json{});
       // BuildTree();
        TreeDirty = true;
    }
}


void EditorContext::BuildTree() {
    if (SelectedEntities.size() == 1) {
        auto& Ent = SelectedEntities[0];

        auto& registry = World::GetWorld().GetCurrentScene()->GetRegistry();

        for (auto&& entity : registry.storage()) {
            const auto& storage = entity.second;

            if (storage.contains(Ent->GetNative())) {
                if (auto* comp = static_cast<VComponent*>(const_cast<void*>(storage.value(Ent->GetNative())))) {
                    //HeaderEntry Entry{};
            
                    /*Entry.HeaderName = comp->GetClass().GetName();

                    for (auto& prop : comp->GetClass().GetProperties()) {
                        Entry.Properties[prop.get()] = comp;
                    }*/

                    //HeadersEntry.push_back(std::move(Entry));
                }
            }
        }
    }
}

