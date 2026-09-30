#include <VPath.h>

#include "Parser/Utils.h"

std::unique_ptr<VPath> VPath::FromPath(std::string Value) {

    const auto Separator = Value.find("://");

    if (Separator != std::string::npos) {
        return std::make_unique<VVirtualPath>(Value.substr(0, Separator), Value.substr(Separator + 3));
    }

    if (IsAbsolutePath(Value)) {
        return std::make_unique<VPhysicalPath>(Value);
    }

    if (NormalizeRelativePath(Value)) {
        return std::make_unique<VRelativePath>(Value);
    }

    // Error : cant have a path from the string 
    return nullptr;
}

// Should maybe not pass by std::filesystem in the future, but for now as all compilers have cpp compiler we can let it. 
bool VPath::IsDirectory() const {
    return std::filesystem::is_directory(Path);
}

bool VPath::IsFile() const {
    return std::filesystem::is_regular_file(Path);
}

std::string VPath::String() const {
    return Path;
}

VPhysicalPath VPath::Parent() const {
    size_t Index = Path.find_last_of("/\\",Path.length() - 1);

    if (Index == std::string::npos) {
        return VPhysicalPath();
    }

    return VPhysicalPath(Path.substr(0,Index));
}

// Need to be platform agnostic.Don't even use std::filesystem if the target platform doesn't have c++17 support.
bool VPath::IsAbsolutePath(std::string InPath) {
    if (InPath.empty()) {
        return false;
    }

    return std::filesystem::path(InPath).is_absolute();
}

bool VPath::NormalizeRelativePath(std::string& InPath) {
    if ((!InPath.empty() && InPath.front() == '/') || InPath.find('\\') != std::string::npos || InPath.find(':') != std::string::npos || InPath.find('\0') != std::string::npos) {
        return false;
    }

    const std::string_view Input = InPath;
    std::vector<std::string_view> Components;

    for (size_t Start = 0; Start < Input.size();) {
        size_t Separator = Input.find('/',Start);
        size_t End = Separator == std::string_view::npos ? Input.size() : Separator;

        std::string_view Component = Input.substr(Start,End - Start);

        if (Component == "..") {
            if (Components.empty()) {
                return false;
            }

            Components.pop_back();
        }
        else if (!Component.empty() && Component != ".") {
            Components.push_back(Component);
        }

        if (Separator == std::string_view::npos) {
            break;
        }

        Start = Separator + 1;
    }
    

    std::string Normalized;
    Normalized.reserve(Components.size());

    for(const std::string_view Component : Components) {
        if (!Normalized.empty()) {
            Normalized += "/";
        }

        Normalized.append(Component);
    }

    InPath = std::move(Normalized);
    return true;
    
}

VPhysicalPath::VPhysicalPath(std::string InPath) {
    Path = std::move(InPath);
}

VRelativePath::VRelativePath(std::string InPath) {
    Path = std::move(InPath);
}



VPhysicalPath& VPhysicalPath::operator/=(const VRelativePath& Relative) {
    Path += "/" + Relative.String();
    return *this;
}

VPhysicalPath VPhysicalPath::operator/(const VRelativePath& Relative) const {
    VPhysicalPath Result = *this;
    Result /= Relative;
    return Result;
}

VRelativePath VPhysicalPath::ToRelative(const VPhysicalPath* Base) const {
    if (Base == nullptr) {
        throw std::invalid_argument("Base must be not null");    
    }

    const std::string Current = String();
    std::string Prefix = Base->String();

    if (Prefix.empty()) {
        throw std::invalid_argument("Prefix must not be empty");
    }

    if (Current == Prefix) {
        return VRelativePath("");
    }

    if (Current.compare(0, Prefix.size(), Prefix) != 0) {
        throw std::invalid_argument("Prefix must not be empty");
    }

    return VRelativePath(Current.substr(Prefix.size() + 1));
}

VPhysicalPath VRelativePath::ToPhysical(const VPhysicalPath& Root) const {
    return VPhysicalPath(std::move(Root)) / *this;
}
