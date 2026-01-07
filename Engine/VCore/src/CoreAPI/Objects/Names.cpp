#include <CoreAPI/Objects/Names.h>

NameView MakeUnconvertedView(const char* View,int32 Len) {
    NameView Out;

    Out.Len = Len;
    Out.Name = View;

    return Out;
}

NameView MakeUnconvertedView(const char* View) {
    return MakeUnconvertedView(View,View ? strlen(View) : 0);
}

NameView MakeLowerView(NameView In, char* Buffer) {
    for (int32 i = 0; i < In.Len; i++) {
        Buffer[i] = (char)ToLowerASCII((unsigned char)In.Name[i]);
    }

    return {In.Len,Buffer};
}


NameEntryId NamePool::Store(NameView View) {
    char Buffer[MAX_NAME_LENGTH];
    NameView LowerView = MakeLowerView(View,Buffer);

    if (LowerView == View) { 
        NameEntryId DisplayId = FindOrCreateInternal(View,true,NameEntryId{}); // "actor"
        return DisplayId;
    }
    
    NameEntryId LowerId = FindOrCreateInternal(LowerView,true,NameEntryId{}); // "actor"
    NameEntryId DisplayId = FindOrCreateInternal(View,true,LowerId); // "Actor"

    return DisplayId;
}

NameEntryId NamePool::Find(NameView View) {
    return FindOrCreateInternal(View,false,NameEntryId{});
}

Name::Name(const char* InName, EFindState FindState)
    : Name(NameHelper::CreateDetectNumber(MakeUnconvertedView(InName),FindState)) {}

Name::Name(const char* Name, int32 InLen, EFindState FindState)
    : Name(NameHelper::CreateDetectNumber(MakeUnconvertedView(Name,InLen),FindState)) {}

Name::Name(const char* Name, int32 InNumber)
    : Name(NameHelper::CreateWithNumber(MakeUnconvertedView(Name),InNumber,FindState_Add)) {
}

Name::Name(const char* Name, int32 InLen, int32 InNumber)
    : Name(NameHelper::CreateWithNumber(MakeUnconvertedView(Name,InLen),InNumber,FindState_Add)){
}

std::string Name::ToString() const {
    std::string Out;
    ToString(Out);
    return Out;
}

void Name::ToString(std::string& OutStr) const {
    const NameEntry* Entry = GetDisplayEntry();
    
    if (GetNumber() == 0) {
        OutStr.clear();
        OutStr.reserve(Entry->GetNameLength());
        Entry->AppendNameToString(OutStr);
    }
    else {
        OutStr.clear();
        OutStr.reserve(Entry->GetNameLength() + 6);
        Entry->AppendNameToString(OutStr);

        OutStr += '_';
        OutStr += std::to_string(GetNumber());
    }
}

void Name::AppendString(std::string& OutStr) const {
    const NameEntry* Entry = GetDisplayEntry();

    Entry->AppendNameToString(OutStr);
    if (GetNumber() != 0) {
        OutStr += '_';
        OutStr += std::to_string(GetNumber());
    }
}
