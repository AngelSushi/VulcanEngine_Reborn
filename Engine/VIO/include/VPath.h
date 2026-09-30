#pragma once
#include <CoreAPI/precomp.h>


class VRelativePath;
class VPhysicalPath;

class VIO_API VPath {

public:
    virtual ~VPath() = default;
    static std::unique_ptr<VPath> FromPath(std::string Value);

    bool IsDirectory() const;
    bool IsFile() const;

    std::string String() const;
    VPhysicalPath Parent() const;

private:
    static bool IsAbsolutePath(std::string InPath);
    static bool NormalizeRelativePath(std::string& InPath);
    
protected:
    std::string Path;
};

/*
 * @brief PhysicalPath is a path that is absolute and points to a physical location on the filesystem.
 * (e.g C:\Users\Username\Documents\file.txt or /home/username/file.txt)
 */
class VIO_API VPhysicalPath : public VPath {

public:
    VPhysicalPath() = default;
    VPhysicalPath(std::string InPath);

    VPhysicalPath& operator/=(const VRelativePath& Relative);
    VPhysicalPath operator/(const VRelativePath& Relative) const;
    
    VRelativePath ToRelative(const VPhysicalPath* Base) const;
};

/*
 * @brief RelativePath is a path that is relative to a directory but we doesnt know which directory.
 * (e.g "Documents/file.txt" or "file.txt")
 */
class VIO_API VRelativePath : public VPath {
    
public:
    VRelativePath() = default;
    explicit VRelativePath(std::string InPath);

    VPhysicalPath ToPhysical(const VPhysicalPath& Root) const;
};

/*
 * @brief VirtualPath is a path that is relative to a root path.
 * (e.g "root://Documents/file.txt" or "root://file.txt")
 */
class VIO_API VVirtualPath : public VPath {

public:
    explicit VVirtualPath(std::string InRoot, std::string InRelativePath) : Root(std::move(InRoot)), RelativePath(std::move(InRelativePath)) {};

private:
    std::string Root;
    std::string RelativePath;
};

