target("VCore")
    set_kind("shared")
	add_defines("VCORE_BUILD")
    add_headerfiles("include/**.h")
    add_files("src/**.cpp")
	add_includedirs("include", { public = true }) 
	add_includedirs("Intermediate/Generated", { public = true })
	add_packages("fmt","nlohmann_json","libsdl2","libsdl2_image", { public = true})
	add_deps("VMath","VHT")
	
	before_build(function (target)
		print("[VHT] Building Vulcan Header Tool...")
		
		
		local vht = target:dep("VHT"):targetfile()
		local vht_dir = path.directory(vht)
		os.execv(vht, { os.projectdir() }, { curdir = vht_dir })
	end)