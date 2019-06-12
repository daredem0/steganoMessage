cmake_minimum_required (VERSION 3.0)
project (steganoMessage)

#Version Number
set (steganoMessage_VERSION_MAJOR 0)
set (steganoMessage_VERSION_MINOR 1)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

configure_file (
	"${PROJECT_SOURCE_DIR}/steganoMessageConfig.h.in"
	"${PROJECT_BINARY_DIR}/header/steganoMessageConfig.h"
	)

include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/header"
	)

add_subdirectory (src)
set (EXTRA_LIBS ${EXTRA_LIBS} src)

find_package(JPEG)
include_directories(${JPEG_INCLUDE_DIRS})

find_package(PNG)
include_directories(${PNG_INCLUDE_DIRS})

message(${JPEG_INCLUDE_DIR})
set (JPEG_LIBS ${JPEG_LIBS} ${JPEG_LIBRARY_RELEASE})

message(${PNG_INCLUDE_DIR})
set (PNG_LIBS ${PNG_LIBS} ${PNG_LIBRARY})

if (UNIX AND NOT APPLE)
	add_executable(steganoMessage_Linux ${PROJECT_SOURCE_DIR}/src/main.cpp)

	target_link_libraries(steganoMessage_Linux ${EXTRA_LIBS}
		${JPEG_LIBS}
		${PNG_LIBS}
		)
endif (UNIX AND NOT APPLE)

if(APPLE)
	add_executable(steganoMessage_MAC ${PROJECT_SOURCE_DIR}/src/main.cpp)

	target_link_libraries(steganoMessage_MAC ${EXTRA_LIBS}
		${JPEG_LIBS}
		${PNG_LIBS}
		)
endif(APPLE)