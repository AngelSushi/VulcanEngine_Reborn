#include <CoreAPI/Globals.h>

#include "Reflection/Property/VNumericProperty.h"

namespace VCG {

    template<typename Type,typename ParamsType>
    Type* NewProperty(VulcanCore::VField* Out, const PropertyBaseParams& Params) {
        const ParamsType& Prop = (const ParamsType&)Params;
        Type* NewProp = new Type(Out,Prop);

        return NewProp;
    }
    
    void ConstructProperty(VulcanCore::VField* Out,PropertyBaseParams& Params) {
        using namespace VulcanCore;
        
        VProperty* NewProp = nullptr;
        
        switch (Params.PropertyType) {
            case PropertyTypeFlags_None:    
                return;

            case PropertyTypeFlags_Int8: 
                NewProp = NewProperty<VInt8Property,Int8PropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_Int16:
                NewProp = NewProperty<VInt16Property,Int16PropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_Int:
                NewProp = NewProperty<VIntProperty,IntPropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_Int64:
                NewProp = NewProperty<VInt64Property,Int64PropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_Float:
                NewProp = NewProperty<VFloatProperty,FloatPropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_Double:
                NewProp = NewProperty<VDoubleProperty,DoublePropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_UInt8:
                NewProp = NewProperty<VUInt8Property,UInt8PropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_UInt16:
                NewProp = NewProperty<VUInt16Property,UInt16PropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_UInt:
                NewProp = NewProperty<VUIntProperty,UIntPropertyParams>(Out,Params);
                break;

            case PropertyTypeFlags_UInt64:
                NewProp = NewProperty<VUInt64Property,UInt64PropertyParams>(Out,Params);
                break;
        }

        NewProp->SetElementCount(Params.ElementCount);
    }
    
    void ConstructProperties(VulcanCore::VField* Out,PropertyBaseParams* PropertyParams, int32 PropertiesSize) {
        for (size_t index = 0; index < PropertiesSize; ++index) {
            ConstructProperty(Out,PropertyParams[index]);
        }    
    }
    
    void ConstructClass(VulcanCore::VClass*& OutClass, const ClassParams& Params) {

        OutClass = Params.ClassRegisterFunc();

        ConstructProperties(OutClass,Params.PropertyParams,Params.NumProperties);
    }
}
