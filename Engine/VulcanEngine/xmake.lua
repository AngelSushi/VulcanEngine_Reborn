target("VulcanEngine")
    set_kind("shared")
	add_deps("VMath","VCore","VIO")
	--add_deps("VUI")
    add_files("src/Vulcan/**.cpp")
    add_headerfiles("include/**.h")
    add_packages("entt","fmt","libsdl2_image","libsdl2_ttf", { public = true})
	add_packages("libsdl2", { public = true })
	
	add_packages("glfw","glew")
    add_packages("nlohmann_json")
    add_defines("VULCAN_ENGINE_BUILD")
	add_includedirs("Intermediate/Generated", { public = true })
	--add_files("$(projectdir)/Intermediate/Generated/VulcanEngine/**.gen.cpp")

	add_files("Intermediate/Generated/**.cpp")

