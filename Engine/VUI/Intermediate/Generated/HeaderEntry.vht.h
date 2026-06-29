//AUTO GENERATED. EDIT AT YOUR OWN RISK.

#pragma once
#include <typeindex>
#include <Reflection/VClass.h>
#include <Reflection/VEnum.h>

namespace VulcanCore { class ObjectManager; } 

struct VC_Construct_VClass_HeaderEntry_Statics; 
::VulcanCore::VClass* VC_Construct_VClass_HeaderEntry(); 

#undef VCLASS_BODY()
#define VCLASS_BODY() \
friend class ::VulcanCore::ObjectManager; \
template<typename T,typename... Args> \
friend T* ::VulcanCore::NewObject(Args&&... args); \
friend struct VC_Construct_VClass_HeaderEntry_Statics;\
public: \
    static ::VulcanCore::VClass& StaticClass(); \
    virtual ::VulcanCore::VClass& GetClass() const override;
