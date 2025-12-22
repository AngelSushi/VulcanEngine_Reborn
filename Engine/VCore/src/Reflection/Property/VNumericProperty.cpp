#include <Reflection/Property/VNumericProperty.h>

namespace VulcanCore {

    IMPLEMENT_FIELD(VNumericProperty)
    IMPLEMENT_FIELD(VInt8Property)
    IMPLEMENT_FIELD(VInt16Property)
    IMPLEMENT_FIELD(VIntProperty)
    IMPLEMENT_FIELD(VInt64Property)
    IMPLEMENT_FIELD(VUInt8Property)
    IMPLEMENT_FIELD(VUInt16Property)
    IMPLEMENT_FIELD(VUIntProperty)
    IMPLEMENT_FIELD(VUInt64Property)
    IMPLEMENT_FIELD(VFloatProperty)
    IMPLEMENT_FIELD(VDoubleProperty)

    
    VNumericProperty::VNumericProperty(VField* InOwner, const char* InName)
        : VProperty(InOwner, InName) {
    }

    VNumericProperty::VNumericProperty(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : VProperty(InOwner, Prop, InPropertyFlags) {
    }

    bool VNumericProperty::IsInteger() const { 
        return true;
    }

    bool VNumericProperty::IsFloatingPoint() const {
        return false;
    }

    int64_t VNumericProperty::GetSignedIntValue(void* instance) const {
        return 0;
    }

    uint64_t VNumericProperty::GetUnsignedIntValue(void* instance) const {
        return 0;
    }

    double VNumericProperty::GetFloatingValue(void* instance) const {
        return 0.0;
    }

    void VNumericProperty::SetIntValue(void* instance, int64_t value) {
        Expects(0);
    }

    void VNumericProperty::SetIntValue(void* instance, uint64_t value) {
        Expects(0);
    }

    void VNumericProperty::SetFloatingValue(void* instance, double value) {
        Expects(0);
    }

    VInt8Property::VInt8Property(VField* InOwner, const char* InName) 
     : TNumericProperty<int8>(InOwner, InName) {
    }

    VInt8Property::VInt8Property(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<int8>(InOwner, Prop, InPropertyFlags) {
    }

    VInt16Property::VInt16Property(VField* InOwner, const char* InName)
        : TNumericProperty<int16>(InOwner, InName) {
    }

    VInt16Property::VInt16Property(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<int16>(InOwner, Prop, InPropertyFlags) {
    }

    VIntProperty::VIntProperty(VField* InOwner, const char* InName)
        : TNumericProperty<int32>(InOwner, InName) {
    }

    VIntProperty::VIntProperty(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<int32>(InOwner, Prop, InPropertyFlags) {
    }

    VInt64Property::VInt64Property(VField* InOwner, const char* InName)
        : TNumericProperty<int64>(InOwner, InName) {
        
    }

    VInt64Property::VInt64Property(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<int64>(InOwner, Prop, InPropertyFlags) {
    }

    VUInt8Property::VUInt8Property(VField* InOwner, const char* InName) 
     : TNumericProperty<uint8>(InOwner, InName) {
    }

    VUInt8Property::VUInt8Property(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<uint8>(InOwner, Prop, InPropertyFlags) {
    }

    VUInt16Property::VUInt16Property(VField* InOwner, const char* InName)
        : TNumericProperty<uint16>(InOwner, InName) {
    }

    VUInt16Property::VUInt16Property(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<uint16>(InOwner, Prop, InPropertyFlags) {
    }

    VUIntProperty::VUIntProperty(VField* InOwner, const char* InName)
        : TNumericProperty<uint32>(InOwner, InName) {
    }

    VUIntProperty::VUIntProperty(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<uint32>(InOwner, Prop, InPropertyFlags) {
    }

    VUInt64Property::VUInt64Property(VField* InOwner, const char* InName)
        : TNumericProperty<uint64>(InOwner, InName) {
        
    }

    VUInt64Property::VUInt64Property(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<uint64>(InOwner, Prop, InPropertyFlags) {
    }

    VFloatProperty::VFloatProperty(VField* InOwner, const char* InName)
        : TNumericProperty<float>(InOwner, InName) {
    }

    VFloatProperty::VFloatProperty(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<float>(InOwner, Prop, InPropertyFlags) {
    }

    VDoubleProperty::VDoubleProperty(VField* InOwner, const char* InName)
        : TNumericProperty<double>(InOwner, InName) {
        
    }

    VDoubleProperty::VDoubleProperty(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<double>(InOwner, Prop, InPropertyFlags) {
        
    }


}
