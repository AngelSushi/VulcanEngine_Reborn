#include <EditorUI/Core/Components/Navbar.h>

#include "EditorUI/Core/UINodeResolver.h"
#include "EditorUI/Core/Components/Button.h"
#include "IO/FileManager.h"
#include "Systems/EditorSystem.h"

void Navbar::Layout() {
    UIWidget::Layout();
    
    for (size_t i = 0; i < GetChildrenCount(); ++i) {
        UIWidget* Child = GetChildren()[i].get();

        if (Child && i >= 1) {
            UIWidget* PrevChild = GetChildren()[i - 1].get();
            if (PrevChild) {
                // To modify in function of navbar direction
                VMath::Vector2f NewPosition = PrevChild->GetPosition() + VMath::Vector2f(PrevChild->GetSize().x, 0.f);
                Child->SetPosition(NewPosition);
            }
        }
    }
}

