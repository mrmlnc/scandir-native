{
	"targets": [
		{
			"target_name": "addon",
			"sources": ["src/cpp/addon.cc"],
			"include_dirs": [
				"src/cpp",
				"<!(node -e \"require('nan')\")"
			]
		}
	]
}
