#pragma once

#ifndef VULCAN_LOG_ERROR
#define VULCAN_LOG_ERROR(...)\
fmt::print(fmt::fg(fmt::color::red), __VA_ARGS__);
#endif


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
#define PREPROCESSOR_TO_STRING_INNER(x) #x
#define PREPROCESSOR_TO_STRING(x) PREPROCESSOR_TO_STRING_INNER(x)

#include <CoreAPI/Memory.h>
#define DECLARE_FIELD(TClass,TSuperClass,TStaticFlags) \
private: \
    TClass& operator=(TClass&&); \
    TClass& operator=(const TClass&); \
public: \
    using Super = TSuperClass; \
    using ThisClass = TClass;\
    TClass(VFieldClass* InClass) : Super(InClass) { \
    } \
    static VFieldClass* StaticClass(); \
    static VField* Construct(const VField* InOwner,Name InName); \
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
        TClass* Mem = (TClass*)VMemory::Alloc(InSize); \
        new (Mem) TClass(TClass::StaticClass()); \
        return Mem; \
    } \
    inline void operator delete(void* InMem) { \
        VMemory::Free(InMem); \
    } \
    virtual size_t GetFieldSize() const override { \
        return sizeof(TClass); \
    }

#define IMPLEMENT_FIELD(TClass) \
VField* TClass::Construct(const VField* InOwner,Name InName) { \
    return new TClass(InOwner,InName); \
} \
VFieldClass* TClass::StaticClass() { \
    static VFieldClass StaticFieldClass(PREPROCESSOR_TO_STRING(TClass), TClass::StaticClassCastFlagsPrivate(), TClass::StaticClassCastFlags(),TClass::Super::StaticClass(),&TClass::Construct); \
    return &StaticFieldClass; \
}