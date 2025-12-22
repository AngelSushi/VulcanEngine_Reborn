
#include <filesystem>
#include <iostream>

#include <CodeGen/CodeGenCpp.h>
#include <CodeGen/CodeGenHeader.h>
#include <Parser/Parser.h>
#include <Scanner/Scanner.h>


int main(int argc, char** argv) {
	std::string ProjectRoot = argv[1];
	std::filesystem::current_path(ProjectRoot);
	
	std::string root = "Intermediate/Generated/";

	std::cout << "[VHT] Scanning headers..." << std::endl;
	auto files = Scanner::ScanHeaders(ProjectRoot);
	std::cout << "[VHT] Found " << files.size() << " files." << std::endl;
	
	std::cout << "[VHT] Parsing macros..." << std::endl;
	auto parseResult = Parser::Parse(files);
	
	std::cout << "[VHT] Generating code..." << std::endl;
	
	for (auto& c : parseResult.Classes) {
		std::string namespaceRoot = "";

		for (auto& ns : c.Namespaces) {
			namespaceRoot += ns + "/";
		}

		std::vector<EnumInfo> EnumInClassFile;
		for (auto& e : parseResult.Enums) {
			if (e.ParentName == c.Name) {
				EnumInClassFile.push_back(e);
			}
		}

		if (!c.ParentName.empty()) {
			auto parent = std::find_if(parseResult.Classes.begin(), parseResult.Classes.end(),[&c] (const ClassInfo& c_info) {
				return c_info.Name == c.ParentName;
			});

			if (parent != parseResult.Classes.end()) {
				c.ParentName = parent->GetFullName();
				//c.Properties.insert(c.Properties.begin(),parent->Properties.begin(),parent->Properties.end());
				//c.Functions.insert(c.Functions.begin(),parent->Functions.begin(),parent->Functions.end());
			}
		}
		
		CodeGenHeader::GenerateClass(c,EnumInClassFile,root + namespaceRoot);
		CodeGenCpp::GenerateClass(c,EnumInClassFile,root + namespaceRoot);
	}

	for (auto& s : parseResult.Structs) {
		std::string namespaceRoot = "";
		
		for (auto& ns : s.Namespaces) {
			namespaceRoot += ns + "/";
		}

		std::vector<EnumInfo> EnumInClassFile;
		for (auto& e : parseResult.Enums) {
			if (e.ParentName == s.Name) {
				EnumInClassFile.push_back(e);
			}
		}

		if (!s.ParentName.empty()) {
			auto parentStruct = std::find_if(parseResult.Structs.begin(), parseResult.Structs.end(),[&s] (const StructInfo& s_info) {
				return s_info.Name == s.ParentName;
			});

			if (parentStruct != parseResult.Structs.end()) {
				s.ParentName = parentStruct->GetFullName();
				s.Properties.insert(s.Properties.begin(),parentStruct->Properties.begin(),parentStruct->Properties.end());
			}
		}
		
		CodeGenHeader::GenerateStruct(s,EnumInClassFile,root + namespaceRoot);
		CodeGenCpp::GenerateStruct(s,EnumInClassFile,root + namespaceRoot);
	}
	
	return 0;
}
