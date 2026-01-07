#pragma once

#include <CoreAPI/Globals.h>
#include <Reflection/VField.h>

#include <Enums.h>
#include <gsl/gsl>

#include "Reflection/VMacros.h"


namespace VulcanCore {
    class ReflectionBase;
    
    class VProperty : public VField {

    public:
        DECLARE_FIELD(VProperty,VField,CastClassFlags_VProperty)
        
        // To create static class (and not instance)
        VProperty(const VField* InOwner,Name InName);

        // To  create instances 
        VProperty(const VField* InOwner,const VCG::PropertyParamsWithOffset& Prop, EPropertyFlags InPropertyFlags = PropertyFlags_None);
        VProperty(const VField* InOwner,const VCG::PropertyParamsWithoutOffset& Prop, EPropertyFlags InPropertyFlags = PropertyFlags_None);
        
        virtual ~VProperty() = default;

        void SetElementCount(int32 InElementCount) {
            ElementCount = InElementCount;
        }
        
        int32 GetElementCount() const {
            return ElementCount;
        }

        int32 GetTypeSize() const {
            return TypeSize;
        }

        template<typename Type>
        FORCEINLINE Type* GetTypedPropertyPtr(void* containerPtr,int32 arrayIndex = 0) const {
            return (Type*) GetPropertyPtrInternal(containerPtr,arrayIndex);
        }

        template<typename Type>
        FORCEINLINE Type* GetTypedPropertyPtr(const void* containerPtr,int32 arrayIndex = 0) const {
            return (Type*) GetPropertyPtrInternal((void*)containerPtr,arrayIndex);
        }
        
        // Initialize the value at the given address to default without container (e.g., functions parameters, local variables)
        FORCEINLINE void InitializeValue(void* dst) const {
            if (PropertyFlags & PropertyFlags_ZeroConstructor) {
                // memset initialize the memory to zero
                memset(dst,0,static_cast<size_t>(ElementCount * TypeSize));
            }
            else {
                InitializeValueInternal(dst);
            }
        }

        // Initialize the value in a container (class/struct) to default
        FORCEINLINE void InitializeValue_InContainer(void* dst) const {
            if (PropertyFlags & PropertyFlags_ZeroConstructor) {    
                memset(GetTypedPropertyPtr<void>(dst),0,static_cast<size_t>(ElementCount * TypeSize));
            }
            else {
                InitializeValueInternal(GetTypedPropertyPtr<void>(dst));
            }
        }

        FORCEINLINE void SetValue_InContainer() const;
        FORCEINLINE void GetValue_InContainer() const;

        FORCEINLINE void SetSpecificValue_InContainer() const;
        FORCEINLINE void GetSpecificValue_InContainer() const;

        FORCEINLINE void CopyValue(void* dst, const void* src) const {
            if (PropertyFlags & PropertyFlags_IsPOD) {
                memcpy(dst,src,static_cast<size_t>(ElementCount * TypeSize));
            }
            else {
                CopyValueInternal(dst,src,ElementCount);
            }
        }

        FORCEINLINE void CopySingleValue(void* dst, const void* src) const {
            if (PropertyFlags & PropertyFlags_IsPOD) {
                memcpy(dst,src,static_cast<size_t>(TypeSize));
            }
            else {
                CopyValueInternal(dst,src,1);
            }
        }

        
         

      /*  virtual std::string ToString(void* instance) const = 0;
        virtual void FromString(void* instance, const std::string& value) const = 0;

        // Save & Load
        virtual void Serialize(void* obj, std::ostream& out) const = 0;
        virtual void Deserialize(void* obj, std::istream& in) const = 0;

        
        virtual void Draw() const = 0;
*/
    protected:
        virtual void InitializeValueInternal(void* dst) const;
        
    private:

        virtual void CopyValueInternal(void* dst,const void* src, int32 count) const;
        
        FORCEINLINE void* GetPropertyPtrInternal(void* containerPtr,int32 arrayIndex = 0) const {
            Expects(arrayIndex >= 0 && arrayIndex < ElementCount);
            Expects(containerPtr);

            // Cast to uint8* for pointer arithmetic
            return (uint8*)containerPtr + Offset + arrayIndex * TypeSize;
        }
        
        EPropertyFlags PropertyFlags;

        int32 ElementCount; // The number of elements of the element for C style arrays (int[])
        int32 TypeSize; // The size of the property type

        int32 Offset; // The offset of the property in the owning struct/class

        VProperty* NextRef; // Next property in the linked list of properties
    };
    
}
