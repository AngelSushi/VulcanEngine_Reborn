#include <CodeGen/CodeGenCpp.h>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <variant>

#include "FileUtils.h"
#include "Parser/Utils.h"

static std::string MakePath(const TypeInfoBase& base_info, const std::string& base) {
    return (std::filesystem::path(base) / (base_info.Name + ".gen.cpp")).string();
}

void CodeGenCpp::GenerateClass(const ClassInfo& class_info, std::vector<EnumInfo> enums,const std::string& output_path) {
    std::ostringstream buffer;

    buffer << "//AUTO GENERATED. EDIT AT YOUR OWN RISK.\n";
    
    buffer << "#include <CoreAPI/precomp.h>\n\n";
    
    buffer << "#include \""  << class_info.GetRelativePath() << "\"\n";
    buffer << "#include \"" << class_info.Name << ".vht.h\"\n\n";
    buffer << "#include <Reflection/VFieldRegistry.h>\n";
    buffer << "#include <Reflection/Function/VStaticFunction.h>\n";
    buffer << "#include <unordered_map>\n";
    buffer << "#include <variant>\n\n";

    buffer << "using namespace VulcanCore; \n\n";

    // ================================================================
                            // 1. Enum Registration
    // ================================================================

    for (auto& e : enums) {
        GenerateEnumPart(e,buffer);
    }
    
    // ================================================================
                            // 2. Statics Helper
    // ================================================================
    
    buffer << "struct VC_Construct_VClass_" << class_info.Name << "_Statics {\n";

    if (!class_info.Properties.empty()) {
        buffer << "    static void RegisterProperties(VClass& c); \n";
    }

    if (!class_info.Functions.empty()) {
        buffer << "    static void RegisterFunctions(VClass& c); \n";
    }
    
    buffer << "\n    static VClass* Construct() { \n";
    buffer << "        auto* c = new VClass(\"" << class_info.Name << "\", \"" << class_info.GetFullName() << "\",sizeof(" << class_info.GetFullName() << "));\n";
    
    if (!class_info.ParentName.empty()) {
        buffer << "        c->Parent = &" << class_info.ParentName << "::StaticClass(); \n";
    }

    if (!class_info.Properties.empty()) {
        buffer << "        RegisterProperties(*c); \n";
    }

    if (!class_info.Functions.empty()) {
        buffer << "        RegisterFunctions(*c); \n";
    }

    buffer << "        VFieldRegistry::Instance().RegisterType(typeid(" << class_info.GetFullName() << "), c); \n";
    buffer << "        return c; \n";
    buffer << "    } \n";
    buffer << "}; \n\n";

    // ================================================================
                            // 3. Singleton Access
    // ================================================================

    buffer << "VClass* VC_Construct_VClass_" << class_info.Name << "() { \n";
    buffer << "    static VClass* Singleton = nullptr; \n";
    buffer << "    if(!Singleton) { \n";
    buffer << "        Singleton = VC_Construct_VClass_" << class_info.Name << "_Statics::Construct(); \n";
    buffer << "    } \n";
    buffer << "    return Singleton; \n";
    buffer << "}\n\n";

    // ================================================================
                            // 4. Startup Registration
    // ================================================================

    buffer << "struct VC_CompiledInDefer_" << class_info.Name << " { \n";
    buffer << "    VC_CompiledInDefer_" << class_info.Name << "() { \n";
    buffer << "        (void)VC_Construct_VClass_" << class_info.Name << "(); \n";
    buffer << "    } \n";
    buffer << "}; \n\n";
    buffer << "static VC_CompiledInDefer_" << class_info.Name << " VC_CompiledInDefer_" << class_info.Name << "_Obj; \n\n";

    // ================================================================
                            // 5. StaticClass / GetClass
    // ================================================================

    buffer << class_info.dll << " VClass& " << class_info.GetFullName() << "::StaticClass() { \n";
    buffer << "    return *VC_Construct_VClass_" << class_info.Name << "(); \n";
    buffer << "}; \n\n";

    buffer << class_info.dll << " VClass& " << class_info.GetFullName() << "::GetClass() const { \n";
    buffer << "    return " << class_info.Name << "::StaticClass(); \n";
    buffer << "}; \n\n";

    // ================================================================
                            // 6. Properties Register
    // ================================================================

    if (!class_info.Properties.empty()) {
        buffer << "void VC_Construct_VClass_" << class_info.Name << "_Statics::RegisterProperties(VClass& c) { \n";

        buffer << "    using MetaValue = std::variant<std::string, std::vector<std::string>>; \n";
        buffer << "    using MetaMap = std::unordered_map<std::string, MetaValue>; \n\n";

        
        for (auto& prop : class_info.Properties) {
            buffer << "    std::vector<std::string> attrs_" << prop.Name << " = {";
            for (size_t i = 0; i < prop.Meta.SimpleAttributes.size();i++) {
                if (i > 0) {
                    buffer << ", ";
                }
                
                buffer << "\"" << prop.Meta.SimpleAttributes[i] << "\"";
            }
            buffer << "}; \n";

            buffer << "    MetaMap meta_" << prop.Name << "; \n";
            for (auto& [k,v] : prop.Meta.MetaPairs) {
                if (auto* p = std::get_if<std::string>(&v)) {
                    buffer << "    meta_" << prop.Name << "[\"" << k << "\"] = std::string(\"" << *p << "\"); \n";
                }
                else {
                    buffer << "    meta_" << prop.Name << "[\"" << k << "\"] = std::vector<std::string>{";
                    for (auto& item : std::get<std::vector<std::string>>(v)) {
                        buffer << "\"" << item << "\"";
                        if (item != std::get<std::vector<std::string>>(v).back()) {
                            buffer << ",";
                        }
                    }
                    buffer << "}; \n";
                }
            }

            buffer << "    c.AddProperty(std::make_unique<VProperty<" << class_info.GetFullName() << "," << prop.Type << ">>(\"" << prop.Name << "\", &" << class_info.GetFullName() << "::" << prop.Name <<  ", attrs_" << prop.Name << ", meta_" << prop.Name << ")); \n\n";
        }
        buffer <<"}; \n\n";
    }
    // ================================================================
                            // 7. Functions Register
    // ================================================================

    if (!class_info.Functions.empty()) {
        buffer << "void VC_Construct_VClass_" << class_info.Name << "_Statics::RegisterFunctions(VClass& c) { \n";
        for (auto& func : class_info.Functions) {
            std::string methodSignature;

            if (!func.isStatic) {
                methodSignature += class_info.GetFullName() + ",";
            }
            methodSignature += func.ReturnType;

            for (auto& param : func.Parameters) {
                methodSignature += "," + param.first;
            }
            
            if (func.isStatic) {
                buffer << "   c.AddFunction(std::make_unique<VStaticFunction<" << methodSignature << ">>(\"" << func.Name << "\", &" << class_info.GetFullName() << "::" << func.Name << ")); \n";
            }
            else {
                buffer << "   c.AddFunction(std::make_unique<VFunction<" << methodSignature << ">>(\"" << func.Name << "\", &" << class_info.GetFullName() << "::" << func.Name << ")); \n";
            }
        }
    
        buffer <<"}; \n\n";
    }
    
    FileUtils::WriteFile(MakePath(class_info,output_path), buffer.str());
}

void CodeGenCpp::GenerateStruct(const StructInfo& struct_info, std::vector<EnumInfo> enums,const std::string& output_path) {
    std::ostringstream buffer;
    
    buffer << "//AUTO GENERATED. EDIT AT YOUR OWN RISK.\n";

    buffer << "#include <precomp.h>\n\n";

    buffer << "#include \""  << struct_info.GetRelativePath() << "\"\n";
    buffer << "#include \"" << struct_info.Name << ".vht.h\"\n\n";

    buffer << "using namespace VulcanCore; \n\n";

    // ================================================================
                            // 1. Enum Registration
    // ================================================================

    for (auto& e : enums) {
        GenerateEnumPart(e,buffer);
    }
    
    
    // ================================================================
                            // 2. Statics Helper
    // ================================================================
    
    buffer << "struct VC_Construct_VStruct_" << struct_info.Name << "_Statics {\n";

    if (!struct_info.Properties.empty()) {
        buffer << "    static void RegisterProperties(VScriptStruct& s); \n";
    }
    
    buffer << "\n    static VScriptStruct* Construct() { \n";
    buffer << "        auto* s = new VScriptStruct(\"" << struct_info.Name << "\", \"" << struct_info.GetFullName() << "\", sizeof(" << struct_info.GetFullName() << "));\n";

    if (!struct_info.ParentName.empty()) {
        buffer << "        s->Parent = &" << struct_info.ParentName << "::StaticStruct(); \n";
    }

    if (!struct_info.Properties.empty()) {
        buffer << "        RegisterProperties(*s); \n";
    }

    buffer << "        VFieldRegistry::Instance().RegisterType(typeid(" << struct_info.GetFullName() << "), s); \n";
    buffer << "        return s; \n";
    buffer << "    } \n";
    buffer << "}; \n\n";

    // ================================================================
                            // 3. Singleton Access
    // ================================================================

    buffer << "VScriptStruct* VC_Construct_VStruct_" << struct_info.Name << "() { \n";
    buffer << "    static VScriptStruct* Singleton = nullptr; \n";
    buffer << "    if(!Singleton) { \n";
    buffer << "        Singleton = VC_Construct_VStruct_" << struct_info.Name << "_Statics::Construct(); \n";
    buffer << "    } \n";
    buffer << "    return Singleton; \n";
    buffer << "}\n\n";

    // ================================================================
                            // 4. Startup Registration
    // ================================================================

    buffer << "struct VC_CompiledInDefer_VStruct_" << struct_info.Name << " { \n";
    buffer << "    VC_CompiledInDefer_VStruct_" << struct_info.Name << "() { \n";
    buffer << "        (void)VC_Construct_VStruct_" << struct_info.Name << "(); \n";
    buffer << "    } \n";
    buffer << "}; \n\n";
    buffer << "static VC_CompiledInDefer_VStruct_" << struct_info.Name << " VC_CompiledInDefer_" << struct_info.Name << "_Obj; \n\n";

    // ================================================================
                            // 5. StaticClass / GetClass
    // ================================================================

    buffer << "VScriptStruct& " << struct_info.GetFullName() << "::StaticStruct() { \n";
    buffer << "    return *VC_Construct_VStruct_" << struct_info.Name << "(); \n";
    buffer << "}; \n\n";

    // ================================================================
                            // 6. Properties Register
    // ================================================================

    if (!struct_info.Properties.empty()) {
        buffer << "void VC_Construct_VStruct_" << struct_info.Name << "_Statics::RegisterProperties(VScriptStruct& s) { \n";

        buffer << "    using MetaValue = std::variant<std::string, std::vector<std::string>>; \n";
        buffer << "    using MetaMap = std::unordered_map<std::string, MetaValue>; \n\n";

        for (auto& prop : struct_info.Properties) {
            buffer << "    std::vector<std::string> attrs_" << prop.Name << " = {";
            for (size_t i = 0; i < prop.Meta.SimpleAttributes.size();i++) {
                if (i > 0) {
                    buffer << ", ";
                }
                
                buffer << "\"" << prop.Meta.SimpleAttributes[i] << "\"";
            }
            buffer << "}; \n";

            buffer << "    MetaMap meta_" << prop.Name << "; \n";
            for (auto& [k,v] : prop.Meta.MetaPairs) {
                if (auto p = std::get_if<std::string>(&v)) {
                    buffer << "    meta_" << prop.Name << "[\"" << k << "\"] = std::string(\"" << *p << "\"); \n";
                }
                else {
                    buffer << "    meta_" << struct_info.Name << "[\"" << k << "\"] = std::vector<std::string>{";
                    for (auto& item : std::get<std::vector<std::string>>(v)) {
                        buffer << "\"" << item << "\"";
                        if (item != std::get<std::vector<std::string>>(v).back()) {
                            buffer << ",";
                        }
                    }
                    buffer << "}; \n";
                }
            }

           buffer << "    s.AddProperty(std::make_unique<VProperty<" << struct_info.GetFullName() << "," << prop.Type << ">>(\"" << prop.Name << "\", &" << struct_info.GetFullName() << "::" << prop.Name <<  ", attrs_" << prop.Name << ", meta_" << prop.Name << ")); \n\n";
         }
        buffer <<"}; \n\n";
    }
    
    FileUtils::WriteFile(MakePath(struct_info,output_path), buffer.str());
}

void CodeGenCpp::GenerateEnumPart(const EnumInfo& enum_info, std::ostringstream& out) {
    out << "// Begin Enum " << enum_info.Name << "\n";
    
    out << "struct VC_Construct_VEnum_" << enum_info.Name << "_Statics { \n";
    out << "    static VEnum* Construct() { \n";
    out << "        auto* e = new VEnum(\"" << enum_info.Name << "\"); \n";

    for (auto& value : enum_info.Values) {
        out << "        e->AddEntry(\"" << value << "\", static_cast<int>(" << enum_info.GetFullName() << "::" << value << ")); \n";
    }
        
    out << "\n        VFieldRegistry::Instance().RegisterType(typeid(" << enum_info.GetFullName() << "), e); \n";
    out << "        return e; \n";
    out << "    } \n";
    out << "}; \n\n";

    out << "VEnum* VC_Construct_VEnum_" << enum_info.Name << "() { \n";
    out << "    static VEnum* Singleton = nullptr; \n";
    out << "    if(!Singleton) { \n";
    out << "        Singleton = VC_Construct_VEnum_" << enum_info.Name << "_Statics::Construct(); \n";
    out << "    } \n";
    out << "    return Singleton; \n";
    out << "} \n\n";

    // Force Registration at module startup
    out << "struct VC_CompiledInDeferEnum_" << enum_info.Name << " { \n";
    out << "    VC_CompiledInDeferEnum_" << enum_info.Name << "() { \n";
    out << "        (void)VC_Construct_VEnum_" << enum_info.Name << "(); \n";
    out << "    } \n";
    out << "}; \n\n";

    out << "static VC_CompiledInDeferEnum_" << enum_info.Name << " VC_CompiledInDeferEnum_" << enum_info.Name << "_Obj; \n\n";
        
    out << "// End Enum " << enum_info.Name << "\n\n";
}

