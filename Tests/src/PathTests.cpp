#include <gtest/gtest.h>
#include <VPath.h>

#include "FileManager.h"

TEST(PathTests, Validation)
{
    /*
    *"assets/config.json" → "assets/config.json"
    "assets/./config.json"     → "assets/config.json"
    "assets//config.json"      → "assets/config.json"
    "assets/temp/../file.bin"  → "assets/file.bin"
    "assets/.."                → "" : racine
    */

    auto P_1 = VPath::FromPath("assets/config.json");
    auto P_2 = VPath::FromPath("assets/./config.json");
    auto P_3 = VPath::FromPath("assets//config.json");
    auto P_4 = VPath::FromPath("assets/temp/../file.bin");
    auto P_5 = VPath::FromPath("assets/..");

    EXPECT_NE(P_1, nullptr);
    EXPECT_NE(P_2, nullptr);
    EXPECT_NE(P_3, nullptr);
    EXPECT_NE(P_4, nullptr);
    EXPECT_NE(P_5, nullptr);
    
    EXPECT_EQ(P_1->String(),"assets/config.json");
    EXPECT_EQ(P_2->String(),"assets/config.json");
    EXPECT_EQ(P_3->String(),"assets/config.json");
    EXPECT_EQ(P_4->String(),"assets/file.bin");
    EXPECT_EQ(P_5->String(),"");
}

TEST(PathTests,Error) {
    /*
    "../file.bin" 
    "assets/../../file.bin" 
    "C:file.bin"
    */

    auto P_1 = VPath::FromPath("../file.bin");
    auto P_2 = VPath::FromPath("assets/../../file.bin");
    auto P_4 = VPath::FromPath("C:file.bin");

    EXPECT_EQ(P_1, nullptr);
    EXPECT_EQ(P_2, nullptr);
    EXPECT_EQ(P_4, nullptr);
}

TEST(PathTests,Parent) {
    auto P_1 = VPath::FromPath("C:/Users/Public/MyGame/assets/character.png");

    EXPECT_EQ(P_1->Parent().String(), "C:/Users/Public/MyGame/assets");
    EXPECT_EQ(P_1->Parent().Parent().String(), "C:/Users/Public/MyGame");
    EXPECT_EQ(P_1->Parent().Parent().Parent().String(), "C:/Users/Public");
}

TEST(PathTests,PhysicalToRelative) {
    // Attention a si P_1 fini par un / 
    auto P_1 = VPath::FromPath("C:/Users/Public/MyGame");
    auto P_2 = VPath::FromPath("C:/Users/Public/MyGame/assets/character.png");

    auto* Base = dynamic_cast<VPhysicalPath*>(P_1.get());
    auto* File = dynamic_cast<VPhysicalPath*>(P_2.get());

    ASSERT_NE(Base, nullptr);
    ASSERT_NE(File, nullptr);

    EXPECT_EQ(File->ToRelative(Base).String(), "assets/character.png");
}

TEST(PathTests,RelativeToPhysical) {
    auto P_1 = VPath::FromPath("C:/Users/Public/MyGame");
    auto P_2 = VPath::FromPath("assets/character.png");

    auto* Base = dynamic_cast<VPhysicalPath*>(P_1.get());
    auto* File = dynamic_cast<VRelativePath*>(P_2.get());

    ASSERT_NE(Base, nullptr);
    ASSERT_NE(File, nullptr);

    EXPECT_EQ(File->ToPhysical(*Base).String(),"C:/Users/Public/MyGame/assets/character.png");
}

TEST(PathTests,FindDirectory) {
    auto P_1 = VPath::FromPath("C:/Users/Public/MyGame");
    auto P_2 = VPath::FromPath("C:/Users/Public/MyGame/character.bin");

    std::string Directory = FileManager::Get().FindDirectory(P_1->String());
    std::string Directory2 = FileManager::Get().FindDirectory(P_2->String());

    EXPECT_EQ(Directory,"C:/Users/Public");
    EXPECT_EQ(Directory2,"C:/Users/Public/MyGame");
}

TEST(PathTests,FindDirectoryRecursive) {

    auto P_1 = VPath::FromPath("C:/Users/Public/MyGame");
    auto V = std::vector<std::string>();

    FileManager::Get().FindDirectoryRecursive(V,P_1->String());

    auto Model = std::vector<std::string>();
    
    Model.push_back("C:/Users/Public");
    Model.push_back("C:/Users");
    Model.push_back("C:");
    
    EXPECT_EQ(V, Model);

    V.clear();
    
    auto P_2 = VPath::FromPath("C:/Users/Public/MyGame/character.bin");

    FileManager::Get().FindDirectoryRecursive(V,P_2->String());

    Model.insert(Model.begin(),"C:/Users/Public/MyGame");

    EXPECT_EQ(V, Model);
}

