#include <Reflection/Property/VProperty.h>


namespace VulcanCore {

    IMPLEMENT_FIELD(VProperty)


    VProperty::VProperty(VField* InOwner, const char* InName)
        : Super(InOwner,InName),
        ElementCount(1),
        TypeSize(0),
        PropertyFlags(PropertyFlags_None),
        Offset(0) {
    }

    VProperty::VProperty(VField* InOwner, VCG::PropertyParamsWithOffset Prop, EPropertyFlags InPropertyFlags)
        : Super(InOwner,Prop.Name),
        ElementCount(1),
        TypeSize(0),
        PropertyFlags(PropertyFlags_None),
        Offset(Prop.Offset) {
    }

    VProperty::VProperty(VField* InOwner, VCG::PropertyParamsWithoutOffset Prop, EPropertyFlags InPropertyFlags) 
        : Super(InOwner,Prop.Name),
        ElementCount(1),
        TypeSize(0),
        PropertyFlags(PropertyFlags_None),
        Offset(0) {
    }

    

    void VProperty::InitializeValueInternal(void* dst) const {
        Expects(0);
    }

    void VProperty::CopyValueInternal(void* dst,const void* src, int32 count) const {
        Expects(0);
    }
}
