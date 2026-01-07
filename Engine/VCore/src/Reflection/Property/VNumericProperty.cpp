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

    
    VNumericProperty::VNumericProperty(const VField* InOwner,Name InName)
        : VProperty(InOwner, InName) {
    }

    VNumericProperty::VNumericProperty(const VField* InOwner,const VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags)
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

    VInt8Property::VInt8Property(const VField* InOwner,Name InName) 
     : TNumericProperty<int8>(InOwner, InName) {
    }

    VInt8Property::VInt8Property(const VField* InOwner,const VCG::Int8PropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<int8>(InOwner, (const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VInt16Property::VInt16Property(const VField* InOwner,Name InName)
        : TNumericProperty<int16>(InOwner, InName) {
    }

    VInt16Property::VInt16Property(const VField* InOwner,const VCG::Int16PropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<int16>(InOwner,(const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VIntProperty::VIntProperty(const VField* InOwner,Name InName)
        : TNumericProperty<int32>(InOwner, InName) {
    }

    VIntProperty::VIntProperty(const VField* InOwner,const VCG::IntPropertyParams& Prop,EPropertyFlags InPropertyFlags)
        : TNumericProperty<int32>(InOwner, (const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VInt64Property::VInt64Property(const VField* InOwner,Name InName)
        : TNumericProperty<int64>(InOwner, InName) {
        
    }

    VInt64Property::VInt64Property(const VField* InOwner,const VCG::Int64PropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<int64>(InOwner, (const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VUInt8Property::VUInt8Property(const VField* InOwner,Name InName) 
     : TNumericProperty<uint8>(InOwner, InName) {
    }

    VUInt8Property::VUInt8Property(const VField* InOwner,const VCG::UInt8PropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<uint8>(InOwner,(const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VUInt16Property::VUInt16Property(const VField* InOwner,Name InName)
        : TNumericProperty<uint16>(InOwner, InName) {
    }

    VUInt16Property::VUInt16Property(const VField* InOwner,const VCG::UInt16PropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<uint16>(InOwner,(const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VUIntProperty::VUIntProperty(const VField* InOwner,Name InName)
        : TNumericProperty<uint32>(InOwner, InName) {
    }

    VUIntProperty::VUIntProperty(const VField* InOwner,const VCG::UIntPropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<uint32>(InOwner,(const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VUInt64Property::VUInt64Property(const VField* InOwner,Name InName)
        : TNumericProperty<uint64>(InOwner, InName) {
        
    }

    VUInt64Property::VUInt64Property(const VField* InOwner,const VCG::UInt64PropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<uint64>(InOwner,(const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VFloatProperty::VFloatProperty(const VField* InOwner,Name InName)
        : TNumericProperty<float>(InOwner, InName) {
    }

    VFloatProperty::VFloatProperty(const VField* InOwner,const VCG::FloatPropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<float>(InOwner,(const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
    }

    VDoubleProperty::VDoubleProperty(const VField* InOwner, Name InName)
        : TNumericProperty<double>(InOwner, InName) {
        
    }

    VDoubleProperty::VDoubleProperty(const VField* InOwner,const VCG::DoublePropertyParams& Prop, EPropertyFlags InPropertyFlags)
        : TNumericProperty<double>(InOwner,(const VCG::PropertyParamsWithOffset&) Prop, InPropertyFlags) {
        
    }


}
