target("VulcanTests")
	set_kind("binary")
	if is_plat("windows") then
		add_ldflags("/SUBSYSTEM:CONSOLE")
	end
	set_default(false)
	add_files("src/**.cpp")
	add_packages("gtest")
	
	add_deps("VIO","VMath")
	
	add_tests("all")
