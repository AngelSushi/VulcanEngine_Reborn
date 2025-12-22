target("VCore")
    set_kind("static")
    add_headerfiles("include/**.h")
    add_files("src/**.cpp")
	add_includedirs("include", { public = true }) 
	add_includedirs("$(projectdir)/Intermediate/Generated/VulcanEngine", { public = true })
	add_packages("fmt","nlohmann_json","imgui","libsdl2","libsdl2_image", { public = true})
	add_deps("VMath","VHT")
	
	before_build(function (target)
		print("[VHT] Building Vulcan Header Tool...")
		
		
		local vht = target:dep("VHT"):targetfile()
		local vht_dir = path.directory(vht)
		os.execv(vht, { os.projectdir() }, { curdir = vht_dir })
	end)