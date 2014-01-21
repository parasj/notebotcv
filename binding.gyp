{
	"targets": [
		{
			"target_name": "nodebotcv",
			"sources": [ "main.cpp" ],
			"include_dirs": [ "/usr/local/include/opencv" ],
			'libraries': ['<!@(pkg-config --libs opencv)']
		}
	]
}
