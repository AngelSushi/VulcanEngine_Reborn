add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

add_requires("imgui v1.90.9-docking", { configs = { sdl2 = true, sdl2_renderer = true,debug = is_mode("debug"), with_symbols = true}})

add_requires("fmt","libsdl2","libsdl2_image","entt","nlohmann_json")
add_requireconfs("libsdl2", "**.libsdl2", { configs = { sdlmain = not is_mode("debug") }})

set_languages("cxx20")

set_project("VulcanEngine")

set_exceptions("cxx")
set_encodings("utf-8")
set_rundir(".")
set_warnings("allextra")

add_includedirs("Engine/VulcanEngine/include/Vulcan", { public = true})
add_includedirs("Engine/VulcanEngine/include", { public = true})
add_includedirs("ThirdParty/gsl/include", { public = true })

add_headerfiles("Engine/VCore/include/precomp.h", {prefixheader = "precomp.h"})

add_syslinks("Comdlg32")

add_cxflags("/wd4251")
	

includes("Tools/VHT/")
includes("Engine/VCore/")	
includes("Engine/VMath/")
includes("Engine/VUI/")
includes("Engine/VulcanEngine/")
includes("Game/")

target("GEN_ALL_BUILD")
	set_kind("phony")
	add_deps("VMath","VCore","VUI","VulcanEngine","VulcanGame")
	
	
set_default("GEN_ALL_BUILD")