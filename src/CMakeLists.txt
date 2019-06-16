add_library(stegmes BitmapArray.cpp
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

install(TARGETS stegmes DESTINATION lib)
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
