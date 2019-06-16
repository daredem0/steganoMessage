add_library(src BitmapArray.cpp
	BitmapHeader.cpp
	ErrorHandler.cpp
	Filter.cpp
	Image.cpp
	Jpeg.cpp
	Png.cpp
	Message.cpp
	SteganoMessage.cpp
	OpenGLWrapper.cpp
	main.cpp
	)

install(TARGETS src DESTINATION lib)
message("src lib worked")
install(FILES ../header/BitmapHeader.h
	../header/ErrorHandler.h
	../header/Filter.h
	../header/Image.h
	../header/Jpeg.h
	../header/Png.h
	../header/Message.h
	../header/SteganoMessage.h
	../header/OpenGLWrapper.h
	../header/constants.h
	DESTINATION include)
message("src header worked")
