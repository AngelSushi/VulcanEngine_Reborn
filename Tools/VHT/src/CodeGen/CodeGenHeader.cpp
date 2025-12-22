#include <CodeGen/CodeGenHeader.h>
#include <filesystem>
#include <iostream>
#include <sstream>

#include "FileUtils.h"

static std::string MakePath(const TypeInfoBase& baseInfo, const std::string& baseDir) {
    return (std::filesystem::path(baseDir) / (baseInfo.Name + ".vht.h")).string();
}

void CodeGenHeader::GenerateClass(const ClassInfo& classInfo, std::vector<EnumInfo> enums,const std::string& outputPath) {
    std::ostringstream buffer;

    buffer << "//AUTO GENERATED. EDIT AT YOUR OWN RISK.\n\n";
    buffer << "#pragma once\n";
    buffer << "#include <typeindex>\n";
    buffer << "#include <Reflection/VClass.h>\n";
    buffer << "#include <Reflection/VEnum.h>\n\n";

    for (auto& e : enums) {
        GenerateEnumPart(e,buffer);
    }
    
    buffer << "namespace VulcanCore { class ObjectManager; } \n\n"; // To destroy

    buffer << "struct VC_Construct_VClass_" << classInfo.Name << "_Statics; \n";
    buffer << "::VulcanCore::VClass* VC_Construct_VClass_" << classInfo.Name << "(); \n\n";

    buffer << "#undef VCLASS_BODY()\n";
    buffer << "#define VCLASS_BODY() \\\n";
    buffer << "friend class ::VulcanCore::ObjectManager; \\\n";
    buffer << "template<typename T,typename... Args> \\\n";
    buffer << "friend T* ::VulcanCore::NewObject(Args&&... args); \\\n";
    buffer << "friend struct VC_Construct_VClass_" << classInfo.Name << "_Statics;\\\n";
    buffer << "public: \\\n";
    buffer << "    static ::VulcanCore::VClass& StaticClass(); \\\n";
    buffer << "    virtual ::VulcanCore::VClass& GetClass() const override;\n";
    
    FileUtils::WriteFile(MakePath(classInfo, outputPath), buffer.str());
}

void CodeGenHeader::GenerateStruct(const StructInfo& structInfo, std::vector<EnumInfo> enums,const std::string& outputPath) {
    std::ostringstream buffer;

    buffer << "//AUTO GENERATED. EDIT AT YOUR OWN RISK.\n\n";
    buffer << "#pragma once\n";
    buffer << "#include <typeindex>\n";
    buffer << "#include <Reflection/VScriptStruct.h>\n";
    buffer << "#include <Reflection/VEnum.h>\n\n";

    buffer << "namespace ";
    for (auto & ns : structInfo.Namespaces) {
        buffer << ns;

        if (&ns != &structInfo.Namespaces.back()) {
            buffer << "::";
        }
    }
    buffer << " { struct " << structInfo.Name << "; } \n\n";

    for (auto& e : enums) {
        GenerateEnumPart(e,buffer);
    }

    buffer << "struct VC_Construct_VStruct_" << structInfo.Name << "_Statics; \n";
    buffer << "::VulcanCore::VScriptStruct* VC_Construct_VStruct_" << structInfo.Name << "(); \n\n";

    buffer << "namespace VulcanCore { \n";
    buffer << "    template<>\n";
    buffer << "    inline VScriptStruct& StaticStruct<" << structInfo.GetFullName() << ">() { \n";
    buffer << "        return *VC_Construct_VStruct_" << structInfo.Name << "(); \n";
    buffer << "    }\n";
    buffer << "}\n\n";
    
    buffer << "#undef VSTRUCT_BODY()\n";
    buffer << "#define VSTRUCT_BODY() \\\n";
    buffer << "public: \\\n";
    buffer << "    static ::VulcanCore::VScriptStruct& StaticStruct(); \\\n";
    
    FileUtils::WriteFile(MakePath(structInfo, outputPath), buffer.str());
}

void CodeGenHeader::GenerateEnumPart(const EnumInfo& enum_info, std::ostream& out) {
    // Maybe forward declaration of enumclass
    
    out << "// Begin Enum " << enum_info.Name << "\n";
    
    out << "namespace ";
    for (auto & ns : enum_info.Namespaces) {
        out << ns;

        if (&ns != &enum_info.Namespaces.back()) {
            out << "::";
        }
    }
    out << " { enum class " << enum_info.Name << "; } \n\n";

    out << "struct VC_Construct_VEnum_" << enum_info.Name << "_Statics;\n";
    out << "::VulcanCore::VEnum* VC_Construct_VEnum_" << enum_info.Name << "(); \n\n";

    out << "namespace VulcanCore { \n";
    out << "    template <> \n";
    out << "    inline VEnum& StaticEnum<" << enum_info.GetFullName() << ">() { \n";
    out << "        return *VC_Construct_VEnum_" << enum_info.Name << "(); \n";
    out << "    } \n";
    out << "} \n";

    out << "// End Enum " << enum_info.Name << "\n\n";
}

