cmake_minimum_required (VERSION 3.0)
project (steganoMessage)

#Version Number
set (steganoMessage_VERSION_MAJOR 0)
set (steganoMessage_VERSION_MINOR 3)

#set folders for garbage files
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

#set path to configuration file for version numbers
configure_file (
	"${PROJECT_SOURCE_DIR}/steganoMessageConfig.h.in"
	"${PROJECT_BINARY_DIR}/header/steganoMessageConfig.h"
	)

#set paths for all directories that need to be included
include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/header"
	)

#add subdirectory for source files 
add_subdirectory (src)
set (EXTRA_LIBS ${EXTRA_LIBS} src)

#get the path for libjpeg and include it
find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIRS})

#get the path for libpng and include it
find_package(PNG REQUIRED) 
include_directories(${PNG_INCLUDE_DIRS})

#get path for opengl stuff
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
set (OPENGL_LIBS ${OPENGL_LIBRARIES})

find_package(SFML COMPONENTS graphics REQUIRED)

find_package(GLEW)
include_directories(${GLEW_INCLUDE_DIRS})
set (GLED_LIBS ${GLEW_LIBRARIES})

find_package(glfw3)



#generate output messages for libjpeg
message("libjpeg include path: " ${JPEG_INCLUDE_DIR})
message("libjpeg version: " ${JPEG_VERSION})

#setup variable for libjpeg
set (JPEG_LIBS ${JPEG_LIBS} ${JPEG_LIBRARY_RELEASE})

#generate output messages for libpng
message("libpng include path: " ${PNG_INCLUDE_DIR})
message("libpng version: " ${PNG_VERSION_STRING})

#setup variable for libpng
set (PNG_LIBS ${PNG_LIBS} ${PNG_LIBRARY})

#check if system is mac or linux based and generate name of executable depending on that
if (UNIX AND NOT APPLE)
	message("Found Linux OS")
	add_executable(steganoMessage_Linux ${PROJECT_SOURCE_DIR}/src/main.cpp)

	target_link_libraries(steganoMessage_Linux ${EXTRA_LIBS}
		${JPEG_LIBS}
		${PNG_LIBS}
		${OPENGL_LIBS}
		sfml-graphics
		${GLEW_LIBRARIES}
		glfw
		)
endif (UNIX AND NOT APPLE)

if(APPLE)
	message("Found MAC OS")
	add_executable(steganoMessage_MAC ${PROJECT_SOURCE_DIR}/src/main.cpp)

	target_link_libraries(steganoMessage_MAC ${EXTRA_LIBS}
		${JPEG_LIBS}
		${PNG_LIBS}
		${OPENGL_LIBS}
		sfml-graphics
		${GLEW_LIBRARIES}
		glfw
		)
endif(APPLE)
