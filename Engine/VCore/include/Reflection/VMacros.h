#pragma once


#define VCLASS(...)
#define VSTRUCT(...)
#define VPROPERTY(...)
#define VFUNCTION(...)
#define VENUM()

#ifndef VCLASS_BODY
#define VCLASS_BODY() /* replaced by .vht.h include */
#endif

#ifndef VSTRUCT_BODY
#define VSTRUCT_BODY() /* replaced by .vht.h include */
#endif

#define VINTERFACE(...)

#define VINTERFACE_UBODY()
#define VINTERFACE_IBODY()

#define REGISTER_COMPONENT(T) \
static struct T##_AutoRegister { \
T##_AutoRegister() { \
::VulcanEngine::ComponentRegistry::Instance().RegisterType<T>(#T); \
} \
} T##_AutoRegister_Instance;


// For now , we put windowss macro here cause we don't support other platforms yet

#define FORCEINLINE __forceinline
//#define FORCENOINLINE __forceinline

#ifndef WITH_METADATA
#define WITH_METADATA 1
#endif

// We used double macro, cause  #x doenst allow macro expansion (it will be TClass name)
#define PREPROCESSOR_TO_STRING_INNER #x
#define PREPROCESSOR_TO_STRING(x) PREPROCESSOR_TO_STRING_INNER(x)

#include <CoreAPI/Memory.h>
#define DECLARE_FIELD(TClass,TSuperClass,TStaticFlags) \
private: \
    TClass& operator=(TClass&&); \
    TClass& operator=(const TClass&); \
public: \
    using Super = TSuperClass; \
    TClass(VFieldClass* InClass) : Super(InClass) { \
    } \
    static VFieldClass* StaticClass(); \
    static VField* Construct(VField* InOwner,const char* InName); \
    inline static constexpr uint64 StaticClassCastFlagsPrivate() { \
        return uint64(TStaticFlags); \
    } \
    inline static constexpr uint64 StaticClassCastFlags() { \
        return uint64(TStaticFlags) | Super::StaticClassCastFlags(); \
    } \
    inline void* operator new(const size_t InSize,void* InMem) { \
        return InMem; \
    } \
    inline void* operator new(const size_t InSize) { \
        TClass* Mem = (TClass*)Memory::Alloc(InSize); \
        new (Mem) TClass(TClass::StaticClass()); \
        return Mem; \
    } \
    inline void operator delete(void* InMem) { \
        Memory::Free(InMem); \
    } \
    virtual size_t GetFieldSize() const override { \
        return sizeof(TClass); \
    }

#define IMPLEMENT_FIELD(TClass) \
VField* TClass::Construct(VField* InOwner,const char* InName) { \
    VField* Instance = new TClass(InOwner,InName); \
    return Instance; \
} \
VFieldClass* TClass::StaticClass() { \
    static VFieldClass StaticFieldClass(PREPROCESSOR_TO_STRING(TClass), TClass::StaticClassCastFlagsPrivate(), TClass::StaticClassCastFlags(),TClass::Super::StaticClass(),&TClass::Construct); \
    return &StaticFieldClass; \
} 