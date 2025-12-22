target("VulcanEngine")
    set_kind("shared")
	add_deps("VMath","VUI","VCore")
    add_files("src/Vulcan/**.cpp")
    add_headerfiles("include/**.h")
    add_packages("entt","fmt","imgui","libsdl2","libsdl2_image", { public = true})
	add_packages("glfw","glew")
    add_packages("nlohmann_json")
    add_defines("VULCAN_ENGINE_BUILD")
	add_includedirs("$(projectdir)/Intermediate/Generated/VulcanEngine", { public = true })
	add_files("$(projectdir)/Intermediate/Generated/VulcanEngine/**.gen.cpp")

	--add_files("Intermediate/Generated/VClassInit.cpp")

