#pragma once
#include <Reflection/VField.h>
#include <any>
#include <functional>
#include <string>
#include <typeinfo>
#include <fmt/core.h>

#include "VProperty.h"

namespace VulcanCore {
    
    class VNumericProperty : public VProperty {

        DECLARE_FIELD(VNumericProperty,VProperty,CastClassFlags_VNumericProperty)

        VNumericProperty(VField* InOwner, const char* InName);
        VNumericProperty(VField* InOwner,VCG::PropertyParamsWithOffset& Prop,EPropertyFlags InPropertyFlags);

        
        virtual bool IsInteger() const;
        virtual bool IsFloatingPoint() const;

        virtual int64 GetSignedIntValue(void* data) const;
        virtual uint64 GetUnsignedIntValue(void* data) const;
        virtual double GetFloatingValue(void* data) const;

        virtual void SetIntValue(void* data, int64 value);
        virtual void SetIntValue(void* data, uint64 value);
        virtual void SetFloatingValue(void* data, double value);    
        
//        virtual void Draw() const override;

       /* virtual std::string ToString(void* container) const override;
        virtual void FromString(void* container, const std::string& value) const override;

        virtual void Serialize(void* obj, std::ostream& out) const override;
        virtual void Deserialize(void* obj, std::istream& in) const override;
*/
        
    };

    template<typename Type>
    class TypeFundamentals {
    public:

        static FORCEINLINE const Type* GetPropertyValuePtr(const void* valuePtr) {
            return (const Type*)valuePtr;
        }

        static FORCEINLINE Type* GetPropertyValuePtr(void* valuePtr) {
            return (Type*) valuePtr;
        }

        static FORCEINLINE const Type& GetPropertyValue(const void* valuePtr) {
            return *GetPropertyValuePtr(valuePtr);
        }

        static FORCEINLINE Type& GetPropertyValue(void* valuePtr) {
            return *GetPropertyValuePtr(valuePtr);
        }

        static FORCEINLINE void SetPropertyValue(void* propertyPtr, const Type& value) {
            GetPropertyValuePtr(propertyPtr) = value;
        }
        
    };
    

    template<typename Type>
    class TNumericProperty : public VNumericProperty {
    public:

        TNumericProperty(VFieldClass* InClass) : VNumericProperty(InClass) {
            
        }
        
        TNumericProperty(VField* InOwner, const char* InName) : VNumericProperty(InOwner,InName) {
            
        }

        TNumericProperty(VField* InOwner,VCG::PropertyParamsWithOffset& Prop,EPropertyFlags InPropertyFlags)
            : VNumericProperty(InOwner,Prop.Name) {
            
        }
        
        bool IsInteger() const override {
            return std::is_integral_v<Type>;
        }

        bool IsFloatingPoint() const override {
            return std::is_floating_point_v<Type>;
        }

        int64 GetSignedIntValue(void* Data) const override {
            Expects(std::is_integral_v<Type> && Data);
            return (int64) TypeFundamentals<Type>::GetPropertyValue(Data);
        }

        uint64 GetUnsignedIntValue(void* Data) const override {
            Expects(std::is_integral_v<Type> && Data);
            return (uint64) TypeFundamentals<Type>::GetPropertyValue(Data);
        }

        double GetFloatingValue(void* Data) const override {
            Expects(std::is_floating_point_v<Type> && Data);
            return (double) TypeFundamentals<Type>::GetPropertyValue(Data);
        }

        void SetIntValue(void* Data, int64 value) override {
            Expects(std::is_integral_v<Type> && Data);
            TypeFundamentals<Type>::SetPropertyValue(Data, value);
        }

        void SetIntValue(void* Data, uint64 value) override {
            Expects(std::is_integral_v<Type> && Data);
            TypeFundamentals<Type>::SetPropertyValue(Data, value);
        }

        void SetFloatingValue(void* data, double value) override {
            Expects(std::is_floating_point_v<Type> && data);
            TypeFundamentals<Type>::SetPropertyValue(data, value);
        }
    };

    class VInt8Property : public TNumericProperty<int8> {

        DECLARE_FIELD(VInt8Property,TNumericProperty<int8>, CastClassFlags_VInt8Property)

        VInt8Property(VField* InOwner, const char* InName);
        VInt8Property(VField* InOwner,VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags);
    };

    
    class VInt16Property : public TNumericProperty<int16> {

        DECLARE_FIELD(VInt16Property,TNumericProperty<int16>, CastClassFlags_VInt16Property)

        VInt16Property(VField* InOwner, const char* InName);
        VInt16Property(VField* InOwner,VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags);
    };

    
    class VIntProperty : public TNumericProperty<int32> {
        
        DECLARE_FIELD(VIntProperty,TNumericProperty<int32>, CastClassFlags_VIntProperty)

        VIntProperty(VField* InOwner, const char* InName);
        VIntProperty(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags);
    };
    
    class VInt64Property : public TNumericProperty<int64> {

        DECLARE_FIELD(VInt64Property,TNumericProperty<int64>, CastClassFlags_VInt64Property)

        VInt64Property(VField* InOwner, const char* InName);
        VInt64Property(VField* InOwner, VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags);
    };

    
    class VUInt8Property : public TNumericProperty<uint8> {

        DECLARE_FIELD(VUInt8Property,TNumericProperty<uint8>, CastClassFlags_VUInt8Property)

        VUInt8Property(VField* InOwner, const char* InName);
        VUInt8Property(VField* InOwner,VCG::PropertyParamsWithOffset& Prop,EPropertyFlags InPropertyFlags);
    };
    
    class VUInt16Property : public TNumericProperty<uint16> {

        DECLARE_FIELD(VUInt16Property,TNumericProperty<uint16>,CastClassFlags_VUInt16Property)

        VUInt16Property(VField* InOwner, const char* InName);
        VUInt16Property(VField* InOwner,VCG::PropertyParamsWithOffset& Prop,EPropertyFlags InPropertyFlags);
    };
    
    class VUIntProperty : public TNumericProperty<uint32> {

        DECLARE_FIELD(VUIntProperty,TNumericProperty<uint32>, CastClassFlags_VUIntProperty)

        VUIntProperty(VField* InOwner, const char* InName);
        VUIntProperty(VField* InOwner,VCG::PropertyParamsWithOffset& Prop,EPropertyFlags InPropertyFlags);
    };
    
    class VUInt64Property : public TNumericProperty<uint64> {

        DECLARE_FIELD(VUInt64Property,TNumericProperty<uint64>, CastClassFlags_VUInt64Property)

        VUInt64Property(VField* InOwner, const char* InName);
        VUInt64Property(VField* InOwner,VCG::PropertyParamsWithOffset& Prop,EPropertyFlags InPropertyFlags);
    };

    class VFloatProperty : public TNumericProperty<float> {

        DECLARE_FIELD(VFloatProperty,TNumericProperty<float>, CastClassFlags_VFloatProperty)

        VFloatProperty(VField* InOwner, const char* InName);
        VFloatProperty(VField* InOwner,VCG::PropertyParamsWithOffset& Prop,EPropertyFlags InPropertyFlags);
    };
    
    class VDoubleProperty : public TNumericProperty<double> {

        DECLARE_FIELD(VDoubleProperty,TNumericProperty<double>, CastClassFlags_VDoubleProperty)

        VDoubleProperty(VField* InOwner, const char* InName);
        VDoubleProperty(VField* InOwner,VCG::PropertyParamsWithOffset& Prop,EPropertyFlags InPropertyFlags);
    };
    
}
